/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Get Info
*/

#include "server.h"

/**
*@brief Send the free slot on the client's team
*
*@param srv The main server_t struct
*@param client The client
*@return true sent
*@return false Not sent
*/
bool client_nb_connect(server_t *srv, client_t *client)
{
	(void)srv;
	return (send_message(client->socket.fd, "%d\n", \
	client->team->free_slots));
}