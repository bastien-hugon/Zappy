#!/usr/bin/env python3

from States.survive import survive_mode
from States.search_food_incant import search_food_incant_mode
from States.search_stones import search_stone_mode
from States.incant import incant
from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food
from General_comportement.inventory import GetLeftOverStone
from General_comportement.ressources import GetNeededRessources
from General_comportement.foodHandling import enough_food
from General_comportement.foodHandling import enough_food_incant


def level1(level, socket):
    needed_stones = GetNeededRessources(level)
    while (level == 1):
        inventory = look_inventory(socket)
        food = get_food(inventory)
        left_over = GetLeftOverStone(inventory, needed_stones)
        print ("BASE:food i got: " + str(food))
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
            level = incant(socket, food, level)
    return (level)
