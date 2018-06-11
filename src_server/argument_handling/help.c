/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** help argument handling functions
*/

/*!
** @brief help argument handling functions
** @file argument_handling.c
*/

#include "server.h"

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