#!/usr/bin/env python3

import random
import re

from General_comportement.ressources import nb_player_here
from General_comportement.ressources import get_all_item_here
from General_comportement.language import SendIncantBroadcast
from General_comportement.ressources import number_of_people_to_incant
from General_comportement.ressources import GetNeededRessources
from General_comportement.broadcast import EmptyCacheIgnoreBroadcast
from General_comportement.broadcast import EmptyCacheIgnoreBroadcastIncant
from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food
from General_comportement.mov_to_tile import mov_to_tile


def move_to_free_tile(socket, lvl):
    socket.Look()
    resp, level = EmptyCacheIgnoreBroadcast(socket, lvl)
    if level != lvl:
        return tile, level
    if len(resp) > 0 and resp[0] != "ko":
        resp = resp[0][2:-2].split(',')
    for tile in range(len(resp)):
        if "player" not in resp[tile]:
            return tile, lvl
    return 0, lvl


def ko_incant(socket, lvl):
    socket.Look()
    resp, level = EmptyCacheIgnoreBroadcast(socket, lvl)
    if level != lvl:
        return level
    resp = resp[:1]
    resp = resp[0][2:-2].split(',')
    get_all_item_here(socket, resp[0], lvl)
    tile, level = move_to_free_tile(socket, lvl)
    if level != lvl:
        return level
    mov_to_tile(tile, lvl, socket)
    return lvl


def set_stones(socket, lvl):
    items = GetNeededRessources(lvl)
    for obj in items:
        content = obj.split(' ')
        for i in range(int(content[1])):
            socket.Set(content[0])
            resp, level = EmptyCacheIgnoreBroadcast(socket, lvl)
            if level != lvl:
                return level
    return lvl


def incant(socket, food, lvl):
    while food >= lvl + 3:
        count = 0
        SendIncantBroadcast(socket, lvl)
        resp, level = EmptyCacheIgnoreBroadcast(socket, lvl)
        if level != lvl:
            return level
        socket.Look()
        resp, level = EmptyCacheIgnoreBroadcast(socket, lvl)
        if level != lvl:
            return level
        resp = resp[:1]
        if len(resp) > 0 and resp[0] != "ko":
            resp = resp[0][2:-2].split(',')
            content = resp[0].split(' ')
            for item in content:
                if item == "player":
                    count += 1
        if count == number_of_people_to_incant(lvl):
            socket.Look()
            resp, level = EmptyCacheIgnoreBroadcast(socket, lvl)
            if level != lvl:
                return level
            resp = resp[:1]
            resp = resp[0][2:-2].split(',')
            get_all_item_here(socket, resp[0], lvl)
            set_stones(socket, lvl)
            socket.Incantation()
            resp, level = EmptyCacheIgnoreBroadcastIncant(socket, lvl)
            if level != lvl:
                return level
            # if ("Elevation underway" in resp):
            #     if len(resp) < 2:
            #         resp, level = EmptyCacheIgnoreBroadcast(socket, lvl)
            #         if level != lvl:
            #             return level
            #     for _object in resp:
            #         if ("Current level:" in _object):
            #             ret = re.findall('\d+', _object)
            #             if len(ret) > 0:
            #                 if int(ret[0]) != lvl:
            #                     return int(ret[0])
            #     ko_incant(socket, lvl)
            #     return lvl
            else:
                ko_incant(socket, lvl)
                return (lvl)
        inventory, level = look_inventory(socket, lvl)
        if level != lvl:
            return level
        food = get_food(inventory)
    return lvl
