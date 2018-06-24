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
from General_comportement.inventory import look_inventory_search_broadcast


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


def search_before_broadcast(socket, food, lvl):
    i = 0
    while i < 40 and food >= lvl + 3:
        dire, mess, resp, level = look_inventory_search_broadcast(socket, lvl)
        if level != lvl:
            return dire, mess, level
        if dire != -1 and lvl != 1:
            return dire, mess, lvl
        food = get_food(resp)
        i += 1
    return -1, [], lvl


def incant(socket, food, lvl):
    dire, mess, level = search_before_broadcast(socket, food, lvl)
    if level != lvl:
        return dire, mess, level
    if dire != -1 and lvl != 1:
        return dire, mess, lvl
    while food >= lvl + 3:
        count = 0
        SendIncantBroadcast(socket, lvl)
        resp, level = EmptyCacheIgnoreBroadcast(socket, lvl)
        if level != lvl:
            return dire, mess, level
        socket.Look()
        resp, level = EmptyCacheIgnoreBroadcast(socket, lvl)
        if level != lvl:
            return dire, mess, level
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
                return dire, mess, level
            resp = resp[:1]
            resp = resp[0][2:-2].split(',')
            get_all_item_here(socket, resp[0], lvl)
            set_stones(socket, lvl)
            socket.Incantation()
            resp, level = EmptyCacheIgnoreBroadcastIncant(socket, lvl)
            if level != lvl:
                return dire, mess, level
            else:
                ko_incant(socket, lvl)
                return dire, mess, lvl
        inventory, level = look_inventory(socket, lvl)
        if level != lvl:
            return dire, mess, level
        food = get_food(inventory)
    return dire, mess, lvl
