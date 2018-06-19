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
*@param user [out] The user to initialise
*@param srv [out] The main server_t struct
*/
void create_user(client_t *user, server_t *srv)
{
	memset(user, 0, sizeof(client_t));
	circular_buffer_init(&user->buffer);
	user->team = NULL;
	user->size = sizeof(user->socket.s_in);
	user->id = srv->game.nb_players++;
	user->is_gfx = false;
	user->is_logged = false;
}