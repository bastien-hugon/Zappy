#!/usr/bin/env python3

from States.survive import survive_mode
from States.search_food_incant import search_food_incant_mode
from States.search_stones import search_stone_mode
from States.incant import incant
from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food
from General_comportement.inventory import GetLeftOverStone
from General_comportement.ressources import GetNeededRessources


def level2to7(level, socket):
    needed_stones = GetNeededRessources(level)
#     while (level != 8):
#         inventory, level = look_inventory(socket, level)
#         food = get_food(inventory)
#         left_over = GetLeftOverStone(inventory, needed_stones)
#         if food <= level + 1:
#             survive_mode(level, food, socket)
#         elif food <= level + 3:
#             search_food_incant_mode(level, food, socket)
#         elif len(left_over) != 0:
#             search_stone_mode(level, food, left_over, socket)
#         else:
#             pass
#             #need to create incantation
#     return (level)
