#!/usr/bin/env python3

#
# EPITECH PROJECT, 2018
# PSU_zappy_2017
# File description:
# socket
#

import sockets
import time
import queue
from threading import Thread

from ReadServerThread import ReadOnServer
from General_comportement.check_dead import check_dead


class Socket:

    def __init__(self, host, port, name):
        self.port = port
        self.host = host
        self.name = name
        self.queue = queue.Queue()
        self.init_socket()
        # self.ReadingThread = ReadOnServer(self.fd, self.queue)
        # self.ReadingThread.setDaemon(True)
        # self.ReadingThread.start()
        response = []
        while (len(response) == 0):
            response = self.ReadSocket()
        self.TeamName()
        response = []
        while (len(response) == 0):
            response = self.ReadSocket()

    def init_socket(self):
        self.fd = sockets.create_socket(self.host, self.port)
        if (self.fd == -1):
            print("Bad socket init")
            exit(84)

    def TeamName(self):
        sockets.send_command(self.name, self.fd)

    def Inventory(self):
        sockets.send_command("Inventory", self.fd)

    def Forward(self):
        sockets.send_command("Forward", self.fd)

    def Right(self):
        sockets.send_command("Right", self.fd)

    def Left(self):
        sockets.send_command("Left", self.fd)

    def Look(self):
        sockets.send_command("Look", self.fd)

    def Broadcast(self, sentence):
        sockets.send_command(("Broadcast " + sentence), self.fd)

    def Connect_nbr(self):
        sockets.send_command("Connect_nbr", self.fd)

    def Fork(self):
        sockets.send_command("Fork", self.fd)

    def Eject(self):
        sockets.send_command("Eject", self.fd)

    def Take(self, item):
        sockets.send_command(("Take " + item), self.fd)

    def Set(self, item):
        sockets.send_command(("Set " + item), self.fd)

    def Incantation(self):
        sockets.send_command("Incantation", self.fd)

    def GetServerResponse(self):
        ret = []
        if (self.queue.empty()):
            return ([])
        else:
            while (not self.queue.empty()):
                ret.append(self.queue.get_nowait())
            return (ret)

    def ReadSocket(self):
        command = sockets.get_fd_activity(self.fd).split('\n')
        return (command)

    def EmptyCache(self):
        resp = []
        while (len(resp) == 0):
            resp = self.ReadSocket()
            check_dead(resp)
        print(resp)
        return (resp)
