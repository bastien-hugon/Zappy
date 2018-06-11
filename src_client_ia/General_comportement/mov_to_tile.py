#!/usr/bin/env python3


def go_to_tile(nb_forward, nb_side, socket):
    for i in range(1, (nb_forward) + 1):
        socket.Forward()
    if (nb_side < 0):
        socket.Left()
        nb_forward += 1
    elif (nb_side > 0):
        socket.Right()
        nb_forward += 1
    if (nb_forward > 0):
        resp = []
        while (len(resp) == 0 and nb_forward != 0):
            resp = socket.ReadSocket()
            resp = resp[:1]
            if (len(resp) != 0):
                nb_forward -= len(resp)
    nb_side = abs(nb_side)
    for i in range(1, (nb_side) + 1):
        socket.Forward()
    if (nb_side > 0):
        resp = []
        while (len(resp) == 0 and nb_side != 0):
            resp = socket.ReadSocket()
            resp = resp[:1]
            if (len(resp) != 0):
                nb_side -= len(resp)


def mov_to_tile(tile, level, socket):
    nb_forward = 0
    for x in range(1, (level + 1)):
        if (tile >= (x * (x + 1) - x) and tile <= (x * (x + 1) + x)):
            nb_forward = x
    nb_side = tile - (level * (level + 1) - level)
    go_to_tile(nb_forward, nb_side, socket)
