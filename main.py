from utils.agent_manager import *
from utils.reporter import *
from utils.env_manager import *
from utils.others import *

import argparse
from datetime import datetime
import json

def main(args):
    reporter = reporter_loader(args.loggerLevel, train_name)

    with open(args.param_path) as f:
        param = json.load(f)
    train_param = param['train_param']
    agent_param = param['agent_param']
    RL_param = param['RL_param']
    
    train_name = args.train_name

    agent = agent_loader(reporter, agent_param, RL_param)
    env = 1

    if args.train:
        reporter.info(f"[INFO] Training started!")
        agent_train(reporter, agent, env, train_param, agent_param, RL_param)
        reporter.info(f"[INFO] Training finished!")
    else:
        reporter.info(f"[INFO] Demostration started!")
        agent_demostraion(reporter, agent, env)
        reporter.info(f"[INFO] Demostration finished!")

    reporter.info(f"[INFO] Terminating process.")

if __name__ == "__main__":
    now = datetime.now()
    now = now.strftime('%m%d%H%M')

    parser = argparse.ArgumentParser(description = "Available Options")
    parser.add_argument('--train_name', type=str,
                        default=now, dest="train_name", action="store",
                        help='trained model would be saved in typed directory')
    parser.add_argument('--loggerLevel', type=str,
                        default='warning', dest='loggerLevel', action="store",
                        help='reporter level [debug, info, warning]')    
    parser.add_argument('--train',
                        default=False, dest='train', action='store_true',
                        help='type this arg to train')
    parser.add_argument('--parameters', type=str,
                        default='./config/ppo_ver1.json', dest='param_path', action="store",
                        help='type path of train parameters file (json)')

    args = parser.parse_args()

    main(args)