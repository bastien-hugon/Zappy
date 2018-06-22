#!/usr/bin/env python3

from General_comportement.broadcast import EmptyCacheIgnoreBroadcast


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
