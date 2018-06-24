/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Tile info
*/

#include "server.h"

/**
*@brief Realloc and concat strings
*
*@param s1 [in] Src str
*@param s2 [in] Add this
*@return char* result
*/
char *realloc_concat(char *s1, char *s2)
{
	size_t a = strlen(s1);
	size_t b = strlen(s2);
	int ab = a + b + 1;

	s1 = realloc(s1, ab);
	memcpy(s1 + a, s2, b + 1);
	return (s1);
}

/**
*@brief Get the tile object
*
*@param srv [in] Main server_t struct
*@param x [in] Get this x
*@param y [in] Get this y
*@return tile_t The tile found
*/
tile_t get_tile(server_t *srv, int x, int y)
{
	if (x < 0)
		x = (srv->game.width - (-1 * (0 - x)));
	x %= srv->game.width;
	if (y < 0)
		x = (srv->game.height - (-1 * (0 - y)));
	y %= srv->game.height;
	if (x >= srv->game.width)
		x = 0;
	if (y >= srv->game.height)
		y = 0;
	return (srv->game.map[y][x]);
}

/**
*@brief Add a tile to the buff.
*
*@param srv [in] Main server_t struct
*@param x [in] The x tile coord
*@param y [in] The y tile coord
*@param buffer [in] The buffer
*@return char* The buffer changed
*/
char *add_tile_to_buff(server_t *srv, int x, int y, char *buffer)
{
	tile_t tile = get_tile(srv, x, y);
	client_t **client = tile.player;
	bool space = false;
	char obj[7][10] = {"food", "linemate", "deraumere", "sibur", \
	"mendiane", "phiras", "thystame"};
	while (client != NULL) {
		(space) ? buffer = realloc_concat(buffer, " ") : 0;
		buffer = realloc_concat(buffer, "player");
		space = true;
		if (list_next(&client) == false)
			break;
	}
	for (int i = 0; i < NB_RESSOURCE; i++)
		for (int j = 0; (uint) j < tile.inventory[i]; j++) {
			(space) ? buffer = realloc_concat(buffer, " ") : 0;
			space = true;
			buffer = realloc_concat(buffer, obj[i]);
		}
	buffer = realloc_concat(buffer, ", ");
	return (buffer);
}