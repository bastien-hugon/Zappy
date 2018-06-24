/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation command function
*/

/**
*@brief incantation command function
*@file incantation_command.c
*/

#include "server.h"

/**
*@brief send Elevation underway to all the concerned client on a tile 
*
*@param tile [in] the tile
*@param lvl [in] the level
*/
void send_elevation_underway(tile_t *tile, int lvl)
{
	client_t **client = tile->player;

	do {
		if (client != NULL && *client != NULL && \
			(*client)->level == lvl)
		send_message((*client)->socket.fd, "Elevation underway\n");
	} while (list_next(&client));
}

/**
* @brief the command used for terminate an incantation
*
* @param server [in] the server
* @param client [in] the client
* @return false in case of an error
*/
bool validate_incantation_command(server_t *server, client_t *client)
{
	int lvl = client->level;
	tile_t *tile = &server->game.map[client->pos.y][client->pos.x];
	client_t **clients = tile->player;
	bool was_ok = validate_incantation(tile, lvl);

	do {

		if (clients != NULL && *clients != NULL && \
			(*clients)->level == lvl + 1 && was_ok)
			send_message((*clients)->socket.fd, \
				"Current level: %d\n", (*clients)->level);
		if (clients != NULL && *clients != NULL && \
			(*clients)->level == lvl + 1 && was_ok == false)
			send_message((*clients)->socket.fd, "ko\n");
	} while (list_next(&clients));
	send_to_gfx(server, "pie %d %d %d %s\n", client->pos.x, \
		client->pos.y, client->id, was_ok ? "ok" : "ko");
	LOG("End of incatention ok: %d", was_ok);
	return (was_ok);
}

/**
* @brief the launch incantation command
*
* @param server [in] the server
* @param client [in] the client
* @return false on error
*/
bool incantation_command(server_t *server, client_t *client)
{
	int lvl = client->level;
	tile_t *tile = &server->game.map[client->pos.y][client->pos.x];

	if (check_incantation_conditions(tile, lvl) == false) {
		send_message(client->socket.fd, "ko\n");
		return (false);
	}
	send_elevation_underway(tile, lvl);
	LOG("send_elevation_underway done");
	force_command_for_client(client, INCANTATION_VALIDATE);
	LOG("force_command_for_client done");
	send_to_gfx(server, "pic %d %d %d %d\n", client->pos.x, \
		client->pos.y, client->level, client->id);
	LOG("Incantation started");
	return (true);
}
