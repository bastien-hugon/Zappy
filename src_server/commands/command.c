/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** command functions
*/

/**
*@brief command functions
*
*@file command.c
*@author Fabre Lucas
*@date 15-06-2018
*/

#include "server.h"

bool je_sapelle_forward(server_t *server, client_t *client)
{
	(void)server;
	(void)client;
	LOG("JE FORWARD");
	return (true);
}

command_t commands[] = {
	{"forward", FORWARD, 1, je_sapelle_forward},
	{"msz", GFX_MSZ, 0, gfx_map_size},
	{"bct", GFX_BCT, 0, gfx_map_tile},
	{"mct", GFX_MCT, 0, gfx_map_tiles}
};

/**
*@brief transform a str in a command
*
*@param str the string
*@return command_t the command
*/
command_t *get_command_from_str(char *str)
{
	for (int i = 0; i < NB_CMDS; i++) {
		if (strncmp(commands[i].cmd_str, str, \
			strlen(commands[i].cmd_str)) == 0)
			return (&commands[i]);
	}
	return (NULL);
}
