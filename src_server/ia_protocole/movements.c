/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Movements
*/

/**
*@brief Client movements
*
*@file movements.c
*@author Hugon Bastien
*@date 20-06-2018
*/
#include "server.h"

/**
*@brief Move a client forward
*
*@param srv [out] The main server_t struct
*@param client [out] The client to move
*@return true If the client was moved
*@return false Otherwise
*/
bool client_forward(server_t *srv, client_t *client)
{
	list_remove(&(srv->game.map[client->pos.y][client->pos.x].player));
	switch (client->dir) {
		case EAST:
			client->pos.x = (client->pos.x + 1) % srv->game.width;
			break;
		case SOUTH:
			client->pos.y = (client->pos.y + 1) % srv->game.height;
			break;
		case WEST:
			client->pos.x = (int) (client->pos.x - 1 >= 0) ? \
			(client->pos.x - 1) : (srv->game.width - 1);
			break;
		case NORTH:
			client->pos.y = (int) (client->pos.y - 1 >= 0) ? \
			(client->pos.y - 1) : (srv->game.height - 1);
			break;
	}
	list_push(&(srv->game.map[client->pos.y][client->pos.x].player), \
	&client);
	return (send_message(client->socket.fd, "ok\n%d %d\n", client->pos.x, client->pos.y));
}

/**
*@brief Change the direction of a client
*
*@param srv [in] The main server_t struct
*@param client [out] The client to move
*@return true If the client was moved
*@return false Otherwise
*/
bool client_right(server_t *srv, client_t *client)
{
	(void)srv;
	client->dir = (client->dir + 1) % 4;
	return (send_message(client->socket.fd, "ok\n%d\n", client->dir));
}

/**
*@brief Change the direction of a client
*
*@param srv [in] The main server_t struct
*@param client [out] The client to move
*@return true If the client was moved
*@return false Otherwise
*/
bool client_left(server_t *srv, client_t *client)
{
	(void)srv;
	if (client->dir == 0)
		client->dir = 3;
	else
		client->dir--;
	return (send_message(client->socket.fd, "ok\n%d\n", client->dir));
}