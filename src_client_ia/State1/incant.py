#!/usr/bin/env python3

from General_comportement.ressources import nb_player_here
from General_comportement.ressources import get_all_item_here
from General_comportement.check_dead import check_dead


def incant(socket):
    socket.Look()
    resp = []
    while (len(resp) == 0):
        resp = socket.ReadSocket()
        print ("look: " + str(resp))
    check_dead(resp)
    resp = resp[:1]
    if len(resp) > 0 and resp[0] != "ko":
        resp = resp[0][2:-2].split(',')
    if (nb_player_here(resp[0]) == 1):
        get_all_item_here(socket, resp[0])
        socket.Set('linemate')
        resp = []
        while (len(resp) == 0):
            resp = socket.ReadSocket()
            print ("set: " + str(resp))
        check_dead(resp)
        socket.Incantation()
        resp = []
        while (len(resp) == 0):
            resp = socket.ReadSocket()
            print ("Incant: " + str(resp))
        check_dead(resp)
        if (resp[0] == "Elevation underway"):
            resp = []
            while (len(resp) == 0):
                resp = socket.ReadSocket()
                print ("Incant: " + str(resp))
            check_dead(resp)
            if (resp[0] == "ko"):
                return (1)
            else:
                return (2)
        else:
            return (1)
    else:
        socket.Forward()
        resp = []
        while (len(resp) == 0):
            resp = socket.ReadSocket()
            check_dead(resp)
        return (1)