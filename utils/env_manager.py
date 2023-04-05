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
    def __init__(self, CM_PATH, TCP_IP, TCP_PORT) -> None:
        os.system(f"{CM_PATH} -cmdport {TCP_PORT} &")
        time.system(2)
        
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((TCP_IP, TCP_PORT))
    
    def loadTestRun(self, testRun):
        msg = "LoadTestRun %s" % (testRun)
        self.send(msg)
        time.sleep(500)

    def startTestRun(self):
        pass

    def stopTestRun(self):
        pass

    def subscribe(self, quantity):
        pass

    def read(self):
        pass
    
    def DVA_write(self):
        pass

    def DVA_release(self):
        pass

    def send(self, msg):
        msg = msg + "\r" 
        msg = msg.encode('utf-8')
        self.socket.send(msg)
        time.sleep(1)
        return self.socket.recv(200)

