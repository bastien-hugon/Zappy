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
static void manage_events(server_t *srv, int i)
{
	client_t user;

	if (srv->srv_epoll.events[i].data.fd == srv->srv_epoll.socket.fd) {
		create_user(&user);
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
		LOG("New user connected with fd: %d", user.socket.fd);
	} else {
		call_worker(srv, srv->srv_epoll.events[i].data.fd);
	}
}

/**
*@brief Get the time object
*
*@return long The current timestamp in ms
*/
static long get_time(void)
{
	long ms;
	struct timespec spec;

	clock_gettime(CLOCK_REALTIME, &spec);
	ms = round(spec.tv_nsec / 1.0e6);
	return (ms);
}

/**
*@brief Manage the execution loop and the timeout ticks
*
*@param srv The main server_t struct
*/
static void loop_manager(server_t *srv)
{
	int nfds = 0;
	long tick_b = get_time();
	static long tick_e = 0;
	int timeout = (tick_e != 0) ? (TICKS - (tick_e - tick_b)) : (-1);

	if ((tick_e - tick_b) < TICKS) {
		nfds = epoll_wait(srv->srv_epoll.epollfd, \
		srv->srv_epoll.events, MAX_EVENTS, timeout);
		if (nfds == -1)
			close_and_msg(srv, "error: epoll_wait");
		for (int i = 0; i < nfds; ++i)
			manage_events(srv, i);
	}
	exec_client_actions(srv);
	tick_e = get_time();
}

static void print_map(tile_t **map)
{
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++)
			printf("%d%d%d%d%d%d%d ", map[y][x].inventory[0], map[y][x].inventory[1], map[y][x].inventory[2], map[y][x].inventory[3], map[y][x].inventory[4], map[y][x].inventory[5], map[y][x].inventory[6]);
		printf("\n");
	}
}

/**
*@brief Manage all socket and redistribute data to wanted fd
*
*@param srv Main server_t struct
*/
void socket_manager(server_t *srv)
{
	INFO("Server's ready !");
	srv->game.height = 10;
	srv->game.width = 10;
	srand(time(NULL));
	generate_map(&(srv->game));
	print_map(srv->game.map);
	while (true)
		loop_manager(srv);
}