#!/usr/bin/env python3
# coding: utf-8


# from threading import Thread


# class ListenSocketThread(Thread):

#     def __init__(self):
#         pass

import threading
import queue
import time


def func1(num, q):
    for i in range(10):
        _str = ""
        num = num**2
        # _str = "this\nmessage -> " + str(num) + "\n\n"
        _str = input("here: ")
        q.put(_str.split('\n'))


def func2(num, q):
    time.sleep(1)
    _str = []
    while True:
        if not q.empty():
            _str = q.get_nowait()
            print(_str)
        # print("yolo")


num = 2
q = queue.Queue()
thread1 = threading.Thread(target=func1,args=(num,q))
thread2 = threading.Thread(target=func2,args=(num,q))
print('setup')
thread1.start()
thread2.start()
