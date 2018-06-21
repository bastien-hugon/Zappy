/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** the drop egg command
*/

/*!
** @brief the drop egg command
** @file command.c
*/

#include "server.h"

/**
*@brief the Fork command handler
*
*@param server [in] the server
*@param client [in] the client
*/
bool drop_egg_command(server_t *server, client_t *client)
{
	egg_t egg = { client->pos, \
		client->team, 600};
	bool ret = (list_push(&server->game.egg, &egg));

	LOG("New Egg at pos: {%d %d}, team: #%s", egg.pos.x, \
		egg.pos.y, egg.team->name);
	send_message(client->socket.fd, "ok\n");
	return (ret);
}