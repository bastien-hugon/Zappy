/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** main
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "server.h"

server_t server_g;

/*!
** @brief zappy main function file
** @file main.c
*/

void sighandler(int signum)
{
	(void)signum;
	stop_server(&server_g, NULL);
}

/**
* @brief the server main function
*
* @param argc argc the arguments count
* @param argv argv the arguments values
* @return int 0 onn success 84 on failure
*/
int main(int argc, char **argv)
{

	if (handle_help(argc, argv))
		return (EXIT_SUCCESS);
	if (handle_args(&server_g, argc, argv) == false)
		return (EXIT_FAILURE);
	if (check_arguments(&server_g) == false)
		return (EXIT_FAILURE);
	srand(time(NULL));
	init_server(&server_g);
	init_epoll(&server_g);
	signal(SIGINT, sighandler);
	socket_manager(&server_g);
	return (EXIT_SUCCESS);
}