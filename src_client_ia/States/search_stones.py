#!/usr/bin/env python3

from General_comportement.inventory import look_inventory_search_broadcast
from General_comportement.inventory import get_food
from General_comportement.mov_to_tile import mov_to_tile_search_broadcast
from General_comportement.ressources import IsThereItemSearchBroadcast
from General_comportement.inventory import GetLeftOverStone
from General_comportement.ressources import GetNeededRessources
from General_comportement.broadcast import EmptyCacheIgnoreBroadcast
from General_comportement.language import EmptyCacheSearchBroadcast


def enough_food(level, food):
    if (food >= (level + 1)):
        return (True)
    else:
        return (False)


def search_stone_mode(level, food, left_over, socket):
    while (enough_food(level, food) and len(left_over) != 0):
        dire, mess, resp = look_inventory_search_broadcast(socket, level)
        if dire != -1 and level != 1:
            return dire, mess

        food = get_food(resp)
        location, item, dire, mess = IsThereItemSearchBroadcast(socket,
                                                                left_over,
                                                                level)
        if dire != -1 and level != 1:
            return dire, mess

        if (location >= 0):
            dire, mess = mov_to_tile_search_broadcast(location, level, socket)
            if dire != -1 and level != 1:
                return dire, mess

            socket.Take(item)
            dire, mess, resp = EmptyCacheSearchBroadcast(socket, level)
            if dire != -1 and level != 1:
                return dire, mess

            dire, mess, resp = look_inventory_search_broadcast(socket, level)
            if dire != -1 and level != 1:
                return dire, mess

            left_over = GetLeftOverStone(resp, GetNeededRessources(level))
            print ("Stone search: stone i got: " + str(food))
        else:
            socket.Forward()
            dire, mess, resp = EmptyCacheSearchBroadcast(socket, level)
            if dire != -1 and level != 1:
                return dire, mess
    return -1, []
