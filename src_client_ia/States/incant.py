#!/usr/bin/env python3

import random

from General_comportement.ressources import nb_player_here
from General_comportement.ressources import get_all_item_here
from General_comportement.broadcast import EmptyCacheIgnoreBroadcast


def SearchAvailaibleBroadcast(socket, lvl):
    for i in range(random.randint(20, 40)):
        socket.Inventory()
        direction, resp = EmptyCacheInventoryPlusBroadcast(socket, lvl)


def incant(socket):
    socket.Look()
    resp = EmptyCacheIgnoreBroadcast(socket)
    resp = resp[:1]
    if len(resp) > 0 and resp[0] != "ko":
        resp = resp[0][2:-2].split(',')
    if (nb_player_here(resp[0]) == 1):
        get_all_item_here(socket, resp[0])
        socket.Set('linemate')
        EmptyCacheIgnoreBroadcast(socket)
        socket.Incantation()
        resp = EmptyCacheIgnoreBroadcast(socket)
        if (resp[0] == "Elevation underway"):
            socket.EmptyCache()
            if (resp[0] == "ko"):
                return (1)
            else:
                return (2)
        else:
            return (1)
    else:
        socket.EmptyCache()
        return (1)

