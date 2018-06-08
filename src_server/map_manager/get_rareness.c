/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Get Rareness
*/

#include "server.h"

/**
*@brief Get the rareness of a materials
*
*@param res The ressource to get the rareness
*@return uint The rareness percentage
*/
uint get_rareness(ressource_e res)
{
	uint ressources[NB_RESSOURCE] = {R_LINEMATE, R_DERAUMERE, \
	R_SIBUR, R_MENDIANE, R_PHIRAS, R_THYSTAME, R_FOOD};

	return (ressources[res]);
}

/**
*@brief Knowing if a ressource can be added to a Tile
*
*@param res The ressource
*@return true The ressource is lucky
*@return false The ressource isn't lucky
*/
bool is_lucky(ressource_e res)
{
	int luck = rand() % 100;

	return (get_rareness(res) < (uint) luck);
}