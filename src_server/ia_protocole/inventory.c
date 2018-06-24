/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Client Inventory
*/

/**
*@brief Send the inventory
*
*@file inventory.c
*@author Hugon Bastien
*@date 21-06-2018
*/
#include "server.h"

/**
*@brief Send the inventory to the client
*
*@param srv [in] Main server_t struct
*@param client [in] The client
*@return true If the message was sent
*@return false The message wasn't sent
*/
bool client_inventory(server_t *srv, client_t *client)
{
	bool val = send_message(client->socket.fd, \
	"[ %s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d ]\n", \
	N_FOOD, client->inventory[0], N_LINEMATE, client->inventory[1], \
	N_DERAUMERE, client->inventory[2], N_SIBUR, client->inventory[3], \
	N_MENDIANE, client->inventory[4], N_PHIRAS, client->inventory[5], \
	N_THYSTAME, client->inventory[6]);

	(void)srv;
	if (!val)
		send_message(client->socket.fd, "ko\n");
	return (true);
}