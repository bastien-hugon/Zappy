/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** module c socket
*/

#include "module.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/**
* @brief Set connexion between client and server
*
* @return int -> Filedescriptor
*/
int connection(int fd, struct sockaddr_in *s_in)
{
	if (connect(fd, (struct sockaddr *)s_in, sizeof(*s_in)) == -1) {
		close(fd);
		return (-1);
	}
	return (fd);
}

/**
* @brief check for a '\n' in the recieved message
*
* @param command [In], the command line
* @return int if '\n then 0 else -1
*/
int check_carriage_return(char *command)
{
	(void)sockets;
	if (strlen(command) > 4000 || command[strlen(command) - 1] == '\n')
		return (0);
	else
		return (-1);
}

int init_epoll(int fd)
{
	int epollfd;
	struct epoll_event ev;

	epollfd = epoll_create1(0);
	if (epollfd == -1) {
		fprintf(stderr, "error: epoll_create1\n");
		exit(84);
	}
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
		fprintf(stderr, "error: epoll_ctl\n");
		exit(84);
	}
	return (epollfd);
}
