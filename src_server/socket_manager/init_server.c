/*
** EPITECH PROJECT, 2018
** MyFTP - Server
** File description:
** Init Server
*/

/**
*@brief Initialise server's sockets
*
*@file init_server.c
*@author Hugon Bastien
*@date 06-05-2018
*/
#include "server.h"

/**
*@brief Initialise and fill server_t struct
*
*@param srv Server's struct
*@param port The listening port
*/
void init_server(server_t *srv)
{
	struct protoent *pe = getprotobyname("TCP");

	if ((srv->srv_epoll.socket.fd = socket(AF_INET, SOCK_STREAM, \
	pe->p_proto)) == -1)
		exit(error_msg("Cannot create socket"));
	srv->srv_epoll.socket.s_in.sin_family = AF_INET;
	srv->srv_epoll.socket.s_in.sin_port = htons(srv->srv_epoll.port);
	srv->srv_epoll.socket.s_in.s_addr = INADDR_ANY;
	if (bind(srv->srv_epoll.socket.fd, (const struct sockaddr *) \
	&(srv->srv_epoll.socket.s_in), sizeof(srv->srv_epoll.socket.s_in)))
		exit(close_and_msg(srv, "Cannot bind socket"));
	if (listen(srv->srv_epoll.socket.fd, MAX_EVENTS))
		exit(close_and_msg(srv, "Cannot listen"));
}