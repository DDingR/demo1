import socket
import time
import sys, string, os

class CM_dict():
    def __init__(self, dictName, dictType) -> None:
        self.name = dictName
        self.type = dictType
        self.data = None
        self.read_msg = "expr {$Qu(" + self.name + ")}\r"

class CM_Manager():
    def __init__(self, reporter, CM_PATH, TCP_IP, TCP_PORT, testRun) -> None:
        os.system(f"{CM_PATH} -cmdport {TCP_PORT} &")
        time.system(2)
        
        self.reporter = reporter

        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((TCP_IP, TCP_PORT))
        self.reporter.info("CarMaker Connected by TCP Socket")

        self.__loadTestRun(testRun)

    def __send(self, msg):
        msg = msg + "\r" 
        self.socket.__send(msg.encode())
        time.sleep(1)
        return self.socket.recv(200)

    def __waitForStatus(self, status):
        self.__send("WaitForStatus %s" % (status))
        while 1:
            data = self.socket.recv(self.BUFFER_SIZE)
            if '0' in data.decode():
                break

    def __loadTestRun(self, testRun):
        self.reporter.info("Loading testRun: %s" % (testRun))        
        msg = "LoadTestRun %s" % (testRun)
        self.__send(msg)
        time.sleep(500)

    def __startTestRun(self):
        msg = "StartSum"
        self.__send(msg)
        self.__waitForStatus("running")

    def __stopTestRun(self):
        msg = "StopSum"
        self.__send(msg)
        self.__waitForStatus("idle")

    def subscribe(self, quantity):
        pass

    def read(self):
        pass
    
    def DVA_write(self):
        pass

    def DVA_release(self):
        pass


    def reset(self):
        self.__stopTestRun()
        self.__startTestRun()
        pass

    def step(self):
        pass