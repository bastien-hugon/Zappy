/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** argument_handling
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include "server.h"

/*!
** @brief argumement handling functions
** @file argument_handling.c
*/

/**
* @brief handle the options of the program
*
* @param server [out] the server to modify
* @param option [in] the current option
* @param opt [in] the option
* @return false in case of an error
*/
bool handle_option(server_t *server, int option, char *opt, uint *nb_players)
{
	switch (option) {
		case 'p':
			sscanf(opt, "%d", (int *)&server->srv_epoll.port);
			return (true);
		case 'x':
			sscanf(opt, "%d", (int *)&server->game.width);
			return (true);
		case 'y':
			sscanf(opt, "%d", (int *)&server->game.height);
			return (true);
		case 'f':
			sscanf(opt, "%d", (int *)&server->game.frequence);
			return (true);
		case 'c':
			sscanf(opt, "%d", (int *)nb_players);
			return (true);
		default:
			fprintf(stderr, "Unknown option `-%c'.\n", option);
			return (false);
	}
}

/**
*@brief handle the teams option
*
*@param server [out] the server to init
*@param argc [in] the arguments count
*@param argv [in] the arguments values
*/
void handle_teams(server_t *server, int argc, char **argv)
{
	team_t team;

	optind--;
	for ( ; optind < argc && *argv[optind] != '-'; optind++){
		team.name = argv[optind];
		list_push(&server->game.teams, &team);
	}
}

/**
*@brief set the free slot of the team to the -c argument
*
*@param server [out] the server
*@param nb_player_by_team [in] the nb of free slot by team
*/
static void init_nb_client_by_team(server_t *server, uint nb_player_by_team)
{
	team_t *team = server->game.teams;

	do {
		if (team != NULL) {
			team->free_slots = nb_player_by_team;
		}
	} while (list_next(&team));
}

/**
* @brief handle the arguments and fill a server_t struct
*
* @param server [out] the server to fill
* @param argc [in] the arguments count
* @param argv [in] the arguments values
* @return true if there is no error
* @return false in case of an error
*/
bool handle_args(server_t *server, int argc, char **argv) {
	int c;
	uint nb_client_by_team = 0;

	memset(server, 0, sizeof(server_t));
	server->game.frequence = 100;
	while ((c = getopt(argc, argv, "p:x:y:n:c:f:")) != -1) {
		if (c == 'n')
			handle_teams(server, argc, argv);
		else if (false == \
			handle_option(server, c, optarg, &nb_client_by_team)) {
			return (false);
		}
	}
	init_nb_client_by_team(server, nb_client_by_team);
	return (true);
}
