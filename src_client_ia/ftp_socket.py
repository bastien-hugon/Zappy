#!/usr/bin/env python3
# coding: utf-8

import socket
import sys


class FTPSocket:

    def __init__(self, port, host):
        self.port = port
        self.host = host

        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))

    def TeamName(self, name):
        self.socket.send((name + "\n").encode())

    def Forward(self):
        self.socket.send("Forward\n".encode())

    def Right(self):
        self.socket.send("Right\n".encode())

    def Left(self):
        self.socket.send("Left\n".encode())

    def Look(self):
        self.socket.send("Look\n".encode())

    def Inventory(self):
        self.socket.send("Inventory\n".encode())

    def Broadcast(self, sentence):
        self.socket.send(("Broadcast " + sentence + "\n").encode())

    def Connect_nbr(self):
        self.socket.send("Connect_nbr\n".encode())

    def Fork(self):
        self.socket.send("Fork\n".encode())

    def Eject(self):
        self.socket.send("Eject\n".encode())

    def Take(self, item):
        self.socket.send(("Take " + item + "\n").encode())

    def Set(self, item):
        self.socket.send(("Set " + item + "\n").encode())

    def Incantation(self):
        self.socket.send("Incantation".encode())

    def __exit__(self):
        self.socket.close()

ftp = FTPSocket(4242, "127.0.0.1")
name = "Yellow"
ftp.TeamName(name)
ftp.Look()
ftp.Forward()
ftp.Right()
ftp.Left()
ftp.Look()
ftp.Forward()
ftp.Look()
ftp.Inventory()
buffer = ""
data = ""
while True:
    data = ftp.socket.recv(1024)
    if data:
        buffer += repr(data)[2:-1]
        print(buffer)
    else:
        break
