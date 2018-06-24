/*
** EPITECH PROJECT, 2018
** Zappy - Server
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
	INFO("Initialising the epoll system...");
	srv->srv_epoll.epollfd = epoll_create1(0);
	if (srv->srv_epoll.epollfd == -1)
		exit(close_and_msg(srv, "error: epoll_create1"));
	srv->srv_epoll.ev.events = EPOLLIN;
	srv->srv_epoll.ev.data.fd = srv->srv_epoll.socket.fd;
	if (epoll_ctl(srv->srv_epoll.epollfd, EPOLL_CTL_ADD, \
	srv->srv_epoll.socket.fd, &(srv->srv_epoll.ev)) == -1)
		exit(close_and_msg(srv, "error: epoll_ctl"));
}