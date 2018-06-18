/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Client Manager Header
*/

#ifndef CLIENT_MANAGER_H_
	#define CLIENT_MANAGER_H_

	#include "server.h"

	void create_user(const client_t *user, const server_t *srv);
	void exec_client_actions(server_t *srv);
	client_t *get_client_for_fd(server_t *srv, int fd);
	bool send_message(const int fd, const char *format, ...);
	bool broadcast(const server_t *srv, const char *format, ...);

#endif /* !CLIENT_MANAGER_H_ */
