import socket
import time
import sys, string, os

class CM_dict():
    def __init__(self, dictName, dictType) -> None:
        self.name = dictName
        self.type = dictType
        self.data = None
        self.read_msg = f"expr {$Qu}"

class CM_Manager():
    def __init__(self) -> None:
        pass

    def connectCM(self):
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
        pass

