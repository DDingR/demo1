
import random
from collections import deque
import numpy as np

import torch
from torch import nn, cat
# from torch.utils.data import DataLoader
# from torchvision import datasets
from torchvision.transforms import ToTensor
from torch.utils.tensorboard import SummaryWriter

def shape_check(array, shape):
    assert array.shape == shape, \
        'shape error | array.shape ' + str(array.shape) + ' shape: ' + str(shape)

class Actor(nn.Module):
    def __init__(self, state_dim, action_dim, action_bound):
        super(Actor, self).__init__()
        self.action_dim = action_dim
        self.action_bound = action_bound

        self.Flatten = nn.Flatten()
        self.fc1 = nn.Linear(state_dim, 64)
        self.relu1 = nn.ReLU()
        self.fc2 = nn.Linear(64, 32)
        self.relu2 = nn.ReLU()
        self.fc3 = nn.Linear(32, 16)
        self.relu3 = nn.ReLU()
        self.fc4 = nn.Linear(16, self.action_dim)
        self.tanh = nn.Tanh()                

    def forward(self, x):
        x = self.Flatten(x)
        x = self.fc1(x)
        x = self.relu1(x)
        x = self.fc2(x)
        x = self.relu2(x)
        x = self.fc3(x)
        x = self.relu3(x)
        x = self.fc4(x)
        x = self.tanh(x)
        return x

class Critic(nn.Module):
    def __init__(self, state_dim, action_dim):
        super(Critic, self).__init__()
        # self.fc1_x = Dense(32, activation='relu')
        # self.fc1_a = Dense(32, activation='relu')
        # self.fc2 = Dense(32, activation='relu')
        # self.fc3 = Dense(16, activation='relu')
        # self.fc_out = Dense(
        #     1,
        #     kernel_initializer=RandomUniform(-1e-3, 1e-3)
        # )

        self.fc1_state = nn.Linear(state_dim, 32)
        self.relu1_state = nn.ReLU()
        
        self.fc1_action = nn.Linear(action_dim, 32)
        self.relu1_action = nn.ReLU()

        self.fc2 = nn.Linear(64, 32)
        self.relu2 = nn.ReLU()
        self.fc3 = nn.Linear(32, 16)
        self.relu3 = nn.ReLU()
        self.fc4 = nn.Linear(16, 1)

    def forward(self, X):
        x = self.fc1_state(X[0])
        x = self.relu1_state(x)
        a = self.fc1_action(X[1])
        a = self.relu1_action(a)
        h = cat((x, a),1)
        h = self.fc2(h)
        h = self.relu2(h)
        h = self.fc3(h)
        h = self.relu3(h)
        h = self.fc4(h)
        
        return h

