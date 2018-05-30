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
	users_t *curr = get_user_by_fd(srv, fd);
	char buffer[BUFF_SIZE];
	int rd = read(fd, &buffer, BUFF_SIZE - 1);

	if (rd != -1) {
		buffer[rd] = '\0';
		if (cb_add_data(curr, buffer))
			exec_user_command(srv, curr);
	}
}