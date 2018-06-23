/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Fill and refill the map
*/

/**
*@brief Fill and Refill the map
*
*@file fill_refill.c
*@author Hugon Bastien
*@date 08-06-2018
*/
#include "server.h"


/**
*@brief init a tile
*
*@param tile The tile to init
*/
static void init_tile(tile_t *tile)
{
	tile->egg = NULL;
	tile->player = NULL;
	for (int i = 0; i < NB_RESSOURCE; i++)
		tile->inventory[i] = 0;
}

/**
*@brief Init the map tiles
*
*@param game The game_t struct to init
*/
static void init_map(game_t *game)
{
	for (int y = 0; y < (int) game->height; y++)
		for (int x = 0; x < (int) game->width; x++)
			init_tile(&(game->map[y][x]));
}

/**
*@brief Fill a tile
*
*@param tile The tile to fill
*/
static void fill_tile(tile_t *tile)
{
	for (int i = 0; i < NB_RESSOURCE; i++)
		if (is_lucky(i))
			tile->inventory[i]++;
}

/**
*@brief Fill the map
*
*@param game The game_t struct
*/
void fill_map(game_t *game)
{
	init_map(game);
	for (int y = 0; y < (int) game->height; y++)
		for (int x = 0; x < (int) game->width; x++)
			fill_tile(&(game->map[y][x]));
}

/**
*@brief Reffill the map
*
*@param game The game_t struct
*/
void refill_map(game_t *game)
{
	static int i = 0;

	for (int y = 0; y < (int) game->height && !(i % 100); y++)
		for (int x = 0; x < (int) game->width; x++)
			fill_tile(&(game->map[y][x]));
	i++;
}