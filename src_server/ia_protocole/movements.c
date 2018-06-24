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
*@brief Send OK to client and PPO command to GFX Client
*
*@param srv [in] Main server_t struct
*@param fd [in] The client fd
*@return true If the message is sent
*@return false If the message isn't sent
*/
static bool send_to_gfx_ppo(server_t *srv, client_t *client)
{
	gfx_send_ppo(srv, client);
	return (send_message(client->socket.fd, "ok\n"));
}

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
			client->pos.x = (client->pos.x - 1 >= 0) ? \
			((uint) client->pos.x - 1) : ((srv->game.width - 1));
			break;
		case NORTH:
			client->pos.y = (client->pos.y - 1 >= 0) ? \
			((uint) client->pos.y - 1) : (srv->game.height - 1);
			break;
	}
	list_push(&(srv->game.map[client->pos.y][client->pos.x].player), \
	&client);
	return (send_to_gfx_ppo(srv, client));
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
	return (send_to_gfx_ppo(srv, client));
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
	return (send_to_gfx_ppo(srv, client));
}