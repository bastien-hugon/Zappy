/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** funcions of the eject command
*/

/**
* @brief funcions of the eject command
* @file eject.c
*/

#include "server.h"

/**
* @brief get the absolute direction number for a dir
*
* @param dir [in] the direction (enum format)
* @return int the direction (the direction int format)
*/
int dir_to_absolute_direction(dir_e dir)
{
	switch (dir) {
		case (NORTH):
			return (3);
		case (SOUTH):
			return (7);
		case (EAST):
			return (1);
		case (WEST):
			return (5);
	}
}

/**
* @brief get the inverted direction
*
* @param dir [in] the base direction
* @return dir_e the inverted direction
*/
dir_e invert_dir(dir_e dir)
{
	switch (dir) {
		case (NORTH):
			return (SOUTH);
		case (SOUTH):
			return (NORTH);
		case (EAST):
			return (WEST);
		case (WEST):
			return (EAST);
	}
}

/**
* @brief send the eject message to the ejected clients
*
* @param client [in] the client who eject
* @param ejected_clients [in] the ejected clients list
*/
void send_message_to_ejected_clients_and_cancel(client_t *client, \
	client_t *ejected_clients)
{
	int direction = 0;
	int absolute_direction = invert_dir(dir_to_absolute_direction( \
		client->dir));

	do {
		if (ejected_clients != NULL) {
			direction = get_direction_by_player( \
				absolute_direction, ejected_clients);
			send_message(ejected_clients->socket.fd, "Eject %d", \
				direction);
			cancel_client_action(ejected_clients);
		}
	} while (list_next(&ejected_clients));
}

/**
*@brief remove a client * from a list of client *
*
*@param list [in] the list
*@param client [in] the client to remove
*@return client_t** [out] the new list
*/
static client_t **remove_client_from_list(client_t **list, client_t *client)
{
	client_t **tmp_client = list;
	do {
		if (tmp_client && *tmp_client == client) {
			list_remove(&tmp_client);
			if (tmp_client == NULL || tmp_client == list)
				return (NULL);
		}
	} while (list_next(&tmp_client));
	return (list);
}

/**
* @brief the eject command
*
* @param server [in] the server
* @param client [in] the client
* @return false in case of an error
*/
bool eject_command(server_t *server, client_t *client)
{
	tile_t *ejected_tile = &(server->game.map[client->pos.y]\
		[client->pos.x]);
	client_t **ejected_client_list = remove_client_from_list(\
		ejected_tile->player, client);

	if (ejected_client_list == NULL) {
		send_message(client->socket.fd, "ko\n");
		return ;
	} else {
		send_message_to_ejected_clients_and_cancel(client, \
			ejected_client_list);
	}
	return (true);
}
