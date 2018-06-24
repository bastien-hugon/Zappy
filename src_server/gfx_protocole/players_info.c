/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Information related to the map
*/

/**
*@brief Send all data related to the map in the GFX protocole
*
*@file player_info.c
*@author Hugon Bastien
*@date 18-06-2018
*/
#include "server.h"

/**
*@brief Get an user by his UID
*
*@param uid [in] The uid of an user
*@param tile [in] The tile to check on
*@return client_t *The client found
*/
static client_t *gfx_get_usr(uint uid, tile_t tile)
{
	client_t **list = tile.player;

	do {
		if (list != NULL && (*list)->id == uid)
			return (*list);
	} while (list_next(&list));
	return (NULL);
}

/**
*@brief Send the map's size to the GFX Client
*
*@param srv [in] The main server_t struct
*@param fd [in] The client fd
*@param cmd [in] The client command
*@return true If the message is sent
*@return false If the message isn't sent
*/
bool gfx_ppo(server_t *srv, client_t *user)
{
	char **cmd = explode(user->cmd_queue[0], " ");
	client_t *player = NULL;
	uint user_id;
	char dir[4][2] = {"1", "2", "3", "4"};

	if (!cmd[1] || atoi(cmd[1]) < 0)
		return (send_message(user->socket.fd, "ko\n"));
	user_id = atoi(cmd[1]);
	for (uint y = 0; y < srv->game.height && !player; y++) {
		for (uint x = 0; x < srv->game.width && !player; x++) {
			player = gfx_get_usr(user_id, srv->game.map[y][x]);
			(player) ? (send_message(user->socket.fd, \
			"ppo %d %d %d %s\n", \
			user_id, x, y, dir[player->dir])) : 0;
			player = (player) ? (player) : (NULL);
		}
	}
	return (player == NULL);
}

/**
*@brief Send the map's size to the GFX Client
*
*@param srv [in] The main server_t struct
*@param fd [in] The client fd
*@param cmd [in] The client command
*@return true If the message is sent
*@return false If the message isn't sent
*/
bool gfx_send_ppo(server_t *srv, client_t *user)
{
	client_t *player = get_gfx_client(srv);
	char *dir[4] = {"1", "2", "3", "4"};

	if (player)
		send_message(player->socket.fd, "ppo %d %d %d %s\n", \
		user->id, user->pos.x, user->pos.y, dir[user->dir]);
	return (player != NULL);
}

/**
*@brief Connection of a new user
*
*@param srv [in] The main server_t struct
*@param user [in] The user connected
*@return true If the message is sent
*@return false If the message isn't sent
*/
bool gfx_pnw(server_t *srv, client_t *user)
{
	client_t *gfx = get_gfx_client(srv);
	char dir[4][2] = {"1", "2", "3", "4"};

	if (gfx == NULL || !user || user->is_gfx)
		return (false);
	WARN("toto");
	return (send_message(gfx->socket.fd, "pnw %d %d %d %s 1 %s\n", \
	user->id, user->pos.x, user->pos.y, dir[user->dir], user->team->name));
}