#!/usr/bin/env python3

from General_comportement.check_dead import check_dead


#
# @brief: Function that calls for server response and parses it so that the
# return value does not contain any broadcast message
#
# @param: socket [in], socket class variable to interact with socket class
#
# @return: resp, a string containing the content of the sever socket fd
# without the broadcast messages
#
def EmptyCacheIgnoreBroadcast(socket):
    resp = []
    while (len(resp) == 0):
        resp = socket.ReadSocket()
        for i in range(len(resp)):
            if "message" in resp[i]:
                del resp[i]
        check_dead(resp)
    print("resp = " + str(resp))
    return (resp)


#
# @brief: Function that get the message send by broadcast and parse it to see
# if it can interrest the actual A.I.
#
# @param: level [in], actual level of the A.I.
# @param: message [in], message received
#
# @return: Boolean : where the message came from
# if the message is interresting, -1 otherwise
#
def isBroadcastInterresting(level, message):
    data = message.split(',')
    broadCast = data[0].split(' ')
    whereItComeFrom = broadCast[1]
    message = data[1].split(':')
    if (broadCast[0] != "message"):
        return (-1)
    if (message[0] != " INCANT"):
        return (-1)
    if (int(message[1]) != level):
        return (-1)
    return (whereItComeFrom)
