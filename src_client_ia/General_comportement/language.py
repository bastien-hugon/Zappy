#!/usr/bin/env python3

# message format: "message [square], [id]:[keyword]:[argv]"


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
# @brief: Function that configures the message to send to server for COMING
# broadcast
#
# @param: socket [in], socket class variable to interact with socket class
# @param: _id [in], string, the _id of the current objectif
#
# @return: None
#
def SendOutBroadcast(socket, _id):
    socket.Broadcast(socket.id + ":OUT:" + _id)


#
# @brief: Function that configures the message to send to server for COMING
# broadcast
#
# @param: socket [in], socket class variable to interact with socket class
# @param: id_list [in], string, the _id of the current objectif
#
# @return: None
#
def SendIncantacceptBroadcast(socket, id_list):
    socket.Broadcast(socket.id + ":INCANTACCEPT:" + id_list)


#
# @brief: Function that configures the message to send to server for COMING
# broadcast
#
# @param: socket [in], socket class variable to interact with socket class
# @param: id_list [in], string, the _id of the current objectif
#
# @return: None
#
def SendIncantrefuseBroadcast(socket, id_list):
    socket.Broadcast(socket.id + ":INCANTREFUSE:" + id_list)


#
# @brief: Function that configures the message to send to server for COMING
# broadcast
#
# @param: socket [in], socket class variable to interact with socket class
# @param: _id [in], string, the _id of the current objectif
#
# @return: None
#
def SendHereBroadcast(socket, _id):
    socket.Broadcast(socket.id + ":HERE:" + _id)


#
# @brief: Function that configures the message to send to server for INCANT
# broadcast
#
# @param: socket [in], socket class variable to interact with socket class
# @param: lvl [in], int, the current level of the player
#
# @return: None
#
def SendStartingBroadcast(socket, lvl):
    socket.Broadcast(socket.id + ":STARTING:" + str(lvl))


def parse_message(socket, message, lvl):
    possible_messages = [
        "INCANT",
        "COMING",
        "OUT",
        "INCANTACCEPT",
        "INCANTREFUSE",
        "HERE",
        "STARTING"
    ]
    split_message = message.split(' ')
    message_type = split_message[-1].split(':')
    if len(message_type) > 1 and message_type[0] in possible_messages:
        return (int(split_message[1]), message_type)
    return -1, [None]


def EmptyCacheSearchBroadcast(socket, lvl, what):
    message = []
    direction = 0
    keep = 0
    store_direction = -1
    while (len(resp) == 0):
        resp = socket.ReadSocket()
        for i in range(len(resp)):
            if "message" in resp[i] and keep == 0:
                direction, message = parse_message(socket, resp[i], lvl)
                if (message[0] == what):
                    keep = 1
            del resp[i]
            store_direction = direction
    return direction, message, resp
