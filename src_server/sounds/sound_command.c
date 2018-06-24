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

/**
* @brief the function for send message
*
* @param server [in] the server
* @param client [in] the client
*/
bool send_message_command(server_t *server, client_t *client)
{
	bool ret;

	LOG("client #%d broadcasting: %s", client->id, client->cmd_queue[0] +
		strlen("Broadcast "));
	ret = send_sound(server, client, client->cmd_queue[0] +
		strlen("Broadcast "));
	LOG("Broadcast status: %d", ret);
	if (ret)
		send_message(client->socket.fd, "ok\n");
	else
		send_message(client->socket.fd, "ko\n");
	return (ret);
}
