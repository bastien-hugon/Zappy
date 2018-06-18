#!/usr/bin/env python3

from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food
from General_comportement.inventory import get_linemate
from General_comportement.mov_to_tile import mov_to_tile
from General_comportement.ressources import IsThereItem
from General_comportement.inventory import GetLeftOverStone


def enough_food(level, food):
    if (food >= (level + 1)):
        return (True)
    else:
        return (False)


def search_stone_mode(level, food, left_over, socket):
    # while (enough_food(level, food) and linemate < 1):
    # left_over = ["linemate 1"]
    while (enough_food(level, food) and len(left_over) != 0):
        # food_location = IsThereItem(socket, ["food"])
        location, item = IsThereItem(socket, left_over)
        if (location >= 0):
            mov_to_tile(location, level, socket)
            socket.Take(item)
            socket.EmptyCache()
            inventory = look_inventory(socket)
            food = get_food(inventory)
            left_over = GetLeftOverStone(inventory, ["linemate 1"])
            # linemate = get_linemate(inventory)
            print ("Stone search: stone i got: " + str(food))
        # elif (food_location >= 0):
        #     mov_to_tile(food_location, level, socket)
        #     socket.Take('food')
        #     socket.EmptyCache()
        #     inventory = look_inventory(socket)
        #     food = get_food(inventory)
        #     print ("Stone search: food i got: " + str(food))
        else:
            socket.Forward()
            socket.EmptyCache()
