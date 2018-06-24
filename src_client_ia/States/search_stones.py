#!/usr/bin/env python3

from General_comportement.inventory import look_inventory_search_broadcast
from General_comportement.inventory import get_food
from General_comportement.mov_to_tile import mov_to_tile_search_broadcast
from General_comportement.ressources import IsThereItemSearchBroadcast
from General_comportement.inventory import GetLeftOverStone
from General_comportement.ressources import GetNeededRessources
from General_comportement.language import EmptyCacheSearchBroadcast


def enough_food(level, food):
    if (food >= (level + 1)):
        return (True)
    else:
        return (False)


def search_stone_mode(lvl, food, left_over, socket):
    while (enough_food(lvl, food) and len(left_over) != 0):
        dire, mess, resp, level = look_inventory_search_broadcast(socket, lvl)
        if level != lvl:
            return dire, mess, level
        if dire != -1 and lvl != 1:
            return dire, mess, lvl
        food = get_food(resp)
        location, item, dire, mess, level = IsThereItemSearchBroadcast(socket,
                                                                       left_over,
                                                                       lvl)
        if level != lvl:
            return dire, mess, level
        if dire != -1 and lvl != 1:
            return dire, mess, lvl
        if (location >= 0):
            dire, mess, level = mov_to_tile_search_broadcast(location, lvl,
                                                             socket)
            if level != lvl:
                return dire, mess, level
            if dire != -1 and lvl != 1:
                return dire, mess, lvl
            socket.Take(item)
            dire, mess, resp, level = EmptyCacheSearchBroadcast(socket, lvl)
            if level != lvl:
                return dire, mess, level
            if dire != -1 and lvl != 1:
                return dire, mess, lvl
            dire, mess, resp, level = look_inventory_search_broadcast(socket,
                                                                      lvl)
            if level != lvl:
                return dire, mess, level
            if dire != -1 and lvl != 1:
                return dire, mess, lvl
            left_over = GetLeftOverStone(resp, GetNeededRessources(lvl))
            print ("Stone search: stone i got: " + str(food))
        else:
            socket.Forward()
            dire, mess, resp, level = EmptyCacheSearchBroadcast(socket, lvl)
            if level != lvl:
                return dire, mess, level
            if dire != -1 and lvl != 1:
                return dire, mess, lvl
    return -1, [], lvl
