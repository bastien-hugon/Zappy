#!/usr/bin/env python3

from General_comportement.broadcast import EmptyCacheIgnoreBroadcast
from General_comportement.language import EmptyCacheSearchBroadcast


#
# @brief: Function that move to the wanted tile
#
# @param: nb_forward [in], int, number of forward move you should realize
# @param: nb_side [in], int, number of side move you should realize
# @param: socket [in], socket class to ask requests to the server
# @param: lvl [in], int, the actual level of the A.I.
#
# @return: None
#
def go_to_tile(nb_forward, nb_side, socket, lvl):
    for i in range(nb_forward):
        socket.Forward()
        resp, level = EmptyCacheIgnoreBroadcast(socket, lvl)
        if level != lvl:
            return level
    if (nb_side < 0):
        socket.Left()
        resp, level = EmptyCacheIgnoreBroadcast(socket, lvl)
        if level != lvl:
            return level
    elif (nb_side > 0):
        socket.Right()
        resp, level = EmptyCacheIgnoreBroadcast(socket, lvl)
        if level != lvl:
            return level
    nb_side = abs(nb_side)
    for i in range(nb_side):
        socket.Forward()
        resp, level = EmptyCacheIgnoreBroadcast(socket, lvl)
        if level != lvl:
            return level


#
# @brief: Function that calculate the number of tiles to go
# on the sides and on the front
#
# @param: tile [in], int, index of the wanted tile returned by look
# @param: level [in], int, the actual level of the A.I.
# @param: socket [in], socket class to ask requests to the server
#
# @return: None
#
def mov_to_tile(tile, level, socket):
    if (tile == 0):
        return
    nb_forward = 0
    for x in range(level + 1):
        if (tile >= (x * (x + 1) - x) and tile <= (x * (x + 1) + x)):
            nb_forward = x
    nb_side = tile - (nb_forward * (nb_forward + 1))
    lvl = go_to_tile(nb_forward, nb_side, socket, level)


#
# @brief: Function that moves acording to the calculation done previously.
# This function also listens for any wanted broadcast
#
# @param: nb_forward [in], The numer of steps forward the player needs to do
# @param: nb_side [in], the number of step the player has to do once he turned
# @param: socket [in], socket class variable to interact with socket class
# @param: level [in], the current level of the player
#
# @return: dire, the direction of where the message came from, -1 if no message
# @return: mess, the content of the message, empty list if no message
#
def go_to_tile_search_broadcast(nb_forward, nb_side, socket, lvl):
    for i in range(nb_forward):
        socket.Forward()
        dire, mess, resp, level = EmptyCacheSearchBroadcast(socket, lvl)
        if level != lvl:
            return dire, mess, level
        if dire != -1 and lvl != 1:
            return dire, mess, lvl
    if (nb_side < 0):
        socket.Left()
        dire, mess, resp, level = EmptyCacheSearchBroadcast(socket, lvl)
        if level != lvl:
            return dire, mess, level
        if dire != -1 and lvl != 1:
            return dire, mess, lvl
    elif (nb_side > 0):
        socket.Right()
        dire, mess, resp, level = EmptyCacheSearchBroadcast(socket, lvl)
        if level != lvl:
            return dire, mess, level
        if dire != -1 and lvl != 1:
            return dire, mess, lvl
    nb_side = abs(nb_side)
    for i in range(nb_side):
        socket.Forward()
        dire, mess, resp, level = EmptyCacheSearchBroadcast(socket, lvl)
        if level != lvl:
            return dire, mess, level
        if dire != -1 and lvl != 1:
            return dire, mess, lvl
    return -1, [], lvl


#
# @brief: Function calculates the number of steps we need to do to go to
# the wanted square.
# This function also listens for any wanted broadcast
#
# @param: tile [in], the tile number where we need to go
# @param: socket [in], socket class variable to interact with socket class
# @param: level [in], the current level of the player
#
# @return: dire, the direction of where the message came from, -1 if no message
# @return: mess, the content of the message, empty list if no message
#
def mov_to_tile_search_broadcast(tile, level, socket):
    if (tile == 0):
        return -1, [], level
    nb_forward = 0
    for x in range(level + 1):
        if (tile >= (x * (x + 1) - x) and tile <= (x * (x + 1) + x)):
            nb_forward = x
    nb_side = tile - (nb_forward * (nb_forward + 1))
    dire, mess, lvl = go_to_tile_search_broadcast(nb_forward, nb_side, socket,
                                                  level)
    if level != lvl:
        return dire, mess, lvl
    if dire != -1 and level != 1:
        return dire, mess, level
    return -1, [], level


#
# @brief: Function that allow an A.I. to follow a broadcast thanks
# to its direction
#
# @param: direction [in], the direction where the broadcast came from
# @param: socket [in], socket class variable to interact with socket class
# @param: lvl [in], the current level of the player
#
# @return: dire, the direction of where the message came from, -1 if no message
# @return: mess, the content of the message, empty list if no message
#
def movToBroadcast(direction, socket, lvl):
    print("MOVE TO INCANT")
    ListActions = [['wait'],
                   ['forward'],
                   ['forward', 'left', 'forward'],
                   ['left', 'forward'],
                   ['left', 'forward', 'left', 'forward'],
                   ['right', 'right', 'forward'],
                   ['right', 'forward', 'right', 'forward'],
                   ['right', 'forward'],
                   ['forward', 'right', 'forward']]
    for action in ListActions[direction]:
        if action == 'forward':
            socket.Forward()
            dire, mess, resp, level = EmptyCacheSearchBroadcast(socket, lvl)
            if level != lvl:
                return dire, mess, level
        elif (action == 'left'):
            socket.Left()
            dire, mess, resp, level = EmptyCacheSearchBroadcast(socket, lvl)
            if level != lvl:
                return dire, mess, level
        elif (action == 'right'):
            socket.Right()
            dire, mess, resp, level = EmptyCacheSearchBroadcast(socket, lvl)
            if level != lvl:
                return dire, mess, level
        else:
            return -1, [], lvl
    return -1, [], lvl
