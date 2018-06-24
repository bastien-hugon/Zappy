/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** check the arguments value
*/

/**
* @brief check the arguments value
* @file check_arguments.c
*/

#include "server.h"

static int check_map_size(server_t *server)
{
	if (server->game.height <= 0 || \
		server->game.width <= 0) {
		ERROR("Invalid map size");
		return (1);
	}
	if (server->game.height > 30 || \
		server->game.width > 30) {
		ERROR("The map size too large");
		return (1);
	}
	return (0);
}


/**
*@brief check the basic arguments
*
*@param server [in] the server
*@return int 1 in case of an invalid argument
*/
static int check_base_arguments(server_t *server)
{
	if (server->game.frequence <= 0) {
		ERROR("Invalid -f option");
		return (1);
	}
	if (server->srv_epoll.port == 0) {
		ERROR("Invalid -port argument");
		return (1);
	}
	return (0);
}

/**
*@brief check the team argument
*
*@param server [in] the server
*@return int 1 in case of an invalid argument
*/
static int check_team_arguments(server_t *server)
{
	team_t *team = server->game.teams;

	if (team == NULL || \
		team->free_slots == 0) {
		ERROR("Invalid teams");
		return (1);
	}
	do {
		if (team->name == NULL || team->free_slots <= 0) {
			ERROR("Invalid teams");
			return (1);
		}
	} while (list_next(&team));
	return (0);
}

/**
*@brief check the arguments
*
*@param server [in] the server
*@return false if the arguments are invalid
*/
bool check_arguments(server_t *server)
{
	int ret = 0;

	ret += check_base_arguments(server);
	ret += check_team_arguments(server);
	ret += check_map_size(server);
	if (ret == 0)
		return (true);
	else
		return (false);
}
