/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** sound_command
*/

/*!
** @brief sound command functions
** @file sound_command.c
*/

#include "server.h"

bool send_message_command(server_t *server, client_t *client)
{
	return send_sound(server, client, client->cmd_queue[0] +
		strlen("Broadcast "));
}
