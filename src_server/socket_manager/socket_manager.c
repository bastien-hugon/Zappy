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
#include <sys/time.h>
#include "server.h"

/**
*@brief Manage each events to distribute data or create new user
*
*@param srv Main server_t struct
*@param i Event index
*/
static void manage_events(server_t *srv, int i)
{
	client_t user;

	if (srv->srv_epoll.events[i].data.fd == srv->srv_epoll.socket.fd) {
		create_user(&user, srv);
		user.socket.fd = accept(srv->srv_epoll.socket.fd, \
		(struct sockaddr *) &(user.socket.s_in), &(user.size));
		if (user.socket.fd == -1)
			close_and_msg(srv, "error: accept");
		srv->srv_epoll.ev.events = EPOLLIN | EPOLLET;
		srv->srv_epoll.ev.data.fd = user.socket.fd;
		if (epoll_ctl(srv->srv_epoll.epollfd, \
		EPOLL_CTL_ADD, user.socket.fd, \
		&(srv->srv_epoll.ev)) == -1)
			close_and_msg(srv, "error: epoll_ctl");
		list_push(&(srv->game.clients), &user);
		send_message(user.socket.fd, "WELCOME\n");
		LOG("New user connected with fd: %d", user.socket.fd);
	} else {
		call_worker(srv, srv->srv_epoll.events[i].data.fd);
	}
}

/**
*@brief Get the time object
*
*@return long long The current timestamp in ms
*/
static long long get_time(void) {
	struct timeval te;
	long long milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

/**
*@brief Manage the execution loop and the timeout ticks
*
*@param srv The main server_t struct
*/
static void loop_manager(server_t *srv)
{
	int nfds = 0;
	long long tick_b = get_time();
	static long long tick_e = 0;
	const long long timeout = (tick_e) ? (tick_b + (srv->game.frequence - \
	(tick_e - tick_b))) : (tick_b + srv->game.frequence);

	while (get_time() < timeout) {
		nfds = epoll_wait(srv->srv_epoll.epollfd, \
		srv->srv_epoll.events, MAX_EVENTS, (int) timeout - get_time());
		if (nfds == -1)
			close_and_msg(srv, "error: epoll_wait");
		for (int i = 0; i < nfds; ++i)
			manage_events(srv, i);
	}
	tick_e = get_time();
	exec_clients_actions(srv);
}

/**
*@brief Manage all socket and redistribute data to wanted fd
*
*@param srv Main server_t struct
*/
void socket_manager(server_t *srv)
{
	float freq = (float) 1 / (float) srv->game.frequence * 1000;

	INFO("Server's ready !");
	srv->game.frequence = (int) freq;
	generate_map(&(srv->game)); 
	while (true)
		loop_manager(srv);
}