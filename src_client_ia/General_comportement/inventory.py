#!/usr/bin/env python3

from General_comportement.check_dead import check_dead


def look_inventory(socket):
    socket.Inventory()
    resp = []
    while (len(resp) == 0):
        resp = socket.ReadSocket()
        print ("look_inventory: " + str(resp))
        check_dead(resp)
    if len(resp) > 0 and resp[0] != "ko":
        resp[0] = resp[0][2:-2].split(', ')
    return (resp)


def get_food(inventory):
    ret = []
    for i in (inventory[0]):
        if (i[:4] == 'food'):
            ret = [int(s) for s in i if s.isdigit()]
    if len(ret) > 0:
        return (ret[0])
    else:
        return (0)


def get_linemate(inventory):
    ret = []
    for i in (inventory[0]):
        if (i[:8] == 'linemate'):
            ret = [int(s) for s in i if s.isdigit()]
    if len(ret) > 0:
        return (ret[0])
    else:
        return (0)
