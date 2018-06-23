#!/usr/bin/env python3


def enough_food(level, food):
    if (food >= (level + 3)):
        return (True)
    else:
        return (False)


def waitForIncantation(socket, food):
    while (enough_food(level, food)):
        sockect.Inventory()
        _dir, message, resp = EmptyCacheSearchBroadcast(socket, level)
        food = get_food(resp)
        if (resp)


def move_to_incant(level, socket, food):
    while (enough_food(level, food)):
        socket.Inventory()
        _dir, message, resp = EmptyCacheSearchBroadcast(socket, level)
        food = get_food(resp)
        if (_dir != -1 and len(message) >= 3 and message[1] == "HERE"):
            shouldIWait = movToBroadcast(_dir, socket, level)
            if shouldIWait == -1:
                return
            elif shouldIWait == 1:
                waitForIncantation(socket, food)
    SendOutBroadcast(socket)
    EmptyCacheIgnoreBroadcast()
    socket.target_id = []
