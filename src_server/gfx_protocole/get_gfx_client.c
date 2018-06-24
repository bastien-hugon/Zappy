/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Get GFX Client
*/

/**
*@brief Get GFX Client
*
*@file get_gfx_client.c
*@author Hugon Bastien
*@date 21-06-2018
*/
#include "server.h"

/**
*@brief Get the gfx client object
*
*@param srv [in] The main server_t struct
*@return client_t *The GFX Client found
*/
client_t *get_gfx_client(const server_t *srv)
{
	client_t *tmp = srv->game.clients;

	if (!tmp)
		return (NULL);
	do {
		if (tmp->is_gfx)
			return (tmp);
	} while (list_next(&tmp));
	return (NULL);
}