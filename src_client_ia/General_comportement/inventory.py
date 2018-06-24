#!/usr/bin/env python3

import re

from General_comportement.check_dead import check_dead
from General_comportement.broadcast import EmptyCacheIgnoreBroadcast
from General_comportement.language import EmptyCacheSearchBroadcast
from General_comportement.language import EmptyCacheFocusBroadcast


#
# @brief: Function that demands to the server for the inventory and then
# parses it
#
# @param: inventory [in], the list of the current inventory
#
# @return: returns the response of the server
#
def look_inventory(socket, lvl):
    socket.Inventory()
    resp, level = EmptyCacheIgnoreBroadcast(socket, lvl)
    if level != lvl:
        return resp, level
    if len(resp) > 0 and resp[0] != "ko":
        resp[0] = resp[0][2:-2].split(', ')
    return resp, level


#
# @brief: Function that demands to the server for the inventory and then
# parses it.
# This function also listens for any wanted broadcast
#
# @param: inventory [in], the list of the current inventory
# @param: level [in], the current level of the player
#
# @return: dire, the direction of where the message came from, -1 if no message
# @return: mess, the content of the message, empty list if no message
#
def look_inventory_search_broadcast(socket, lvl):
    socket.Inventory()
    dire, mess, resp, level = EmptyCacheSearchBroadcast(socket, lvl)
    if lvl != level:
        return dire, mess, resp, level
    if len(resp) > 0 and resp[0] != "ko":
        resp[0] = resp[0][2:-2].split(', ')
    return dire, mess, resp, lvl


#
# @brief: Function that demands to the server for the inventory and then
# parses it.
# This function also listens for any wanted broadcast and focuses a specific
# broadcast id.
#
# @param: inventory [in], the list of the current inventory
# @param: level [in], the current level of the player
#
# @return: dire, the direction of where the message came from, -1 if no message
# @return: mess, the content of the message, empty list if no message
#
def look_inventory_focus_broadcast(socket, lvl):
    socket.Inventory()
    dire, mess, resp, level = EmptyCacheFocusBroadcast(socket, lvl)
    if level != lvl:
        return dire, mess, resp, level
    if len(resp) > 0 and resp[0] != "ko":
        resp[0] = resp[0][2:-2].split(', ')
    return dire, mess, resp, lvl


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
        if len(inventory[0]) != 7 or item[-1] == ',':
            return ["linemate 1"]
        inventory_list.append(item.split(' '))
    for item in stones_needed_list:
        for inv_item in inventory_list:
            if item[0] == inv_item[0]:
                if len(inventory[0]) != 7:
                    return ["linemate 1"]
                number = int(item[1]) - int(inv_item[1])
                if number > 0:
                    left_over.append(item[0] + ' ' + str(number))
    return (left_over)
