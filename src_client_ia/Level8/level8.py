#!usr/bin/env python3

from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food
from States.survive import survive_mode
from General_comportement.language import EmptyCacheSearchBroadcast


def level8(socket):
    level = 8
    while (1):
        inventory, level = look_inventory(socket, level)
        food = get_food(inventory)
        if (food < level + 1):
            level = survive_mode(level, food, socket)
        else:
            socket.Forward()
            dire, mess, resp, level = EmptyCacheSearchBroadcast(socket, lvl)
