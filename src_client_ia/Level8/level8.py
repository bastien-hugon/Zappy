#!usr/bin/env python3

from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food
from State1.survive import survive_mode


def base_state(socket):
    while (1):
        inventory = look_inventory(socket)
        food = get_food(inventory)
        if (not enough_food(level, food)):
            survive_mode(level, food, socket)
        else:
            socket.Forward()
            socket.EmptyCache()
