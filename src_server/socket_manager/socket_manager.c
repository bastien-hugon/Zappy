/*
** EPITECH PROJECT, 2018
** MyIRC - Server
** File description:
** Socket Manager
*/

/**
*@brief Manage socket and create workers
*
*@file socket_manager.c
*@author Hugon Bastien
*@date 06-05-2018
*/
#include "server.h"

/**
*@brief Manage each events to distribute data or create new user
*
*@param srv Main server_t struct
*@param i Event index
*/
void manage_events(server_t *srv, int i)
{
	users_t *new_user = NULL;

	if (srv->events[i].data.fd == srv->sock.s_fd) {
		new_user = create_user();
		new_user->fd = accept(srv->sock.s_fd, \
		(struct sockaddr *) &(new_user->s_in), &(new_user->size));
		if (new_user->fd == -1)
			close_and_msg(srv, "error: accept");
		srv->ev.events = EPOLLIN | EPOLLET;
		srv->ev.data.fd = new_user->fd;
		if (epoll_ctl(srv->epollfd, EPOLL_CTL_ADD, new_user->fd, \
		&(srv->ev)) == -1)
			close_and_msg(srv, "error: epoll_ctl");
		push_user_to_chan(new_user, srv->chan);
	} else {
		call_worker(srv, srv->events[i].data.fd);
	}
}

/**
*@brief Manage all socket and redistribute data to wanted fd
*
*@param srv Main server_t struct
*/
void socket_manager(server_t *srv)
{
	int nfds = 0;

	while (true) {
		nfds = epoll_wait(srv->epollfd, srv->events, MAX_EVENTS, -1);
		if (nfds == -1)
			close_and_msg(srv, "error: epoll_wait");
		for (int i = 0; i < nfds; ++i) {
			manage_events(srv, i);
		}
	}
}