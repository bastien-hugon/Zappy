/*
** EPITECH PROJECT, 2018
** MyIRC - Server
** File description:
** Call worker
*/

/**
*@brief Call wanted commands or send message
*
*@file call_worker.c
*@author Hugon Bastien
*@date 06-05-2018
*/

#include "server.h"

/**
*@brief Parse message and call functions
*
*@param [out] srv Main server_t struct
*@param [out] fd The client's fd who sent a message
*/
void call_worker(server_t *srv, int fd)
{
	client_t *client = get_client_for_fd(srv, fd);
	char *str = NULL;
	LOG("Event on fd: %d", fd);
	if (client == NULL)
		return ;
	if (circular_buffer_read(&client->buffer, fd) == false) {
		WARN("Fd #%d disconnected.", fd);
		disconnect_c_client(srv, fd);
		return ;
	}
	while (true) {
		str = circular_buffer_get_to(&client->buffer, "\n");
		if (str == CIRCULAR_BUFFER_NOT_FOUND || \
			str == CIRCULAR_BUFFER_ALLOCATION_ERROR)
			return ;
		if (!client->is_logged)
			join_team(srv, client, str);
		else
			register_command(client, str);
	}
}