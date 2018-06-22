#!/usr/bin/env python3


def go_to_tile(nb_forward, nb_side, socket):
    for i in range(nb_forward):
        socket.Forward()
        socket.EmptyCache()
    if (nb_side < 0):
        socket.Left()
        socket.EmptyCache()
    elif (nb_side > 0):
        socket.Right()
        socket.EmptyCache()
    nb_side = abs(nb_side)
    for i in range(nb_side):
        socket.Forward()
        socket.EmptyCache()


def mov_to_tile(tile, level, socket):
    if (tile == 0):
        return
    nb_forward = 0
    for x in range(level + 1):
        if (tile >= (x * (x + 1) - x) and tile <= (x * (x + 1) + x)):
            nb_forward = x
    nb_side = tile - (nb_forward * (nb_forward + 1))
    go_to_tile(nb_forward, nb_side, socket)


def movToBroadcast(direction, socket, level):
    ListActions = [['wait'],
                   ['forward'],
                   ['forward', 'left', 'forward'],
                   ['left', 'forward'],
                   ['left', 'forward', 'left', 'forward'],
                   ['right', 'right', 'forward'],
                   ['right', 'forward', 'right', 'forward'],
                   ['right', 'forward'],
                   ['forward', 'right', 'forward']]
    for action in ListActions[direction]:
        if action == 'forward':
            socket.Forward()
            _dir, message, resp = EmptyCacheSearchBroadcast(socket, level)
            if (len(message) >= 3 and message[1] == 'INCANTREFUSE' and
               message[2] == socket.id):
                return (-1)
        elif (action == 'left'):
            socket.Left()
            _dir, message, resp = EmptyCacheSearchBroadcast(socket, level)
            if (len(message) >= 3 and message[1] == 'INCANTREFUSE' and
               message[2] == socket.id):
                return (-1)
        elif (action == 'right'):
            socket.Right()
            _dir, message, resp = EmptyCacheSearchBroadcast(socket, level)
            if (len(message) >= 3 and message[1] == 'INCANTREFUSE' and
               message[2] == socket.id):
                return (-1)
        else:
            return (1)
    return (1)
