/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Information related to the map
*/

/**
*@brief Send all data related to the map in the GFX protocole
*
*@file map_info.c
*@author Hugon Bastien
*@date 15-06-2018
*/
#include "server.h"

/**
*@brief Send the map's size to the GFX Client
*
*@param srv [out] The main server_t struct
*@param user [out] The client
*@return true If the message is sent
*@return false If the message isn't sent
*/
bool gfx_map_size(server_t *srv, client_t *user)
{
	return (send_message(user->socket.fd, "msz %d %d\n", \
	srv->game.width, srv->game.height));
}

/**
*@brief Send a specified tile to the GFX client
*
*@param srv [in] The main server_t struct
*@param fd [in] The client fd
*@param x [in] The X coord tile
*@param y [in] The Y coor Tile
*@return true If the message is sent
*@return false If the message isn't sent
*/
static bool gfx_send_tile(const server_t *srv, const int fd, \
const int x, const int y)
{
	return (send_message(fd, "bct %d %d %d %d %d %d %d %d %d\n", x, y, \
	srv->game.map[y][x].inventory[0], \
	srv->game.map[y][x].inventory[1], srv->game.map[y][x].inventory[2], \
	srv->game.map[y][x].inventory[3], srv->game.map[y][x].inventory[4], \
	srv->game.map[y][x].inventory[5], srv->game.map[y][x].inventory[6]));
}

/**
*@brief Send a map Tile to the GFX client
*
*@param srv [out] The main server_t struct
*@param user [out] The client
*@return true If the message is sent
*@return false If the message isn't sent
*/
bool gfx_map_tile(server_t *srv, client_t *user)
{
	int x;
	int y;
	char **cmd = explode(user->cmd_queue[0], " ");

	if (cmd[1] == NULL || cmd [2] == NULL || atoi(cmd[1]) < 0 || \
	(uint) atoi(cmd[1]) >= srv->game.width || atoi(cmd[2]) < 0 || \
	(uint) atoi(cmd[2]) >= srv->game.height)
		return (send_message(user->socket.fd, "ko\n"));
	x = atoi(cmd[1]);
	y = atoi(cmd[2]);
	return (gfx_send_tile(srv, user->socket.fd, x, y));
}

/**
*@brief Send all the map Tiles to the GFX client
*
*@param srv [out] The main server_t struct
*@param user [out] The client
*@return true If the message is sent
*@return false If the message isn't sent
*/
bool gfx_map_tiles(server_t *srv, client_t *user)
{
	for (uint y = 0; y < srv->game.height; y++)
		for (uint x = 0; x < srv->game.width; x++)
			gfx_send_tile(srv, user->socket.fd, x, y);
	return (true);
}