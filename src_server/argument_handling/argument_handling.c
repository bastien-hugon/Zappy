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
*@brief print the executable help message
*
*/
void print_help(void)
{
	printf("USAGE: ./zappy_server -p port -x width -y height -n name1");
	printf(" name2 ... -c clientsNb -f freq\n");
	printf("\tport\tis the port number\n");
	printf("\twidth\tis the width of the world\n");
	printf("\theight\tis the height of the world\n");
	printf("\tnameX\tis the name of the team X\n");
	printf("\tclientsNb\tis the number of authorized clients per team\n");
	printf("\tfreq\tis the reciprocal of time unit for execution ");
	printf("of actions\n");
}

/**
*@brief search if the option -help is used
*
* @param argc the arguments count
* @param argv the arguments values
* @return true if the option -help was found
* @return false othwerwise
*/
bool handle_help(int argc, char **argv)
{
	int i = 0;

	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-help") == 0) {
			print_help();
			return (true);
		}
	}
	return (false);
}

/**
* @brief handle the options of the program
*
* @param server the server to modify
* @param option the current option
* @param opt the option
* @return false in case of an error
*/
bool handle_option(server_t *server, int option, char *opt)
{
	switch (option) {
		case 'p':
			sscanf(opt, "%d", (int *)&server->srv_epoll.port);
			break;
		case 'x':
			sscanf(opt, "%d", (int *)&server->game.width);
			break;
		case 'y':
			sscanf(opt, "%d", (int *)&server->game.height);
			break;
		case 'f':
			sscanf(opt, "%d", (int *)&server->game.frequence);
			break;
		case '?':
			fprintf(stderr, "Unknown option `-%c'.\n", option);
			return (false);
	}
	return (true);
}

/**
* @brief handle the arguments and fill a server_t struct
*
* @param server the server to fill
* @param argc the arguments count
* @param argv the arguments values
* @return true if there is no error
* @return false in case of an error
*/
bool handle_args(server_t *server, int argc, char **argv) {
	int c;

	while ((c = getopt (argc, argv, "p:x:y:n:c:f:")) != -1) {
		if (handle_option(server, c, optarg) == false)
			return (false);
	}
	return (true);
}
