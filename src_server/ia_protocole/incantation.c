/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation command function
*/

/**
*@brief incantation command function
*@file incantation.c
*/

#include "server.h"

static uint incantation_requirements[7][NB_RESSOURCE] = {
	{1, 1, 0, 0, 0, 0, 0},
	{2, 1, 1, 1, 0, 0, 0},
	{2, 2, 0, 1, 0, 2, 0},
	{4, 1, 1, 2, 0, 1, 0},
	{4, 1, 2, 1, 3, 0, 0},
	{6, 1, 2, 3, 0, 1, 0},
	{6, 2, 2, 2, 2, 2, 1}
};

/**
* @brief Get the nb players on tile of a specific lvl
*
* @param tile [in] the tile
* @param lvl [in] the required level
* @return int the number of client
*/
int get_nb_players_on_tile_of_lvl(tile_t *tile, int lvl)
{
	int ret = 0;
	client_t **client = tile->player;

	do {
		if (client != NULL && *client != NULL && \
			(*client)->level == lvl)
			ret++;
	} while (list_next(&client));
	return (ret);
}

/**
* @brief check the requirements for an incantation
*
* @param tile [in] the tile
* @param lvl [in] the lvl
* @return true if the requirement are met
*/
bool check_incantation_conditions(tile_t *tile, int lvl)
{
	bool ret = true;

	for (ressource_e res = LINEMATE; res < NB_RESSOURCE; res++)
		if (tile->inventory[res] == incantation_requirements[lvl - 1][res])
			ret = false;
	if (get_nb_players_on_tile_of_lvl(tile, lvl) == \
		incantation_requirements[lvl - 1])
		ret = false;
	LOG("the incantation comditions was %s", ret ? "ok" : "ko");
	return (ret);
}

/**
* @brief do the incantation
*
* @param tile [in] the tile
* @param lvl [in] the level
* @return true on ok
* @return false on ko
*/
bool validate_incantation(tile_t *tile, int lvl)
{
	client_t **client = tile->player;

	if (check_incantation_conditions(tile, lvl) == false)
		return (false);
	do {
		if (client != NULL && *client != NULL && \
			(*client)->level == lvl)
		(*client)->level++;
	} while (list_next(&client));
	for (ressource_e res = LINEMATE; res < NB_RESSOURCE; res++)
		tile->inventory[res] -= incantation_requirements[lvl - 1][res];
	LOG("the incantation was done");
	return (true);
}
