#!/usr/bin/env python3


#
# @brief: Check if the A.I. has enough food to survive
#
# @param: level [in], int, actual level of the A.I.
# @param: food [in], int, number of food units own by the A.I.
#
# @return: Boolean, True if the AI has enough food, False otherwise
#
def enough_food(level, food):
    if (food >= (level + 1)):
        return (True)
    else:
        return (False)


#
# @brief: Check if the A.I. has enough food to survive to an incantation
#
# @param: level [in], int, actual level of the A.I.
# @param: food [in], int, number of food units own by the A.I.
#
# @return: Boolean, True if the AI has enough food, False otherwise
#
def enough_food_incant(level, food):
    if (food >= (level + 8)):
        return (True)
    else:
        return (False)
