import torch
from torch import nn
import numpy as np
import matplotlib.pyplot as plt

class NN(nn.Module):
    def __init__(self) -> None:
        super().__init__()
        self.fc = nn.Sequential(
            nn.Linear(3, 64),
            nn.ReLU(),
            nn.Linear(64, 32),
            nn.ReLU(),
            nn.Linear(32, 16),
            nn.ReLU(),
            nn.Linear(16, 1),
        )

    def forward(self, x):
        x = self.fc(x)
        return x

def F(X):
    x1, x2, u = X
    return np.sin(x1) + np.sin(x2/2+np.pi/3) + 2*np.sin(u/6+np.pi/6)

def G(X):
    x1, x2, u = X
    return 1/3*np.sin(x1/3+np.pi) + 1/2*np.sin(x2) + 1/5*np.sin(u/3)

def main():
    model = NN()
    loss_fn = nn.MSELoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=1e-3)
    lossList = []

    for epoch in range(1000):
        X_list = np.random.randn(1, 64, 3)
        # dataSet = F(X_list) + G(X_list)

        # train
        target = G(X_list[0].T)
        # X_list = np.reshape(X_list, [1, 3, 64])
        X_list = np.array(X_list, dtype=np.float32)        
        X_list = torch.as_tensor(X_list)
        target = np.array(target, dtype=np.float32)        
        target = torch.as_tensor(target)
        pred = model(X_list)
        target = np.reshape(target, [1, 64, 1])

        # print(pred.shape)
        # print(target.shape)
        loss = loss_fn(pred, target)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        with torch.no_grad():
            X_list = np.random.randn(1, 16, 3)
            target = G(X_list[0].T)
            # X_list = np.reshape(X_list, [1, 3, 16])
            X_list = np.array(X_list, dtype=np.float32)
            X_list = torch.as_tensor(X_list)    
            target = np.array(target, dtype=np.float32)        
            target = torch.as_tensor(target)     
            target = np.reshape(target, [1, 16, 1])
   
            pred = model(X_list)
            loss = loss_fn(pred, target).item()
            print(f"loss: {loss}")
            lossList.append(loss)



    plt.plot(lossList)
    plt.show()
    
if __name__ == '__main__':
    main()