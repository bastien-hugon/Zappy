/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Client Manager Header
*/

#ifndef CLIENT_MANAGER_H_
	#define CLIENT_MANAGER_H_

	#include "server.h"

	void exec_clients_actions(server_t *srv);
	void create_user(client_t *user, server_t *srv);
	client_t *get_client_for_fd(server_t *srv, int fd);
	bool send_message(const int fd, const char *format, ...);
	bool broadcast(const server_t *srv, const char *format, ...);

#endif /* !CLIENT_MANAGER_H_ */
