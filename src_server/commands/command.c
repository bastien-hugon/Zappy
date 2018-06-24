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

static command_t commands[] = {
 	{"forward", FORWARD, 7, client_forward},
 	{"right", RIGHT, 7, client_right},
 	{"left", LEFT, 7, client_left},
	{"inventory", INVENTORY, 1, client_inventory},
	{"Broadcast", BROADCAST, 7, send_message_command},
	{"Fork", FORK, 42, drop_egg_command},
	{"take", TAKE, 7, client_take},
	{"set", SET, 7, client_set},
	{"look", LOOK, 7, client_look},
	{"Eject", EJECT, 7, eject_command},
	{"Incantation", INCANTATION, 0, incantation_command},
	{"", INCANTATION_VALIDATE, 300, validate_incantation_command},
	{"Connect_nbr", NB_CONNECT, 0, client_nb_connect},
	{"bct", GFX_BCT, 0, gfx_map_tile},
	{"msz", GFX_MSZ, 0, gfx_map_size},
	{"mct", GFX_MCT, 0, gfx_map_tiles},
	{"ppo", GFX_PPO, 0, gfx_ppo}
};

/**
*@brief transform a str in a command
*
*@param str [in] the string
*@return command_t the command
*/
command_t *get_command_from_str(char *str)
{
	for (int i = 0; i < NB_CMDS; i++) {
		if (commands[i].cmd_str[0] != '\0' && \
			strncasecmp(commands[i].cmd_str, str, \
			strlen(commands[i].cmd_str)) == 0)
			return (&commands[i]);
	}
	return (NULL);
}

/**
* @brief force start a command for a client
*
* @param client [in] the client
* @param cmd [in] the command
*/
void force_command_for_client(client_t *client, cmd_e cmd)
{
	client->cmd = &commands[cmd];
	client->tick_left = commands[cmd].time;
}
