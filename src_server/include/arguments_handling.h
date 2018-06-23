/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** argument_handling
*/

#ifndef ARGUMENT_HANDLING_H_
	#define ARGUMENT_HANDLING_H_

	#include "server.h"

	bool handle_help(int argc, char **argv);
	bool handle_args(server_t *server, int argc, char **argv);
	bool check_arguments(server_t *server);

#endif /* !ARGUMENT_HANDLING_H_ */
