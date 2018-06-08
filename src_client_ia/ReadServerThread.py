#!/usr/bin/env python3

#
# EPITECH PROJECT, 2018
# PSU_zappy_2017
# File description:
# ReadServerThread
#

import sockets
import time
import queue
from threading import Thread, RLock

lock = RLock()


class ReadOnServer(Thread):

    def __init__(self, fd, queue):
        Thread.__init__(self)
        self.fd = fd
        self.queue = queue

    def run(self):
        allCommand = list()
        with lock:
            while (True):
                allCommand = sockets.get_fd_activity(self.fd).split('\n')
                allCommand = list(filter(None, allCommand))
                self.queue.put_nowait(allCommand)
                time.sleep(0.1)
