import torch
from torch import nn
import numpy as np
import matplotlib.pyplot as plt

from others import *

# START ========================================
# CONSTANTS ====================================
EPISODE = int(1e4)
EPOCH = int(1e1)
BATCH_SIZE = 256
VALIDATION_SIZE = 32
SAVE_PER_EPISODE = int(EPISODE / 10)
# END ==========================================
# CONSTANTS ====================================

def G(X, c):
    _, y_dot, psi_dot = X
    m_hat, m, x_ddot = c

    return (m_hat - m)/m_hat * (x_ddot - y_dot * psi_dot)

def main():
    m_hat = 1500
    m = 1600
    x_ddot = 1

    device = "cuda" if torch.cuda.is_available() else "cpu"
    model = NN().to(device)
    loss_fn = nn.MSELoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=1e-3)

    loss_list = []

    # VALIDATION
    for episode in range(EPISODE):
        with torch.no_grad():
            X_list = np.random.randn(VALIDATION_SIZE, 3) * 5
            c = np.array([m_hat, m, x_ddot], dtype=np.float32)
            target = G(X_list.T, c.T)    

            X_list = np2tensor(X_list, device)    
            target = np2tensor(target, device)

            pred = model(X_list)
            loss = loss_fn(pred, target).item()
            loss_list.append(loss)

            if loss < loss_list[-1] and episode > EPISODE/2:
                saveONNX(model, device, episode)

        # TRAIN REPORT
        if episode % SAVE_PER_EPISODE == 0:
            print(f"[INFO] EPISODE {episode}, LOSS {loss}")

            fig_name = './fig/loss.png'
            plt.plot(loss_list)
            plt.savefig(fig_name)
            plt.clf()
            print(f"[INFO] LOSS FUNCTION PLOTTED at {fig_name}")

        # EPOCH TRAIN
        for _ in range(EPOCH):
            X_list = np.random.randn(BATCH_SIZE, 3) * 5
            c = np.array([m_hat, m, x_ddot], dtype=np.float32)
            target = G(X_list.T, c.T)    

            X_list = np2tensor(X_list, device)
            target = np2tensor(target, device)

            pred = model(X_list)
            loss = loss_fn(pred, target)

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

    print(f"[INFO] train finished. \nfinal loss: {loss}")
    saveONNX(model, device, "FINAL")
    
if __name__ == '__main__':
    main()