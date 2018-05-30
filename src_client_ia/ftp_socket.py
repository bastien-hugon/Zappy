#!/usr/bin/env python3
# coding: utf-8

import socket
import sys


class FTPSocket:

    def __init__(self):
        self.port = 4242
        self.host = "127.0.0.1"

        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))

    def SendCommand(self, command):
        self.socket.send(command.encode())

    def __exit__(self):
        self.socket.close()

ftp = FTPSocket()
while True:
    command = input("Input :")
    ftp.SendCommand(command)
