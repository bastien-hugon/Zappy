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
