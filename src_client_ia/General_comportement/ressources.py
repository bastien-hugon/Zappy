#!/usr/bin/env python3

from General_comportement.check_dead import check_dead


def is_there_food(socket):
    socket.Look()
    resp = []
    while (len(resp) == 0):
        resp = socket.ReadSocket()
        print ("look: " + str(resp))
    check_dead(resp)
    resp = resp[:1]
    if len(resp) > 0 and resp[0] != "ko":
        resp = resp[0][2:-2].split(',')
    for tile in range(len(resp)):
        content = resp[tile].split(' ')
        for item in content:
            if item == 'food':
                return (tile)
    return (-1)


def is_there_linemate(socket):
    socket.Look()
    resp = []
    while (len(resp) == 0):
        resp = socket.ReadSocket()
        print ("look: " + str(resp))
    check_dead(resp)
    resp = resp[:1]
    if len(resp) > 0 and resp[0] != "ko":
        resp = resp[0][2:-2].split(',')
    for tile in range(len(resp)):
        content = resp[tile].split(' ')
        for item in content:
            if item == 'linemate':
                return (tile)
    return (-1)


def nb_player_here(look_result):
    count = 0
    tile = look_result.split(' ')
    for item in tile:
        if (item == 'player'):
            count += 1
    return (count)


def get_all_item_here(socket, here):
    tile = here.split(' ')
    for item in tile:
        if (item != 'player'):
            socket.Take(item)
            resp = []
            while (len(resp) == 0):
                resp = socket.ReadSocket()
                print ("take: " + str(resp))
            check_dead(resp)
