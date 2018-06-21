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

#include <strings.h>
#include "server.h"

command_t commands[] = {
 	{"forward", FORWARD, 7, client_forward},
 	{"right", RIGHT, 7, client_right},
 	{"left", LEFT, 7, client_left},
	{"inventory", INVENTORY, 1, client_inventory},
	{"msz", GFX_MSZ, 0, gfx_map_size},
	{"bct", GFX_BCT, 0, gfx_map_tile},
	{"mct", GFX_MCT, 0, gfx_map_tiles},
	{"ppo", GFX_PPO, 0, gfx_ppo},
	{"Broadcast", BROADCAST, 7, send_message_command}
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
		if (strncasecmp(commands[i].cmd_str, str, \
			strlen(commands[i].cmd_str)) == 0)
			return (&commands[i]);
	}
	return (NULL);
}
