#!/usr/bin/env python3


def enough_food(level, food):
    if (food >= (level + 1)):
        return (True)
    else:
        return (False)


def enough_food_incant(level, food):
    if (food >= (level + 8)):
        return (True)
    else:
        return (False)
