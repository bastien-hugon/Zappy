/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** command queue functions
*/

/**
*@brief command queue functions
*
*@file command_queue.c
*@author Fabre Lucas
*@date 11-06-2018
*/

#include "server.h"

/**
* @brief register a command in the client command queue
*
* @param client the client
* @param command the command str
* @return true if the command was added in the queue
* @return false if the queue is allready full
*/
bool register_command(client_t *client, char *command)
{
	for (int i = 0; i < NB_CMD_QUEUE; i++) {
		if (client->cmd_queue[i] == NULL) {
			client->cmd_queue[i] = command;
			return (true);
		}
	}
	return (false);
}
