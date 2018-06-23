#!/usr/bin/env python3


from General_comportement.broadcast import EmptyCacheIgnoreBroadcast
from General_comportement.inventory import look_inventory_search_broadcast
from General_comportement.inventory import get_food
from General_comportement.mov_to_tile import movToBroadcast


def go_to_incant_state(socket, level, food, direction, message):
    socket.target_id == message[0]
    while food >= level + 3:
        dire, mess, resp = look_inventory_search_broadcast(socket, level)
        for _object in resp:
            if ("Elevation underway" in _object):
                print("ELEVATION UNDERWAY lvl = " + str(level))
                resp = EmptyCacheIgnoreBroadcast(socket)
                for _object in resp:
                    if ("ko" in _object):
                        return level
                    else:
                        return level + 1
        food = get_food(resp)
        if direction != dire and dire != -1:
            direction = dire
        movToBroadcast(direction, socket, level)
    return level
