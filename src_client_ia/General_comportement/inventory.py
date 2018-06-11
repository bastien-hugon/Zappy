#!/usr/bin/env python3


def look_inventory(socket):
    socket.Inventory()
    resp = []
    while (len(resp) == 0):
        resp = socket.ReadSocket()
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
