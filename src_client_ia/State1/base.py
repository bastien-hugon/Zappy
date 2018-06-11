#!/usr/bin/env python3


def look_inventory(socket):
    socket.Inventory()
    resp = []
    while (len(resp) == 0):
        resp = socket.ReadSocket()
    print ("RESP: " + str(resp))
    if len(resp) > 0 and resp[0] != "ko":
        resp[0] = resp[0][2:-2].split(', ')
    return (resp)


def get_food(inventory):
    ret = []
    for i in (inventory):
        if (i[:4] == 'food'):
            ret = [int(s) for s in i if s.isdigit()]
    if len(ret) > 0:
        return (ret[0])
    else:
        return (0)


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
        print ('NEW LOOP')
        inventory = look_inventory(socket)
        food = get_food(inventory)
        print ("food i got: " + str(food))
        if (not enough_food(level, food)):
            print('MODE: survive mode')
           # survive_mode(actual_level)
        elif (not enough_food_incant(level, food)):
            print('MODE: search food incant')
          #  search_food_incant_mode(actual_level)
        elif (not enough_stone(level, stone)):
            print('MODE: search stone')
         #   search_stone_mode()
        else:
            print('MODE: INCANT')
        #    actual_level = incant()
    return (actual_level)
