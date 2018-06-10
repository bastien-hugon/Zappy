#!/usr/bin/env python3

import sockets
from sys import argv
import time
import signal
from threading import Thread, RLock

CMD_MSZ = ("msz")
CMD_BCT = ("bct %d %d")
CMD_MCT = ("mct")
CMD_TNA = ("tna")
CMD_PPO = ("ppo #%d")
CMD_PLV = ("plv #%d")
CMD_PIN = ("pin #%d")
CMD_SGT = ("sgt")
CMD_SST = ("sst %f")
lock = RLock()


class read_on_server(Thread):
    def __init__(self, fd):
        Thread.__init__(self)
        self.fd = fd

    def run(self):
        allCommand = list()
        while (True):
            with lock:
                allCommand = sockets.get_fd_activity(
                    self.fd).split('\n')
                allCommand = list(filter(None, allCommand))
                print("allCommand = ", allCommand)
                time.sleep(0.1)


def init_socket(port, ip):
    fd = sockets.create_socket(ip, port)
    if (fd == -1):
        print("Bad socket init")
        exit(84)
    return (fd)


def get_command(fd):
    sockets.send_command(CMD_MSZ, fd)
    while (True):
        sockets.send_command(CMD_MCT, fd)
        time.sleep(0.1)


def init_game(fd):
    sockets.send_command("GFX_CLIENT", fd)


def main():
    nb_args = len(argv) - 1
    if (nb_args != 1):
        exit(84)
    connexion = list()
    connexion = argv[1].split(":")
    try:
        ip = connexion[0]
        port = int(connexion[1])
    except ValueError as e:
        print(e)
        exit(84)
    fd = init_socket(port, ip)
    thread_1 = read_on_server(fd)
    thread_1.setDaemon(True)
    thread_1.start()
    init_game(fd)
    get_command(fd)
    return (0)

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt as k:
        print("\nProgram interrupt with CTRL+C")
        exit(0)
