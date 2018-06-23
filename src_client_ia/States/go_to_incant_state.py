#!/usr/bin/env python3

import re

from General_comportement.broadcast import EmptyCacheIgnoreBroadcast
from General_comportement.inventory import look_inventory_focus_broadcast
from General_comportement.inventory import get_food
from General_comportement.mov_to_tile import movToBroadcast
from General_comportement.language import EmptyCacheFocusBroadcast


def waiting_for_incant(socket, resp, level):
    for _object in resp:
        if ("Current level:" in _object):
            ret = re.findall('\d+', _object)
            if len(ret) > 0:
                if int(ret[0]) != level:
                    return int(ret[0])
    return level


def go_to_incant_state(socket, lvl, food, direction, message):
    level = lvl
    print("MESSAGE " + str(message))
    print("SET TARGET: " + message[0])
    socket.target_id = message[0]
    dire = -1
    mess = []
    while food >= level + 3:
        movToBroadcast(direction, socket, level)
        dire = -1
        while food >= level + 3 and dire == -1:
            dire, mess, resp = look_inventory_focus_broadcast(socket, level)
            food = get_food(resp)
            level = waiting_for_incant(socket, resp, level)
            if level != lvl:
                return level
            if dire == -1:
                socket.Look()
                dire, mess, resp = EmptyCacheFocusBroadcast(socket, level)
                level = waiting_for_incant(socket, resp, level)
                if level != lvl:
                    return level
        direction = dire
    return level
