#!/usr/bin/env python3

from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food
from General_comportement.inventory import get_linemate
from General_comportement.mov_to_tile import mov_to_tile
from General_comportement.ressources import is_there_food
from General_comportement.ressources import is_there_linemate


def enough_food(level, food):
    if (food >= (level + 1)):
        return (True)
    else:
        return (False)


def search_stone_mode(level, food, linemate, socket):
    while (enough_food(level, food) and linemate < 1):
        food_location = is_there_food(socket)
        stone_location = is_there_linemate(socket)
        if (stone_location >= 0):
            mov_to_tile(stone_location, level, socket)
            socket.Take('linemate')
            socket.EmptyCache()
            inventory = look_inventory(socket)
            food = get_food(inventory)
            linemate = get_linemate(inventory)
            print ("Stone search: stone i got: " + str(food))
        elif (food_location >= 0):
            mov_to_tile(food_location, level, socket)
            socket.Take('food')
            socket.EmptyCache()
            inventory = look_inventory(socket)
            food = get_food(inventory)
            print ("Stone search: food i got: " + str(food))
        else:
            socket.Forward()
            socket.EmptyCache()
