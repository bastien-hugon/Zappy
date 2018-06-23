#!/usr/bin/env python3

import re

from General_comportement.check_dead import check_dead
from General_comportement.broadcast import EmptyCacheIgnoreBroadcast


#
# @brief: Function that demands to the server for the inventory and then
# parses it
#
# @param: inventory [in], the list of the current inventory
#
# @return: returns the response of the server
#
def look_inventory(socket):
    socket.Inventory()
    resp = EmptyCacheIgnoreBroadcast(socket)
    if len(resp) > 0 and resp[0] != "ko":
        resp[0] = resp[0][2:-2].split(', ')
    return (resp)


#
# @brief: Function that looks in the inventory list and returns the numbe
# of food in the player inventory
#
# @param: inventory [in], the list of the current inventory
#
# @return: returns the number of food in the inventory. if error return 0
#
def get_food(inventory):
    ret = []
    for i in (inventory[0]):
        if (i[:4] == 'food'):
            ret = re.findall('\d+', i)
    print("FINDALL = " + str(ret) + " RESP = " + str(inventory))
    if len(ret) > 0:
        return (int(ret[0]))
    else:
        return (0)


#
# @brief: Function that compares the inventory with the required stones to
#         level up and returns a list of the stones left to take for level up
#
# @param: inventory [in], the list of the current inventory
# @param: stones_needed [in], the list of the required stones for level up
#
# @return: left_over [], the list of the stones left to take
#
def GetLeftOverStone(inventory, stones_needed):
    if inventory[0] == "ko":
        return ["linemate 1"]
    left_over = []
    stones_needed_list = []
    for item in stones_needed:
        stones_needed_list.append(item.split(' '))
    inventory_list = []
    for item in inventory[0]:
        inventory_list.append(item.split(' '))
    for item in stones_needed_list:
        for inv_item in inventory_list:
            if item[0] == inv_item[0]:
                number = int(item[1]) - int(inv_item[1])
                if number > 0:
                    left_over.append(item[0] + ' ' + str(number))
    return (left_over)
