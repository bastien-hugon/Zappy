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
	bool send_to_gfx(server_t *server, const char *format, ...);
	bool broadcast(const server_t *srv, const char *format, ...);
	void join_team(server_t *srv, client_t *client, char *str);
	void disconnect_client(server_t *srv, client_t *client);
	void kill_client(server_t *srv, client_t *client);
	bool disconnect_c_client(server_t *srv, int fd);

#endif /* !CLIENT_MANAGER_H_ */
