#!/usr/bin/env python3


def check_dead(list):
    for object in list:
        if object == "dead":
            print("Dead")
            exit(0)
