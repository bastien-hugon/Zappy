/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Exec Client Actions
*/

#include "server.h"

/**
* @brief Get the associated client for a socket fd
*
* @param srv the server
* @param fd the client file descriptor
* @return client_t * the client
*/
client_t *get_client_for_fd(server_t *srv, int fd)
{
	client_t *client = srv->game.clients;

	do {
		if (client->socket.fd == fd)
			return (client);
	} while (list_next(&client));
	return (NULL);
}

void exec_client_actions(server_t *srv)
{
	LOG("Exec client actions");
}