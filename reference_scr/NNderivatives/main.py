import torch
from torch import nn
import numpy as np
import matplotlib.pyplot as plt

class NN(nn.Module):
    def __init__(self) -> None:
        super().__init__()
        self.fc = nn.Sequential(
            nn.Linear(3, 100),
            nn.ReLU(),
            nn.Linear(100, 100),
            nn.ReLU(),
            nn.Linear(100, 100),
            nn.ReLU(),
            nn.Linear(100, 1)
        )

    def forward(self, x):
        x = self.fc(x)
        return x

def G(X):
    x1, x2, u = X
    return 1/3*np.sin(x1/3+np.pi) + 1/2*np.sin(x2) + 1/5*np.sin(u/3)

def dG(X):
    x1, x2, u = X
    return [1/3*1/3*np.cos(x1/3+np.pi), 1/2*np.cos(x2), 1/5*1/3*np.cos(u/3)]

def main():
    model = NN()
    loss_fn = nn.MSELoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=1e-3)
    lossList = []

    for epoch in range(100000):
        X_list = np.random.randn(1, 256, 3) * 5
        # dataSet = F(X_list) + G(X_list)

        # train
        target = G(X_list[0].T)
        # X_list = np.reshape(X_list, [1, 3, 64])
        X_list = np.array(X_list, dtype=np.float32)        
        X_list = torch.as_tensor(X_list)
        target = np.array(target, dtype=np.float32)        
        target = torch.as_tensor(target)
        pred = model(X_list)
        target = np.reshape(target, [1, 256, 1])

        # print(pred.shape)
        # print(target.shape)
        loss = loss_fn(pred, target)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        with torch.no_grad():
            X_list = np.random.randn(1, 32, 3) * 5
            target = G(X_list[0].T)
            # X_list = np.reshape(X_list, [1, 3, 16])
            X_list = np.array(X_list, dtype=np.float32)
            X_list = torch.as_tensor(X_list)    
            target = np.array(target, dtype=np.float32)        
            target = torch.as_tensor(target)     
            target = np.reshape(target, [1, 32, 1])
   
            pred = model(X_list)
            loss = loss_fn(pred, target).item()
            # print(f"loss: {loss}")
            lossList.append(loss)

        if epoch % 1000 == 0:
            X_list = np.arange(2,4,0.001)

            y_list = []
            NN_y_list = []

            for x in X_list:
                X = np.array([[1.,1.,x]], dtype=np.float32)
                X = torch.tensor(X, requires_grad=True)

                target = dG((X[0].detach().numpy()))
                y_list.append(np.dot(target, X[0].T.detach().numpy()))

                pred = model(X)
                pred.backward()

                NN_y_list.append(np.dot(X.grad.detach().numpy(), X[0].T.detach().numpy()))

            plt.plot(X_list, y_list, X_list, NN_y_list)
            plt.savefig(str(epoch) + '.png')
            plt.clf()

            print(f"EPOCH {epoch}, LOSS {loss}")

    print(f"[INFO] train finished. \nloss: {loss}")



# a = torch.tensor([1.], requires_grad=True)
# Q = torch.sin(a)
# Q.backward(gradient=torch.tensor([1.]))
# a.grad == np.cos(1.0)

if __name__ == '__main__':
    main()