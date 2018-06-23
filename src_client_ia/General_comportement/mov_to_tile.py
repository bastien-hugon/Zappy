#!/usr/bin/env python3

from General_comportement.broadcast import EmptyCacheIgnoreBroadcast
from General_comportement.language import EmptyCacheSearchBroadcast


def go_to_tile(nb_forward, nb_side, socket):
    for i in range(nb_forward):
        socket.Forward()
        EmptyCacheIgnoreBroadcast(socket)
    if (nb_side < 0):
        socket.Left()
        EmptyCacheIgnoreBroadcast(socket)
    elif (nb_side > 0):
        socket.Right()
        EmptyCacheIgnoreBroadcast(socket)
    nb_side = abs(nb_side)
    for i in range(nb_side):
        socket.Forward()
        EmptyCacheIgnoreBroadcast(socket)


def mov_to_tile(tile, level, socket):
    if (tile == 0):
        return
    nb_forward = 0
    for x in range(level + 1):
        if (tile >= (x * (x + 1) - x) and tile <= (x * (x + 1) + x)):
            nb_forward = x
    nb_side = tile - (nb_forward * (nb_forward + 1))
    go_to_tile(nb_forward, nb_side, socket)


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
def go_to_tile_search_broadcast(nb_forward, nb_side, socket, level):
    for i in range(nb_forward):
        socket.Forward()
        dire, mess, resp = EmptyCacheSearchBroadcast(socket, level)
        if dire != -1 and level != 1:
            return dire, mess
    if (nb_side < 0):
        socket.Left()
        dire, mess, resp = EmptyCacheSearchBroadcast(socket, level)
        if dire != -1 and level != 1:
            return dire, mess
    elif (nb_side > 0):
        socket.Right()
        dire, mess, resp = EmptyCacheSearchBroadcast(socket, level)
        if dire != -1 and level != 1:
            return dire, mess
    nb_side = abs(nb_side)
    for i in range(nb_side):
        socket.Forward()
        dire, mess, resp = EmptyCacheSearchBroadcast(socket, level)
        if dire != -1 and level != 1:
            return dire, mess
    return -1, []


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
        return -1, []
    nb_forward = 0
    for x in range(level + 1):
        if (tile >= (x * (x + 1) - x) and tile <= (x * (x + 1) + x)):
            nb_forward = x
    nb_side = tile - (nb_forward * (nb_forward + 1))
    dire, mess = go_to_tile_search_broadcast(nb_forward, nb_side, socket,
                                             level)
    if dire != -1 and level != 1:
        return dire, mess
    return -1, []


def movToBroadcast(direction, socket, level):
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
            dire, mess, resp = EmptyCacheSearchBroadcast(socket, level)
        elif (action == 'left'):
            socket.Left()
            dire, mess, resp = EmptyCacheSearchBroadcast(socket, level)
        elif (action == 'right'):
            socket.Right()
            dire, mess, resp = EmptyCacheSearchBroadcast(socket, level)
        else:
            return (1)
    return (1)
