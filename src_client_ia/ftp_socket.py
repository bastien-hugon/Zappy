#!/usr/bin/env python3
# coding: utf-8

import socket
import sys
import time
import errno


class FTPSocket:

    def __init__(self, port, host):
        self.port = port
        self.host = host

        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))

    def TeamName(self, name):
        try:
            self.socket.send((name + "\n").encode())
        except socket.error:
            if (self.SocketRecv()[-1] == "dead"):
                print("YOU'RE DEAD !  ->  ", end="")
            print("Socket Error")
            exit(84)
        except IOError:
            if IOError.errno == errno.EPIPE:
                print("Broken Pipe")
            else:
                print("Other error")

    def Forward(self):
        try:
            self.socket.send("Forward\n".encode())
        except socket.error:
            if (self.SocketRecv()[-1] == "dead"):
                print("YOU'RE DEAD !  ->  ", end="")
            print("Socket Error")
            exit(84)
        except IOError:
            if IOError.errno == errno.EPIPE:
                print("Broken Pipe")
            else:
                print("Other error")

    def Right(self):
        try:
            self.socket.send("Right\n".encode())
        except socket.error:
            if (self.SocketRecv()[-1] == "dead"):
                print("YOU'RE DEAD !  ->  ", end="")
            print("Socket Error")
            exit(84)
        except IOError:
            if IOError.errno == errno.EPIPE:
                print("Broken Pipe")
            else:
                print("Other error")

    def Left(self):
        try:
            self.socket.send("Left\n".encode())
        except socket.error:
            if (self.SocketRecv()[-1] == "dead"):
                print("YOU'RE DEAD !  ->  ", end="")
            print("Socket Error")
            exit(84)
        except IOError:
            if IOError.errno == errno.EPIPE:
                print("Broken Pipe")
            else:
                print("Other error")

    def Look(self):
        try:
            self.socket.send("Look\n".encode())
        except socket.error:
            if (self.SocketRecv()[-1] == "dead"):
                print("YOU'RE DEAD !  ->  ", end="")
            print("Socket Error")
            exit(84)
        except IOError:
            if IOError.errno == errno.EPIPE:
                print("Broken Pipe")
            else:
                print("Other error")

    def Inventory(self):
        try:
            self.socket.send("Inventory\n".encode())
        except socket.error:
            if (self.SocketRecv()[-1] == "dead"):
                print("YOU'RE DEAD !  ->  ", end="")
            print("Socket Error")
            exit(84)
        except IOError:
            if IOError.errno == errno.EPIPE:
                print("Broken Pipe")
            else:
                print("Other error")

    def Broadcast(self, sentence):
        try:
            self.socket.send(("Broadcast " + sentence + "\n").encode())
        except socket.error:
            if (self.SocketRecv()[-1] == "dead"):
                print("YOU'RE DEAD !  ->  ", end="")
            print("Socket Error")
            exit(84)
        except IOError:
            if IOError.errno == errno.EPIPE:
                print("Broken Pipe")
            else:
                print("Other error")

    def Connect_nbr(self):
        try:
            self.socket.send("Connect_nbr\n".encode())
        except socket.error:
            if (self.SocketRecv()[-1] == "dead"):
                print("YOU'RE DEAD !  ->  ", end="")
            print("Socket Error")
            exit(84)
        except IOError:
            if IOError.errno == errno.EPIPE:
                print("Broken Pipe")
            else:
                print("Other error")

    def Fork(self):
        try:
            self.socket.send("Fork\n".encode())
        except socket.error:
            if (self.SocketRecv()[-1] == "dead"):
                print("YOU'RE DEAD !  ->  ", end="")
            print("Socket Error")
            exit(84)
        except IOError:
            if IOError.errno == errno.EPIPE:
                print("Broken Pipe")
            else:
                print("Other error")

    def Eject(self):
        try:
            self.socket.send("Eject\n".encode())
        except socket.error:
            if (self.SocketRecv()[-1] == "dead"):
                print("YOU'RE DEAD !  ->  ", end="")
            print("Socket Error")
            exit(84)
        except IOError:
            if IOError.errno == errno.EPIPE:
                print("Broken Pipe")
            else:
                print("Other error")

    def Take(self, item):
        try:
            self.socket.send(("Take " + item + "\n").encode())
        except socket.error:
            if (self.SocketRecv()[-1] == "dead"):
                print("YOU'RE DEAD !  ->  ", end="")
            print("Socket Error")
            exit(84)
        except IOError:
            if IOError.errno == errno.EPIPE:
                print("Broken Pipe")
            else:
                print("Other error")

    def Set(self, item):
        try:
            self.socket.send(("Set " + item + "\n").encode())
        except socket.error:
            if (self.SocketRecv()[-1] == "dead"):
                print("YOU'RE DEAD !  ->  ", end="")
            print("Socket Error")
            exit(84)
        except IOError:
            if IOError.errno == errno.EPIPE:
                print("Broken Pipe")
            else:
                print("Other error")

    def Incantation(self):
        try:
            self.socket.send("Incantation".encode())
        except socket.error:
            if (self.SocketRecv()[-1] == "dead"):
                print("YOU'RE DEAD !  ->  ", end="")
            print("Socket Error")
            exit(84)
        except IOError:
            if IOError.errno == errno.EPIPE:
                print("Broken Pipe")
            else:
                print("Other error")

    def SocketRecv(self):
        buffer = ""
        data = ""
        ret_list = []
        keep = -1
        while len(buffer) != keep:
            try:
                data = ftp.socket.recv(1024)
            except socket.error:
                print("Socket Error")
                exit(84)
            except IOError:
                if IOError.errno == errno.EPIPE:
                    print("Broken Pipe")
                else:
                    print("Other error")
            if data:
                buffer += repr(data)[2:-1]
                keep = len(buffer)
        ret_list = buffer.split('\\n')
        i = 0
        while i < len(ret_list):
            if (len(ret_list[i]) <= 1):
                ret_list.pop(i)
                i -= 1
            i += 1
        return ret_list

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
time.sleep(1)
print(ftp.SocketRecv())
ftp.Inventory()
time.sleep(1)
ftp.Forward()
time.sleep(0.1)
