from reporter import *

from time import strftime, localtime, time
import sys
import os
import numpy as np
#import telnetlib # when you use dSpace products

sys.path.append("/opt/ipg/carmaker/linux64-12.0/Python/python3.9")
from ASAM.XIL.Implementation.Testbench import TestbenchFactory
from ASAM.XIL.Interfaces.Testbench.MAPort.Enum.MAPortState import MAPortState
from ASAM.XIL.Interfaces.Testbench.Common.Error.TestbenchPortException import TestbenchPortException


def main():
    DemoMAPort = None

    # rec config
    simtime = 100.0
    trg_testrun = "demo1"
    rec_num = 1
    down_sample_rate = 10
    var_list = [
        "Time", 
        "Car.ax", "Car.ay", "Car.YawAcc",
        "Car.vx", "Car.vy", "Car.YawRate",
        # "Car.Aero.Frx_1.x",
        # "Car.WheelSpd_FL", "Car.WheelSpd_FR", "Car.WheelSpd_RL", "Car.WheelSpd_RR",
        # "Car.FxFL", "Car.FxFR", "Car.FxRL", "Car.FxRR",
        # "Car.FyFL", "Car.FyFR", 
        "Car.FyRL", "Car.FyRR",
        "VC.Steer.Ang"
        ]

    # reporter config
    cur_dir = os.getcwd()
    cur_time = strftime("%m%d_%I%M%p", localtime(time()))
    log_name = cur_time + ".log"
    reporter = reporter_loader("info", log_name)

    # MAPort config
    MAPortConfigFile = "Config.xml"

    try:
        # Initialize all necessary class instances
        reporter.info("Initializing all necessary class instances")
        MyTestbenchFactory = TestbenchFactory()
        MyTestbench = MyTestbenchFactory.CreateVendorSpecificTestBench("IPG", "CarMaker", "12.0")
        MyMAPortFactory = MyTestbench.MAPortFactory
        MyWatcherFactory = MyTestbench.WatcherFactory

        reporter.info("Creating and Configuring MAPort...")
        DemoMAPort = MyMAPortFactory.CreateMAPort("DemoMAPort")

        # Start CarMaker instance using a Project directory as Configuration parameter
        DemoMAPortConfig = DemoMAPort.LoadConfiguration(MAPortConfigFile)
        DemoMAPort.Configure(DemoMAPortConfig, False)

        # SIM ============================================================================================
        for i in range(rec_num):
            # Capture config
            DemoCapture = DemoMAPort.CreateCapture("captureTask")
            DemoCapture.Variables = var_list
            DemoCapture.Downsampling = down_sample_rate 

            reporter.info("Starting simulation...")
            if DemoMAPort.State is not MAPortState.eSIMULATION_RUNNING:
                # DemoMAPort.StartSimulation("Examples/BasicFunctions/Driver/BackAndForth")
                DemoMAPort.StartSimulation(trg_testrun)
                DemoCapture.Start()

            # Stop simulation
            # DemoMAPort.StopSimulation()
            # DemoMAPort.WaitForSimEnd(20.0)
            DemoMAPort.WaitForTime(simtime)
            DemoMAPort.StopSimulation()

            reporter.info("Terminating simulation...")

            capture_result = DemoCapture.Fetch(False)
            DemoCapture.Stop()
            # SIM ============================================================================================
                
                # data proccessing
            result = []
            for trg_var in var_list:
                tmp = capture_result.ExtractSignalValue(trg_var)
                result.append(tmp.FcnValues.Value)

            result = np.array(result)
                # size: (var_number, sample_number)
            
            csv_name = cur_dir + "/results/" + cur_time + str(i) + ".csv"
            np.savetxt(csv_name, result)

    except TestbenchPortException as ex:
        reporter.warning("TestbenchPortException occured:")
        reporter.warning("VendorCodeDescription: %s" % ex.VendorCodeDescription)

    finally:
        if DemoMAPort != None:
            DemoMAPort.Dispose()
            DemoMAPort = None

if __name__ == "__main__":
    main()