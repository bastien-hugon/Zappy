/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** get tile at direction
*/

/**
*@brief get tile at direction
*@file get_tile.c
*/

#include "server.h"

/**
*@brief Get the tile at a specific direction
*
*@param server [in] the server
*@param pos [in] the position
*@param dir [in] the direction
*@return tile_t* the tile
*/
tile_t *get_tile_at_dir(server_t *server, pos_t pos, dir_e dir)
{
	switch (dir) {
		case (NORTH):
			return (&(server->game.map[(pos.y != 0) ? \
				pos.y - 1: server->game.height][pos.x]));
		case (SOUTH):
			return (&(server->game.map[(pos.y != \
				server->game.height) ? pos.y + 1 : 0][pos.x]));
		case (EAST):
			return (&(server->game.map[pos.y][(pos.x != \
				server->game.width) ? pos.x + 1 : 0]));
		case (WEST):
			return (&(server->game.map[pos.y][(pos.x != 0) ? \
				pos.x - 1 : server->game.width]));
	}
}
