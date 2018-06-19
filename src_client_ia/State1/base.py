#!/usr/bin/env python3

from State1.survive import survive_mode
from State1.search_food_incant import search_food_incant_mode
from State1.search_stones import search_stone_mode
from State1.incant import incant
from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food
from General_comportement.inventory import GetLeftOverStone
from General_comportement.ressources import GetNeededRessources


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


def base_state(level, socket):
    needed_stones = GetNeededRessources(level)
    while (level == 1):
        inventory = look_inventory(socket)
        food = get_food(inventory)
        left_over = GetLeftOverStone(inventory, needed_stones)
        print ("food i got: " + str(food))
        if (not enough_food(level, food)):
            print('MODE: survive')
            survive_mode(level, food, socket)
        elif (not enough_food_incant(level, food)):
            print('MODE: search food incant')
            search_food_incant_mode(level, food, socket)
        elif len(left_over) != 0:
            print('MODE: search stone')
            search_stone_mode(level, food, left_over, socket)
        else:
            print('MODE: INCANT')
            level = incant(socket)
    return (level)
