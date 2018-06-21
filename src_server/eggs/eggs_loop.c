/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** eggs main loop functions
*/

/*!
** @file eggs_loop.c
** @brief eggs main loop functions
*/

#include "server.h"


/**
*@brief single egg main loop executed each tickg 
*
*@param server 
*@param egg 
*/
void egg_loop(egg_t *egg)
{
	if (egg->tick_left > 0) {
		egg->tick_left--;
		if (egg->tick_left == 0) {
			LOG("Egg ready at pos: {%d %d}, team: #%s", \
				egg->pos.x, egg->pos.y, egg->team->name);
			egg->team->free_slots++;
		}
	}
}

/**
*@brief the eggs main loop executed each tick
*
*@param server [out] the server
*/
void eggs_loop(server_t *server)
{
	egg_t *egg = server->game.egg;
	do {
		if (egg != NULL)
			egg_loop(egg);
	} while (list_next(&egg));
}