#!/usr/bin/env python3

from General_comportement.ressources import nb_player_here
from General_comportement.ressources import get_all_item_here


def incant(socket):
    socket.Look()
    resp = socket.EmptyCache()
    resp = resp[:1]
    if len(resp) > 0 and resp[0] != "ko":
        resp = resp[0][2:-2].split(',')
    if (nb_player_here(resp[0]) == 1):
        get_all_item_here(socket, resp[0])
        socket.Set('linemate')
        socket.EmptyCache()
        socket.Incantation()
        resp = socket.EmptyCache()
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
