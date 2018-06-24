#!/usr/bin/env python3

import re

from General_comportement.check_dead import check_dead
from General_comportement.broadcast import EmptyCacheIgnoreBroadcast


#
# @brief: Function that configures the message to send to server for INCANT
# broadcast
#
# @param: socket [in], socket class variable to interact with socket class
# @param: lvl [in], int, the current level of the player
#
# @return: None
#
def SendIncantBroadcast(socket, lvl):
    socket.Broadcast(socket.id + ":INCANT:" + str(lvl))


#
# @brief: Function that configures the message to send to server for COMING
# broadcast
#
# @param: socket [in], socket class variable to interact with socket class
# @param: _id [in], string, the _id of the current objectif
#
# @return: None
#
def SendComingBroadcast(socket, _id):
    socket.Broadcast(socket.id + ":COMING:" + _id)


#
# @brief: Function that configures the message to send to server for OUT
# broadcast
#
# @param: socket [in], socket class variable to interact with socket class
# @param: _id [in], string, the _id of the current objectif
#
# @return: None
#
def SendOutBroadcast(socket):
    socket.Broadcast(socket.id + ":OUT:" + socket.target_id[0])


#
# @brief: Function that configures the message to send to server for
# INCANTACCEPT broadcast
#
# @param: socket [in], socket class variable to interact with socket class
# @param: _id [in], string, the _id of the current objectif
#
# @return: None
#
def SendIncantacceptBroadcast(socket, _id):
    socket.Broadcast(socket.id + ":INCANTACCEPT:" + _id)


#
# @brief: Function that configures the message to send to server for
# INCANTREFUSE broadcast
#
# @param: socket [in], socket class variable to interact with socket class
# @param: _id [in], string, the _id of the current objectif
#
# @return: None
#
def SendIncantrefuseBroadcast(socket, _id):
    socket.Broadcast(socket.id + ":INCANTREFUSE:" + _id)


#
# @brief: Function that configures the message to send to server for HERE
# broadcast
#
# @param: socket [in], socket class variable to interact with socket class
# @param: _id [in], string, the _id of the current objectif
#
# @return: None
#
def SendIncanthereBroadcast(socket, lvl):
    socket.Broadcast(socket.id + ":HERE:" + str(lvl))


#
# @brief: Function that parses the broadcast message
#
# @param: socket [in], socket class variable to interact with socket class
# @param: message [in], int, the current level of the player
# @param: lvl [in], the current level of the player
#
# @return: direction, message. The directino is where the message came from,
# the message is the cut up message to be executed later
#
def parse_message(socket, message):
    possible_messages = [
        "INCANT",
        "COMING",
        "OUT",
        "INCANTACCEPT",
        "INCANTREFUSE",
        "HERE"
    ]
    split_message = message.split(' ')
    message_type = split_message[-1].split(':')
    if len(message_type) >= 3 and message_type[1] in possible_messages:
        return (int(split_message[1][:-1]), message_type)
    return -1, []


#
# @brief: Function that configures the message to send to server for INCANT
# broadcast
#
# @param: socket [in], socket class variable to interact with socket class
# @param: lvl [in], int, the current level of the player
#
# @return: direction, message. The direction is where the message came from,
# the message is the cut up message to be executed later
#
def EmptyCacheSearchBroadcast(socket, lvl):
    mess = []
    dire = -1
    message = []
    direction = -1
    incant = False
    resp = []
    while (len(resp) == 0):
        resp = socket.ReadSocket()
        check_dead(resp)
        i = 0
        while i < len(resp):
            if resp[i].find("message") != -1 or resp[i].find("Elevation underway") != -1:
                direction, message = parse_message(socket, resp[i])
                if len(message) >= 3 and message[1] == "INCANT" and int(message[2]) == lvl and dire == -1:
                    dire = direction
                    mess = message
                    keep = 1
                resp.pop(i)
            elif resp[i].find("Elevation underway") != -1:
                incant = True
                resp.pop(i)
            elif resp[i].find("Current level:") != -1:
                print("FOUND CURRENT LEVEL")
                ret = re.findall('\d+', resp[i])
                if len(ret) > 0:
                    if int(ret[0]) != lvl:
                        return dire, mess, resp, int(ret[0])
            else:
                i += 1
    if incant is True:
        ret_incant, level = EmptyCacheIgnoreBroadcast(socket, lvl)
        if (level != lvl):
            return dire, mess, resp, level
        for response in ret_incant:
            if "Current level:" in response:
                ret = re.findall('\d+', response)
                if len(ret) > 0:
                    if int(ret[0]) != lvl:
                        return dire, mess, resp, int(ret[0])
        return dire, mess, resp, lvl
    print("FOCUSBROADCAST resp = " + str(resp) + " mess = " + str(mess) + " dire = " + str(dire))
    return dire, mess, resp, lvl


#
# @brief: Function that configures the message to send to server for INCANT
# broadcast
# This function focuses a scecific id of broadcast message
#
# @param: socket [in], socket class variable to interact with socket class
# @param: lvl [in], int, the current level of the player
#
# @return: direction, message. The direction is where the message came from,
# the message is the cut up message to be executed later
#
def EmptyCacheFocusBroadcast(socket, lvl):
    mess = []
    dire = -1
    message = []
    direction = -1
    incant = False
    resp = []
    while (len(resp) == 0):
        resp = socket.ReadSocket()
        check_dead(resp)
        i = 0
        while i < len(resp):
            if resp[i].find("message") != -1:
                direction, message = parse_message(socket, resp[i])
                print("ID DIFFERENCE " + str(socket.target_id) + " ?= " + str(message[0]))
                if (len(message) >= 3 and message[1] == "INCANT" and int(message[2]) == lvl and socket.target_id == message[0]):
                    dire = direction
                    mess = message
                    keep = 1
                resp.pop(i)
            elif resp[i].find("Elevation underway") != -1:
                incant = True
                resp.pop(i)
            elif resp[i].find("Current level:") != -1:
                print("FOUND CURRENT LEVEL")
                ret = re.findall('\d+', resp[i])
                if len(ret) > 0:
                    if int(ret[0]) != lvl:
                        return dire, mess, resp, int(ret[0])
            else:
                i += 1
    if incant is True:
        ret_incant, level = EmptyCacheIgnoreBroadcast(socket, lvl)
        if (level != lvl):
            return dire, mess, resp, level
        for response in ret_incant:
            if "Current level:" in response:
                ret = re.findall('\d+', response)
                if len(ret) > 0:
                    if int(ret[0]) != lvl:
                        return dire, mess, resp, int(ret[0])
        return dire, mess, resp, lvl
    print("FOCUSBROADCAST resp = " + str(resp) + " mess = " + str(mess) + " dire = " + str(dire))
    return dire, mess, resp, lvl