class DDPG_Agent:
    def __init__(self, logger, agent_param, RL_param):
        self.logger = logger
        self.load_network_path = RL_param["load_network"]
 
        self.device = "cuda" if torch.cuda.is_available() else "cpu"
        self.logger.info(f"[INFO] Loaded device: {self.device}")

        # env parameters
        self.state_dim = len(agent_param["obs_list"])
        self.action_dim = len(agent_param["ctrl_list"])
        # self.action_bound = [ctrl_max for ctrl_max in agent_param["ctrl_max"]]
        self.action_bound = np.pi/3

        # hyperparameters
        self.GAMMA = RL_param["gamma"]
        self.Actor_learning_rate = RL_param["learning_rate"]["actor"]
        self.Critic_learning_rate = RL_param["learning_rate"]["critic"]
        self.BATCH_SIZE = RL_param["batch_size"]
        self.BUFFER_SIZE = RL_param["max_buffer_size"]
        self.TAU = RL_param["tau"]
        self.train_start_limit = RL_param["train_start_at"]

        # ou noise parameters
        self.noise_rho = RL_param["noise"]["rho"]
        self.noise_mu = RL_param["noise"]["mu"]
        self.noise_sigma = RL_param["noise"]["sigma"]
        self.noise_increment = RL_param["noise"]["increment"] # increment: 시간 증분

        # buffer
        self.buffer = deque(maxlen=self.BUFFER_SIZE)

        self.Actor_model = Actor(self.state_dim, self.action_dim, self.action_bound).to(self.device)
        self.Actor_target_model = Actor(self.state_dim, self.action_dim, self.action_bound).to(self.device)
        self.Critic_model = Critic(self.state_dim, self.action_dim).to(self.device)
        self.Critic_target_model = Critic(self.state_dim, self.action_dim).to(self.device)

        # model optimizer
        self.Actor_optimizer =  torch.optim.Adam(self.Actor_model.parameters(), lr=self.Actor_learning_rate)
        self.Critic_optimizer = torch.optim.Adam(self.Critic_model.parameters(), lr=self.Critic_learning_rate)

        if self.load_network_path != "NOT_LOADED":
            self.logger.error(f"[ERROR] Loading existing network is not available now. Use random network.")
            
        self.tensorboardWriter = SummaryWriter()


    def sample_append(self, state, action, reward, next_state, done):
        self.buffer.append(
            [
                state,
                action,
                reward,
                next_state,
                done
            ]
        )

    def TD_target(self, reward_list, next_state_list, done_list):
        next_action_list = np.array(next_state_list, dtype=np.float32)
        next_state_list = np.array(next_state_list, dtype=np.float32)

        next_action_list = self.Actor_target_model(
            torch.as_tensor(next_state_list, device=self.device)
        )
        next_Q = self.Critic_target_model(
            [
                torch.as_tensor(next_state_list, device=self.device),
                torch.as_tensor(next_action_list, device=self.device)
            ]
        )

        reward_list = np.reshape(reward_list, [self.BATCH_SIZE, 1])
        done_list = np.reshape(done_list, [self.BATCH_SIZE, 1])

        next_Q = next_Q.detach().cpu().numpy()
        # target = reward_list + (1 - done_list) * self.GAMMA * next_Q
        
        target = np.asarray(next_Q)
        for i in range(len(next_Q)):
            if done_list[i]:
                target[i] = reward_list[i]
            else: 
                target[i] = reward_list[i] + self.GAMMA * next_Q[i]

        shape_check(next_Q, (self.BATCH_SIZE, 1))
        shape_check(target, (self.BATCH_SIZE, 1))

        return target

    def update_target_networks(self, model, target_model, TAU):
        with torch.no_grad():
            # for i in range(len(model)):
            #     target_model[i].weight = TAU * model[i].weight + (1-TAU) * target_model[i].weight
            for target_param, param in zip(target_model.parameters(), model.parameters()):
                target_param.data.copy_(TAU*param.data + target_param.data*(1.0 - TAU))

    def ou_noise(self, pre_noise):
        nt = np.random.normal(size=self.action_dim)
        noise = pre_noise + self.noise_rho * (self.noise_mu - pre_noise) * self.noise_increment \
             + np.sqrt(self.noise_increment) * self.noise_sigma * nt
        
        return noise

    def get_action(self, state, noise):
        state = np.array(state, dtype=np.float32)
        # print(state)
        action = self.Actor_model(
            torch.as_tensor(
                state, device=self.device
            )
            # torch.tensor(state, device=self.device)
        )
        action = action.detach().cpu().numpy()

        action = np.clip(action+noise, -self.action_bound, self.action_bound)
        return action

    def actor_train(self, state_list):
        state_list = np.array(state_list, dtype=np.float32)

        self.Actor_model.train()
        action_list = self.Actor_model(
            torch.as_tensor(
                state_list, device=self.device
            )
        )
        # with torch.no_grad():
        Q = self.Critic_model(
            [
                torch.as_tensor(
                    state_list, device=self.device
                ),
                action_list
            ]
        )
        loss = -torch.mean(Q)
        shape_check(action_list, (self.BATCH_SIZE, 1))
        shape_check(Q, (self.BATCH_SIZE, 1))
        # grads = tape.gradient(loss, model_params)
        self.Actor_optimizer.zero_grad()
        loss.backward()
        self.Actor_optimizer.step()
        # self.Actor_optimizer.apply_gradients(zip(grads, model_params))

    def critic_train(self, target_list, state_list, action_list):
        # model_params = self.Critic_model.trainable_variables
        state_list = np.array(state_list, dtype=np.float32)
        action_list = np.array(action_list, dtype=np.float32)
        target_list = torch.tensor(target_list, device=self.device)

        self.Critic_model.train()
        predict_Q = self.Critic_model(
            [
            torch.as_tensor(
                state_list, device=self.device
            ),            
            torch.as_tensor(
                action_list, device=self.device
            )
            ]
        )
        # loss = tf.reduce_mean(tf.square(target_list - predict_Q))
        loss = torch.mean(torch.square(target_list - predict_Q))
        shape_check(predict_Q, (self.BATCH_SIZE, 1))
        shape_check(target_list, (self.BATCH_SIZE, 1))
        # grads = tape.gradient(loss, model_params)
        # self.Critic_optimizer.apply_gradients(zip(grads, model_params))
        self.Critic_optimizer.zero_grad()
        loss.backward()
        self.Critic_optimizer.step()

    def train(self):
        
        batch = random.sample(self.buffer, self.BATCH_SIZE)

        state_list = [sample[0][0] for sample in batch]
        action_list = [sample[1][0] for sample in batch]
        reward_list = [sample[2][0] for sample in batch]
        next_state_list = [sample[3][0] for sample in batch]
        done_list = [sample[4][0] for sample in batch]

        target_list = self.TD_target(reward_list, next_state_list, done_list)

        self.critic_train(target_list, state_list, action_list)
        self.actor_train(state_list)
        
        self.update_target_networks(
            self.Actor_model, self.Actor_target_model, self.TAU
        )
        self.update_target_networks(
            self.Critic_model, self.Critic_target_model, self.TAU
        )

    def saveasONNX(self):
        self.Actor_model.eval()
        self.Critic_model.eval()

        dummy_state = torch.randn(1, self.state_dim, device=self.device, requires_grad=True)
        dummy_action = torch.randn(1, self.action_dim, device=self.device, requires_grad=True)        
        
        torch.onnx.export(
            self.Actor_model, 
            dummy_state, 
            "DDPG_actor.onnx", 
            verbose=False,
            input_names= ['input']
            )
        torch.onnx.export(
            self.Critic_model, 
            [dummy_state, dummy_action], 
            "DDPG_critic.onnx", 
            verbose=False
            )         

    def tensorboardWrite(self, score, episode):
        self.tensorboardWriter.add_scalar("Score/score", score, episode)

