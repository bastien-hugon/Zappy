#!/usr/bin/env python3

from State1.survive import survive_mode
from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food


def enough_food(level, food):
    if (food >= (level + 1)):
        return (True)
    else:
        return (False)


def enough_food_incant(level, food):
    if (food >= (level + 3)):
        return (True)
    else:
        return (False)


def enough_stone(level, linemate):
    if (linemate >= 1):
        return (True)
    else:
        return (False)


def base_state(level, socket):
    actual_level = level
    stone = 0
    while (actual_level == level):
        inventory = look_inventory(socket)
        food = get_food(inventory)
        print ("food i got: " + str(food))
        if (not enough_food(level, food)):
            print('MODE: survive')
            survive_mode(actual_level, food, socket)
        elif (not enough_food_incant(level, food)):
            print('MODE: search food incant')
#           search_food_incant_mode(actual_level)
        elif (not enough_stone(level, stone)):
            print('MODE: search stone')
#           search_stone_mode()
        else:
            print('MODE: INCANT')
        #    actual_level = incant()
    return (actual_level)
