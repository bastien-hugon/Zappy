#!/usr/bin/env python3

import random

from General_comportement.ressources import nb_player_here
from General_comportement.ressources import get_all_item_here
from General_comportement.language import EmptyCacheSearchBroadcast
from General_comportement.language import SendIncantBroadcast
from General_comportement.ressources import number_of_people_to_incant
from General_comportement.ressources import GetNeededRessources
from General_comportement.broadcast import EmptyCacheIgnoreBroadcast
from General_comportement.inventory import look_inventory
from General_comportement.inventory import get_food


def set_stones(socket, level):
    items = GetNeededRessources(level)
    for obj in items:
        content = obj.split(' ')
        for i in range(int(content[1])):
            socket.Set(content[0])
            resp = EmptyCacheIgnoreBroadcast(socket)


def incant(socket, food, level):
    while food >= level + 3:
        count = 0
        SendIncantBroadcast(socket, level)
        resp = EmptyCacheIgnoreBroadcast(socket)
        socket.Look()
        resp = EmptyCacheIgnoreBroadcast(socket)
        resp = resp[:1]
        if len(resp) > 0 and resp[0] != "ko":
            resp = resp[0][2:-2].split(',')
            content = resp[0].split(' ')
            for item in content:
                if item == "player":
                    count += 1
        if count == number_of_people_to_incant(level):
            socket.Look()
            resp = EmptyCacheIgnoreBroadcast(socket)
            resp = resp[:1]
            resp = resp[0][2:-2].split(',')
            get_all_item_here(socket, resp[0])
            set_stones(socket, level)
            socket.Incantation()
            resp = EmptyCacheIgnoreBroadcast(socket)
            if (resp[0] == "Elevation underway"):
                resp = EmptyCacheIgnoreBroadcast(socket)
                if (resp[0] == "ko"):
                    return (level)
                else:
                    return (level + 1)
            else:
                return (level)
        inventory = look_inventory(socket)
        food = get_food(inventory)
