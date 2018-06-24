/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Print Message
*/

/**
* @brief Print message file
*
* @file print_messages.c
* @author Hugon Bastien
* @date 05-05-2018
*/
#include "server.h"

/**
* @brief Close the server's fd and display a message on error output
*
* @param srv Current server structure to close the server fd
* @param msg The message to print
* @return int Return EXIT_FAILURE (84)
*/
int close_and_msg(server_t *srv, char *msg)
{
	close(srv->srv_epoll.socket.fd);
	ERROR(msg);
	return (EXIT_FAILURE);
}