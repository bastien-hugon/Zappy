#!/usr/bin/env python3

#
# EPITECH PROJECT, 2018
# PSU_zappy_2017
# File description:
# socket
#

import socket
from socket import error as socket_error
import time
from threading import Thread
import random
import time

from General_comportement.check_dead import check_dead


#
# @brief: class that handles all the socket interaction with the server
#
class SocketInteraction:

    #
    # @brief: Function that inits the class. It inits the C sockets module,
    # it also does the basic "login" of the server (Gets the Welcome and sends
    # team name)
    #
    # @param: host [in], host of the zappy server, given as program argument
    # @param: port [in], port of the zappy server, given as program argument
    # @param: name [in], name of the team that the program will participate in
    #
    # @return: None
    #
    def __init__(self, host, port, name):
        self.port = port
        self.host = host
        self.name = name
        self.init_socket()
        response = []
        while (len(response) == 0):
            response = self.ReadSocket()
            print("Response = " + str(response))
        self.TeamName()
        response = []
        while (len(response) == 0):
            response = self.ReadSocket()
            print("Response = " + str(response))
            for answer in response:
                if "ko" in answer:
                    print("Connection failed")
                    exit(84)
            self.nbplaces = int(response[0])
        if len(response) == 1:
            response = []
            while (len(response) == 0):
                response = self.ReadSocket()
                print("Response = " + str(response))
        self.id = str(self.GenerateRandomId())
        self.target_id = ""

    #
    # @brief: Function that creates the socket and ask for connection
    #
    # @param: self [in], contains class variables
    #
    # @return: EXIT(84) if there is an error
    #
    def init_socket(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.socket.connect((self.host, self.port))
        except socket_error as serr:
            print("Connection Refused !")
            exit(84)

    #
    # @brief: Function that sends the command telling the server the team name
    #
    # @param: self [in], contains class variables
    #
    # @return: None
    #
    def TeamName(self):
        message = (self.name + '\n').encode('utf-8')
        print(message)
        self.socket.send(message)
        # sockets.send_command(self.name, self.fd)

    #
    # @brief: Function that sends the command to get the inventory
    #
    # @param: self [in], contains class variables
    #
    # @return: None
    #
    def Inventory(self):
        message = ("Inventory\n").encode('utf-8')
        print(message)
        self.socket.send(message)
        # sockets.send_command("Inventory", self.fd)

    #
    # @brief: Function that sends the command to go forward
    #
    # @param: self [in], contains class variables
    #
    # @return: None
    #
    def Forward(self):
        message = ("Forward\n").encode('utf-8')
        print(message)
        self.socket.send(message)
        # sockets.send_command("Forward", self.fd)

    #
    # @brief: Function that sends the command to turn right
    #
    # @param: self [in], contains class variables
    #
    # @return: None
    #
    def Right(self):
        message = ("Right\n").encode('utf-8')
        print(message)
        self.socket.send(message)
        # sockets.send_command("Right", self.fd)

    #
    # @brief: Function that sends the command to turn left
    #
    # @param: self [in], contains class variables
    #
    # @return: None
    #
    def Left(self):
        message = ("Left\n").encode('utf-8')
        print(message)
        self.socket.send(message)
        # sockets.send_command("Left", self.fd)

    #
    # @brief: Function that sends the command to look what items are on the
    # floor in front of player
    #
    # @param: self [in], contains class variables
    #
    # @return: None
    #
    def Look(self):
        message = ("Look\n").encode('utf-8')
        print(message)
        self.socket.send(message)
        # sockets.send_command("Look", self.fd)

    #
    # @brief: Function that sends the command to broadcast a message to every
    # player on the map
    #
    # @param: self [in], contains class variables
    # @param: sentence [in], string containing the message to be broadcast
    # to all players
    #
    # @return: None
    #
    def Broadcast(self, sentence):
        message = ("Broadcast " + sentence + '\n').encode('utf-8')
        print(message)
        self.socket.send(message)
        # sockets.send_command(("Broadcast " + sentence), self.fd)

    #
    # @brief: Function that sends the command to know how much free slots
    # is left in the team
    #
    # @param: self [in], contains class variables
    #
    # @return: None
    #
    def Connect_nbr(self):
        message = ("Connect_nbr\n").encode('utf-8')
        print(message)
        self.socket.send(message)
        # sockets.send_command("Connect_nbr", self.fd)

    #
    # @brief: Function that sends the command create an egg thus in term
    # create a new team free slot
    #
    # @param: self [in], contains class variables
    #
    # @return: None
    #
    def Fork(self):
        message = ("Fork\n").encode('utf-8')
        print(message)
        self.socket.send(message)
        # sockets.send_command("Fork", self.fd)

    #
    # @brief: Function that sends the command to eject all players from a tile
    #
    # @param: self [in], contains class variables
    #
    # @return: None
    #
    def Eject(self):
        message = ("Eject\n").encode('utf-8')
        print(message)
        self.socket.send(message)
        # sockets.send_command("Eject", self.fd)

    #
    # @brief: Function that sends the command to take a specified object from
    # the ground
    #
    # @param: self [in], contains class variables
    # @param: item [in], string containing the item that needs to be picked up
    #
    # @return: None
    #
    def Take(self, item):
        message = ("Take " + item + '\n').encode('utf-8')
        print(message)
        self.socket.send(message)
        # sockets.send_command(("Take " + item), self.fd)

    #
    # @brief: Function that sends the command topick up a specified object from
    # the ground
    #
    # @param: self [in], contains class variables
    # @param: item [in], string containing the item that needs to be set down
    #
    # @return: None
    #
    def Set(self, item):
        message = ("Set " + item + '\n').encode('utf-8')
        print(message)
        self.socket.send(message)
        # sockets.send_command(("Set " + item), self.fd)

    #
    # @brief: Function that sends the command to start leveling up
    #
    # @param: self [in], contains class variables
    #
    # @return: None
    #
    def Incantation(self):
        message = ("Incantation\n").encode('utf-8')
        print(message)
        self.socket.send(message)
        # sockets.send_command("Incantation", self.fd)

    #
    # @brief: Function that reads the server socket fd and returns the content
    #
    # @param: self [in], contains class variables
    #
    # @return: command, a string containing what was in the server socket fd
    #
    def ReadSocket(self):
        command = self.socket.recv(16384).decode('utf-8').split('\n')
        del command[-1]
        return (command)

    #
    # @brief: Function that calls the self.ReadSocket() and checks if our
    # player has died
    #
    # @param: self [in], contains class variables
    #
    # @return: resp, a string containing the content of the sever socket fd
    #
    def EmptyCache(self):
        resp = []
        while (len(resp) == 0):
            resp = self.ReadSocket()
            check_dead(resp)
        print("resp = " + str(resp))
        return (resp)

    #
    # @brief: Function that creates a random id of 10 characters
    #
    # @param: self [in], contains class variables
    #
    # @return: resp, a string containing the randomly generated id token
    #
    def GenerateRandomId(self):
        now = time.time()
        coeff = str(float(self.nbplaces * now))
        value = coeff.split('.')
        final = value[0] + value[1] + str(random.randint(100, 999))
        return (final)
