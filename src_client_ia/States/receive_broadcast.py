#!/usr/bin/env python3


#
# @brief: Function that checks if we received INCANTACCEPT or INCANTREFUSE
#
# @param: socket [in], socket class variable to interact with socket class
# @param: direction [in], the direction where the message was received from
# @param: message [in], a list of the message pre-parsed
#
# @return: if "" then back to normal else "MOVETOINCANT"
#
def check_incant_status(socket, direction, message):
    if direction != -1 and len(message) > 0 and
    message[0] is in socket.target_id:
        if message[1] == "INCANTACCEPT" and message[2] == socket.id:
            return "MOVETOINCANT"
        if message[1] == "INCANTREFUSE" and message[2] == socket.id:
            return "BACKTONORMAL"
    return ""


#
# @brief: Function that is called when an interesting INCANT Broadcast is
# received, therefore the function waits for people to say they are coming and
# either accepts them to come or refuses
#
# @param: socket [in], socket class variable to interact with socket class
# @param: direction [in], the direction where the message was received from
# @param: message [in], a list of the message pre-parsed
# @param: lvl [in], int, the current level of the player
#
# @return: direction, message. The direction is where the message came from,
# the message is the cut up message to be executed later
#
def ReceiveIncantFunction(socket, direction, message, food, lvl):
    socket.target_id.append(message[0])
    while food >= lvl + 3:
        SendComingBroadcast(socket.target_id[0])
        direction, message, resp = EmptyCacheSearchBroadcast(socket, lvl)
        mess = check_incant_status(socket, direction, message)
        if mess == "MOVETOINCANT":
            return "MOVETOINCANT"
        elif mess == "BACKTONORMAL":
            return ""
        socket.Inventory()
        direction, message, resp = EmptyCacheSearchBroadcast(socket, lvl)
        food = get_food(resp[0])
        mess = check_incant_status(socket, direction, message)
        if mess == "MOVETOINCANT":
            return "MOVETOINCANT"
        elif mess == "BACKTONORMAL":
            return ""
    return ""
