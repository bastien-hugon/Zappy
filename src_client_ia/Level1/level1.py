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
from States.go_to_incant_state import go_to_incant_state


def level1(lvl, socket):
    level = lvl
    needed_stones = GetNeededRessources(level)
    dire = -1
    mess = []
    while (level == lvl):
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
        elif (dire != -1 and level != 1):
            print('MODE: go to incant')
            level = go_to_incant_state(socket, level, food, dire, mess)
            dire = -1
            mess = []
            socket.target_id = ""
        elif len(left_over) != 0 and enough_food_incant(level, food):
            print('MODE: search stone')
            dire, mess = search_stone_mode(level, food, left_over, socket)
        else:
            print('MODE: INCANT')
            level = incant(socket, food, level)
    return (level)
