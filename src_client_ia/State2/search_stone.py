#!/usr/bin/env python3

from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food
from General_comportement.mov_to_tile import mov_to_tile
from General_comportement.ressources import IsThereItem
from General_comportement.inventory import GetLeftOverStone
from General_comportement.broadcast import EmptyCacheIgnoreBroadcast


def search_stone_mode(level, food, left_over, socket):
    while (food >= level + 1 and len(left_over) != 0):
        location, item = IsThereItem(socket, left_over)
        if (location >= 0):
            mov_to_tile(location, level, socket)
            socket.Take(item)
            EmptyCacheIgnoreBroadcast(socket)
            inventory = look_inventory(socket)
            food = get_food(inventory)
            left_over = GetLeftOverStone(inventory, ["linemate 1"])
            print ("Stone search: stone i got: " + str(food))
        else:
            socket.Forward()
            EmptyCacheIgnoreBroadcast(socket)
