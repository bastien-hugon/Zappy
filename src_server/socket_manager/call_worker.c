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
*@param srv Main server_t struct
*@param fd The client's fd who sent a message
*/
void call_worker(server_t *srv, int fd)
{
	client_t *client = get_client_for_fd(srv, fd);
	char *str = NULL;

	LOG("Event on fd: %d", fd);
	if (client == NULL)
		return ;
	if (circular_buffer_read(&client->buffer, fd) == false) {
		WARN("Error while reading in the buffer from fd: %d", fd);
		return ;
	}
	while (true) {
		str = circular_buffer_get_to(&client->buffer, "\r\n");
		if (str == CIRCULAR_BUFFER_NOT_FOUND || \
			str == CIRCULAR_BUFFER_ALLOCATION_ERROR)
			return;
		register_command(client, str);
	}
}
