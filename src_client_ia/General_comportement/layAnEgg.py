#!/usr/bin/env python3

from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food
from General_comportement.foodHandling import enough_food_incant
from States.search_food_incant import search_food_incant_mode
from General_comportement.broadcast import EmptyCacheIgnoreBroadcast


def layAnEgg(level, socket):
    inventory, lvl = look_inventory(socket, level)
    food = get_food(inventory)
    if (not enough_food_incant(level, food)):
        search_food_incant_mode(level, food, socket)
    socket.Fork()
    EmptyCacheIgnoreBroadcast(socket, level)
