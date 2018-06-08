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
*@param user The user to initialise
*/
void create_user(client_t *user)
{
	user->team = NULL;
	user->size = sizeof(user->socket.s_in);
}