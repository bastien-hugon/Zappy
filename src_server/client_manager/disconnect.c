/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** disconnect a client
*/

/**
* @brief disconnect a client
* @file disconnect.c
*/

#include "server.h"

void disconnect_client(server_t *server, client_t *client)
{
	close(client->socket.fd);
	list_remove(&client);
	if (client == server->game.clients)
		server->game.clients = NULL;
}

void kill_client(server_t *server, client_t *client)
{
	WARN("Killing client fd #%d", client->socket.fd);
	send_message(client->socket.fd, "dead\n");
	disconnect_c_client(server, client->socket.fd);
}