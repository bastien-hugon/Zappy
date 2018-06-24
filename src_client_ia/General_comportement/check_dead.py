#!/usr/bin/env python3


#
# @brief: Function that verify if a server response is a dead signal. If the
# client is dead it exit the program.
#
# @param: list [in], list of recently receive responses.
#
# @return: None
#
def check_dead(list):
    for object in list:
        if object == "dead":
            print("Dead")
            exit(0)
