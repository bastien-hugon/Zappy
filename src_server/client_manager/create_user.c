/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Create User
*/

#include "client_manager.h"

/**
*@brief Create a user object
*
*@param user [in] The user to initialise
*@param srv [in] The main server_t struct
*/
void create_user(client_t *user, server_t *srv)
{
	memset(user, 0, sizeof(client_t));
	circular_buffer_init(&user->buffer);
	user->team = NULL;
	user->size = sizeof(user->socket.s_in);
	user->id = srv->game.nb_players++;
}