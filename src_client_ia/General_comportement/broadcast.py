#!/usr/bin/env python3

import re

from General_comportement.check_dead import check_dead


#
# @brief: Function that calls for server response and parses it so that the
# return value does not contain any broadcast message
#
# @param: socket [in], socket class variable to interact with socket class
# @param: lvl [in], int, level of the A.I.
#
# @return: resp, a string containing the content of the sever socket fd
# without the broadcast messages
# @return: lvl, the level of the ia at the end of the function
#
def EmptyCacheIgnoreBroadcast(socket, lvl):
    resp = []
    incant = False
    while (len(resp) == 0):
        resp = socket.ReadSocket()
        check_dead(resp)
        i = 0
        while i < len(resp):
            if resp[i].find("message") != -1:
                resp.pop(i)
            elif resp[i].find("Elevation underway") != -1:
                incant = True
                print("INCANT TRUE : " + str(resp[i]))
                print("CURRENT LIST : " + str(resp))
                resp.pop(i)
            elif resp[i].find("Current level:") != -1:
                print("FOUND CURRENT LEVEL: " + str(resp))
                ret = re.findall('\d+', resp[i])
                if len(ret) > 0:
                    if int(ret[0]) != lvl:
                        return resp, int(ret[0])
            else:
                i += 1
    if incant is True:
        print("WAITING FOR INCANT")
        ret_incant, level = EmptyCacheIgnoreBroadcast(socket, lvl)
        if (level != lvl):
            return resp, level
        for response in ret_incant:
            if "Current level:" in response:
                ret = re.findall('\d+', response)
                if len(ret) > 0:
                    if int(ret[0]) != lvl:
                        return resp, int(ret[0])
        return resp, lvl
    print("IngnoreBroadcast resp = " + str(resp))
    return resp, lvl


#
# @brief: Function that calls for server response and parses it so that the
# return value does not contain any broadcast message. It should be used
# to incant
#
# @param: socket [in], socket class variable to interact with socket class
# @param: lvl [in], int, level of the A.I.
#
# @return: resp, a string containing the content of the sever socket fd
# without the broadcast messages
# @return: lvl, the level of the ia at the end of the function
#
def EmptyCacheIgnoreBroadcastIncant(socket, lvl):
    resp = []
    incant = False
    while (len(resp) == 0):
        resp = socket.ReadSocket()
        check_dead(resp)
        i = 0
        while i < len(resp):
            if resp[i].find("message") != -1:
                resp.pop(i)
            elif resp[i].find("Elevation underway") != -1:
                incant = True
                print("INCANT TRUE : " + str(resp[i]))
                print("CURRENT LIST : " + str(resp))
                resp.pop(i)
            elif resp[i].find("Current level:") != -1:
                print("FOUND CURRENT LEVEL")
                ret = re.findall('\d+', resp[i])
                if len(ret) > 0:
                    if int(ret[0]) != lvl:
                        return resp, int(ret[0])
            else:
                i += 1
    if incant is True:
        for response in resp:
            if "Current level:" in response:
                ret = re.findall('\d+', response)
                if len(ret) > 0:
                    if int(ret[0]) != lvl:
                        return resp, int(ret[0])
    print("IngnoreBroadcastIncant resp = " + str(resp))
    return resp, lvl
