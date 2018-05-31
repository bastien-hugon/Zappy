#!/usr/bin/env python3

import sockets
from sys import argv


def init_socket(port, ip):
    if (sockets.create_socket(ip, port) == -1):
        print("Bad socket init")
        exit(84)
    return (0)

def get_command(fd):
    command = list()
    while (1):
        command.append(sockets.get_fd_activity(fd))

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
    get_command(fd)
    return (0)

if __name__ == "__main__":
    main()
