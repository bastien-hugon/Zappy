/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Socket Manager Header
*/

#ifndef SOCKET_MANAGER_H_
	#define SOCKET_MANAGER_H_

	#include "server.h"

	#define TICKS (3000)

	void init_server(server_t *srv);
	void init_epoll(server_t *srv);
	void socket_manager(server_t *srv);
	int close_and_msg(server_t *srv, char *msg);
	void call_worker(server_t *srv, int fd);

#endif /* !SOCKET_MANAGER_H_ */
