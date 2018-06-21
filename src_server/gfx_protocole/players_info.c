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
*@return client_t* The client found
*/
static client_t *gfx_get_usr(uint uid, tile_t tile)
{
	client_t *list = tile.player;

	do {
		if (list != NULL && list->id == uid)
			return (list);
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

	if (!cmd[1] || atoi(cmd[1]) < 0)
		return (send_message(user->socket.fd, "ko\n"));
	user_id = atoi(cmd[1]);
	for (uint y = 0; y < srv->game.height && !player; y++) {
		for (uint x = 0; x < srv->game.width && !player; x++) {
			player = gfx_get_usr(user_id, srv->game.map[y][x]);
			(player) ? (send_message(user->socket.fd, \
			"ppo %d %d %d %d\n", \
			user_id, x, y, player->dir)) : (player = NULL);
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

	if (player)
		send_message(player->socket.fd, "ppo %d %d %d %d\n", \
		user->id, user->pos.x, user->pos.y, user->dir);
	return (player != NULL);
}