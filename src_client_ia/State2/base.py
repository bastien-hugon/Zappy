#!/usr/bin/env python3

from State2.survive import survive_mode
from State2.search_food_incant import search_food_incant_mode
from State1.search_stones import search_stone_mode
from State1.incant import incant
from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food
from General_comportement.inventory import GetLeftOverStone
from General_comportement.ressources import GetNeededRessources


def base_state2(level, socket):
    needed_stones = GetNeededRessources(level)
    while (level != 8):
        inventory = look_inventory(socket)
        food = get_food(inventory)
        left_over = GetLeftOverStone(inventory, needed_stones)
        if food <= level + 1:
            survive_mode(level, food, socket)
        elif food <= level + 3:
            search_food_incant_mode(level, food, socket)
        elif len(left_over) != 0:
            pass
            #search_stone_mode(level, food, left_over, socket)
        else:
            pass
            #need to create incantation
    return (level)
