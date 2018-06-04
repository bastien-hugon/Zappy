/*
** EPITECH PROJECT, 2018
** MyIRC - Server
** File description:
** Initialise epoll events
*/

/**
*@brief Init epoll socket management
*
*@file init_epoll.c
*@author Hugon Bastien
*@date 06-05-2018
*/
#include "server.h"

/**
*@brief Init epoll on server_t struct
*
*@param srv The main server_t struct
*/
void init_epoll(server_t *srv)
{
	srv->epollfd = epoll_create1(0);
	if (srv->epollfd == -1)
		exit(close_and_msg(srv, "error: epoll_create1"));
	srv->ev.events = EPOLLIN;
	srv->ev.data.fd = srv->sock.s_fd;
	if (epoll_ctl(srv->epollfd, EPOLL_CTL_ADD, srv->sock.s_fd, \
	&(srv->ev)) == -1)
		exit(close_and_msg(srv, "error: epoll_ctl"));
}