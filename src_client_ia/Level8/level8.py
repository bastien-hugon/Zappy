#!usr/bin/env python3

from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food
from States.survive import survive_mode


def level8(socket):
    level = 8
    while (1):
        inventory, level = look_inventory(socket, level)
        food = get_food(inventory)
        if (not enough_food(level, food)):
            survive_mode(level, food, socket)
        else:
            socket.Forward()
            socket.EmptyCache()
