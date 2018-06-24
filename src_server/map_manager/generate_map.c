/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Generate Map
*/

/**
*@brief Generate the Map
*
*@file generate_map.c
*@author Hugon Bastien
*@date 08-06-2018
*/
#include "server.h"

/**
*@brief Allocate memory for the map
*
*@param game [out] The game_t struct
*@return true If the map is well allocated
*@return false If the allocation failed
*/
static bool allocate_map(game_t *game)
{
	if ((game->map = malloc(sizeof(tile_t *) * (game->height))) == NULL)
		return (false);
	for (int i = 0; i < (int) game->height; i++)
		if ((game->map[i] = malloc(sizeof(tile_t) * \
		(game->width))) == NULL)
			return (false);
	return (true);
}

/**
*@brief Generate the Tiled Map
*
*@param game [out] The game_t struct
*@return true If the map is well generated
*@return false If the generation failed
*/
bool generate_map(game_t *game)
{
	if (!allocate_map(game))
		return (false);
	fill_map(game);
	return (true);
}