import torch
from torch import nn
import numpy as np
import matplotlib.pyplot as plt
import os
from time import time, localtime, strftime


from others import *
from reporter import *

raw_csv_dir = "0420_0459PM"

# Cf = 435.418/0.296296;
# Cr = 756.349/(0.6*pi/180);
# m = 1644.80;
# Iz = 2488.892;
# lf = 1.240;
# lr = 1.510;
# w = 0.8;

# START ========================================
# CONSTANTS ====================================
Ca = 756.349/(0.6*np.pi/180)
l = 1.240
m = 1644.80

EPISODE = int(1e3)
EPOCH = int(1e3)
BATCH_SIZE = 128
VALIDATION_SIZE = 16
SAVE_START = int(1)
PLOT_PER_EPISODE = int(1)
# END ==========================================
# CONSTANTS ====================================

# known function
# sample_data = [ax vx vy yawRate FRL FRR StrAng] ->  7

def F(sample):
    # [vx, vy, yawRate, Frl, Frr, StrAng] = sample

    vx = sample[:,0]
    vy = sample[:,1]    
    yawRate = sample[:,2]
    Frl = sample[:,3]
    Frr = sample[:,4]
    StrAng = sample[:,5]
    
    Fxf = 0
    # vx = np.where(vx > 1e-5, vx, 1e-5)
    # Fyf = 2 * Ca * (StrAng - np.arctan2((vy+l*yawRate), vx))
    Fyf = 2 * Ca * (StrAng - ((vy+l*yawRate)/ vx))


    x_dot = ((Fxf * np.cos(StrAng) - Fyf * np.sin(StrAng)) + Frl+Frr) * 1/m + yawRate*vy
    return x_dot

def main():
    # reporter config
    cur_dir = os.getcwd()
    cur_time = strftime("%m%d_%I%M%p", localtime(time()))
    log_name = cur_time + ".log"
    reporter = reporter_loader("info", log_name)

    # dataset load
    # raw_csv = os.listdir("raw_csv_dir/" + raw_csv_dir)
    raw_csv = "0421_0641PM0.csv"
    # dataset = [csv2dataset(csv_file) for csv_file in raw_csv]
    # dataset = np.concatenate(dataset, axis=1)
    dataset = csv2dataset(raw_csv)
    np.random.shuffle(dataset[0])
    [sample_num, _] = dataset.shape

    test_dataset = dataset[0:int(sample_num*0.1), :]
    train_dataset = dataset[int(sample_num*0.1):, :]

    # Trainer Setting
    device = "cuda" if torch.cuda.is_available() else "cpu"
    model = NN().to(device)
    print(f"device({device}) is working")
    loss_fn = nn.MSELoss()
   
    optimizer = torch.optim.Adam(model.parameters(), lr=1e-3)
    loss_list = []

    try: 
        # VALIDATION
        for episode in range(EPISODE):
            with torch.no_grad():
                random_pick = np.random.choice(len(test_dataset), VALIDATION_SIZE)
                val_data = test_dataset[random_pick,:]
                target = val_data[:,0]
                input_data = val_data[:,1:]
                analystic_target = F(input_data)

                target = target-analystic_target

                X_list = np2tensor(input_data, device)    
                target = np2tensor(target, device)

                pred = model(X_list)
                loss = torch.sqrt(loss_fn(pred, target)).item()
                loss_list.append(loss)

                if loss < loss_list[-1] and episode > SAVE_START:
                    saveONNX(model, device, episode)

            # TRAIN REPORT
            if episode % PLOT_PER_EPISODE == 0:
                print(f"[INFO] EPISODE {episode}, LOSS {loss}")

                fig_name = './fig/loss.png'
                plt.plot(loss_list)
                plt.savefig(fig_name)
                plt.clf()
                print(f"[INFO] LOSS FUNCTION PLOTTED at {fig_name}")

            # EPOCH TRAIN
            for _ in range(EPOCH):
                random_pick = np.random.choice(len(train_dataset), BATCH_SIZE)
                train_data = train_dataset[random_pick,:]
                target = train_data[:,0]
                input_data = train_data[:,1:]
                analystic_target = F(input_data)

                target = target-analystic_target

                X_list = np2tensor(input_data, device)    
                target = np2tensor(target, device)

                pred = model(X_list)
                loss = torch.sqrt(loss_fn(pred, target))

                optimizer.zero_grad()
                loss.backward()
                optimizer.step()

    finally:
        print(f"[INFO] train finished. \nfinal loss: {loss}")
        saveONNX(model, device, "FINAL")

if __name__ == '__main__':
    main()