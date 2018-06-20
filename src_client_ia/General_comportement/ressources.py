#!/usr/bin/env python3

from General_comportement.broadcast import EmptyCacheIgnoreBroadcast


#
# @brief: Funtion that takes the lvl nbr of the player and returns the list
# of needed stones for next level
#
# @param: lvl [in], the current level of the player
#
# @return: needed_stones[lvl], returns the list of the required stones for
# next level
#
def GetNeededRessources(lvl):
    needed_stones = [
        [],
        ['linemate 1'],
        ['linemate 1', 'deraumere 1', 'sibur 1'],
        ['linemate 2', 'sibur 1', 'phiras 2'],
        ['linemate 1', 'deraumere 1', 'sibur 2', 'phiras 1'],
        ['linemate 1', 'deraumere 2', 'sibur 1', 'mendiane 3'],
        ['linemate 1', 'deraumere 2', 'sibur 3', 'phiras 1'],
        ['linemate 2', 'deraumere 2', 'sibur 2', 'mendiane 2', 'phiras 2', 'thystame 1']
    ]
    return needed_stones[lvl]


#
# @brief: Function that looks for one of the items demanded by the player.
# The smallest index tile where one of the requested item is situated will
# be returned
#
# @param: socket [in], variable of type class Socket
# @param: requested_item [in], a list with all the requested item needed by
# the player
#
# @return: tile, item [], returns 2 elements, the first one is the position
# of the tile where the requested item is situated
#
def IsThereItem(socket, requested_item):
    socket.Look()
    resp = EmptyCacheIgnoreBroadcast(socket)
    resp = resp[:1]
    if len(resp) > 0 and resp[0] != "ko":
        resp = resp[0][2:-2].split(',')
    for tile in range(len(resp)):
        content = resp[tile].split(' ')
        for item in content:
            for req_item in requested_item:
                if item in req_item.split(' '):
                    return (tile, item)
    for tile in range(len(resp)):
        content = resp[tile].split(' ')
        for item in content:
            if item == "food":
                return (tile, item)
    return (-1, "None")


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
            EmptyCacheIgnoreBroadcast(socket)
