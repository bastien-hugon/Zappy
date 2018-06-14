#!/usr/bin/env python3

from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food
from General_comportement.mov_to_tile import mov_to_tile
from General_comportement.ressources import is_there_food


def enough_food(level, food):
    if (food >= (level + 1)):
        return (True)
    else:
        return (False)


def survive_mode(level, food, socket):
    while (not enough_food(level, food)):
        food_location = is_there_food(socket)
        if (food_location >= 0):
            mov_to_tile(food_location, level, socket)
            socket.Take('food')
            socket.EmptyCache()
            inventory = look_inventory(socket)
            food = get_food(inventory)
            print ("SURVIVE: food i got: " + str(food))
        else:
            socket.Forward()
            socket.EmptyCache()
