from utils.agents.DDPG import *

def rewardCalc(obs):    
    err_y = obs[1]
    err_r = obs[2] + 0.006
    reward = -(abs(err_y) + abs(err_r))

    state = [err_y, err_r]

    if reward > 1:
        isDone = True
    else:
        isDone = False

    state, reward, isDone

def agent_loader(reporter, agent_param, RL_param):
    reporter.info(f"[INFO] Agent loading started.")    
    algorithm = RL_param["Algorithm"]

    if algorithm == "DDPG":
        agent = DDPG_Agent(reporter, agent_param, RL_param)
        reporter.info(f"[INFO] Agent loading finished.")        
    else:
        reporter.critical(f"[CRITICAL] Unavailable RL algorithm. Your algorithm {algorithm}")
        exit()

    return agent
    
def __DDPG_agent_train(reporter, agent, env, train_param, agent_param):
    MAX_EPISODE = train_param['MAX_EPISODE']
    MAX_TIME = train_param['MAX_TIME']
    Ts = train_param['TIME_DIFFERENCE']
    Save_ONNX_per = train_param["SAVE_PER"]
    max_steps = int(MAX_TIME / Ts)

    obs_len = len(agent_param["obs_list"])
    ctrl_len = len(agent_param["ctrl_list"])

    for e in range(MAX_EPISODE):
        # reset env
        state = env.reset([]) 
        # the state should be initialized randomly
        state = np.reshape(state, [1, ctrl_len])

        # param initializenext_state
        score, step,done = 0, 0, 0
        noise = np.zeros()

        # copry weights to target network weights 
        agent.update_target_networks(
            agent.Actor_model, agent.Actor_target_model, 1
        )
        agent.update_target_networks(
            agent.Critic_model, agent.Critic_target_model, 1
        )

        while not done:
            print(state)
            print(time)
            step += 1

            # action, step
            noise = agent.ou_noise(noise)
            action = agent.get_action(state, noise)
            adj_parameters = {
                "steer": {'value': action}
            }            
            time, obs = env.step(adj_parameters)
            next_state, reward, done, _ = rewardCalc(obs)     

            # reshape dim
            action = np.reshape(action, [1, ctrl_len])
            next_state = np.reshape(next_state, [1, obs_len])
            reward =  np.reshape(reward, [1, 1])
            done = np.reshape(done, [1, 1])     

            # sampling
            agent.sample_append(
                state,action,reward,next_state,done
            )

            # train
            if len(agent.buffer) > agent.train_start_limit:
                agent.train()

            # for next_state
            score += reward[0][0]
            state = next_state

            reporter.info(f"[INFO] EPISODE: {e+1} |SCORE: {round(score, 3)}")
            agent.tensorboardWrite(score, e)

        agent.tensorboardWriter.flush()
        if (e+1) % Save_ONNX_per == 0:
            agent.saveasONNX()

def agent_train(reporter, agent, env, train_param, agent_param, RL_param):
    algorithm = RL_param["algorithm"] 
    if algorithm == "DDPG":
        __DDPG_agent_train(reporter, agent, env, train_param, agent_param)
    else:
        reporter.critical(f"[CRITICAL] Unavailable RL algorithm. Your algorithm {algorithm}")
        exit()

def agent_demostraion(reporter, agent, env):
    _, state = env.reset([]) 

    print(state)

    for i in range(5):
        adj_parameters = {
            "steer": {'value': 0}
        }
        time, state = env.step(adj_parameters)
    
        print(state)
        print(time)

    # while not done:
    #     state = np.reshape(state, [1, len(state)])

    #     # action, step
    #     noise = agent.ou_noise(noise)
    #     action = agent.get_action(state, noise)
    #     adj_parameters = {
    #         "steer": {'value': action}
    #     }
    #     next_state, reward, done, _ = env.step(adj_parameters)

    #     # for next_state
    #     score += reward[0]
    #     state = next_state

