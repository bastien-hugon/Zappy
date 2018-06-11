#!/usr/bin/env python3

from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food
from General_comportement.mov_to_tile import mov_to_tile


def is_there_food(socket):
    socket.Look()
    resp = []
    while (len(resp) == 0):
        resp = socket.ReadSocket()
    resp = resp[:1]
    if len(resp) > 0 and resp[0] != "ko":
        resp = resp[0][2:-2].split(',')
    for tile in range(len(resp)):
        content = resp[tile].split(' ')
        for item in content:
            if item == 'food':
                return (tile)
    return (-1)


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
            resp = []
            while (len(resp) == 0):
                resp = socket.ReadSocket()
            inventory = look_inventory(socket)
            food = get_food(inventory)
            print ("SURVIVE: food i got: " + str(food))
        else:
            socket.Forward()
            resp = []
            while (len(resp) == 0):
                resp = socket.ReadSocket()
