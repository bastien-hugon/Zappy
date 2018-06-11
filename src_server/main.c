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


/*!
** @brief zappy main function file
** @file main.c
*/

/**
* @brief the server main function
*
* @param argc argc the arguments count
* @param argv argv the arguments values
* @return int 0 onn success 84 on failure
*/
int main(int argc, char **argv)
{
	server_t server;

	if (handle_help(argc, argv))
		return (EXIT_SUCCESS);
	if (handle_args(&server, argc, argv) == false)
		return (EXIT_FAILURE);
	init_server(&server);
	init_epoll(&server);
	socket_manager(&server);
	return (EXIT_SUCCESS);
}