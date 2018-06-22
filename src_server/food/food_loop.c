/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** food loop function
*/

/**
* @brief food loop function
*
* @file food_loop.c
* @author Fabre Lucas
* @date 22-06-2018
*/

#include "server.h"

void food_loop_client(server_t *server, client_t *client)
{
	client->food_tick--;
	if (client->food_tick == 0) {
		if (client->inventory[FOOD] == 0) {
			kill_client(server, client);
			return ;
		}
		client->inventory[FOOD]--;
		client->food_tick = 126;
	}
}

void food_loop(server_t *server)
{
	client_t *client = server->game.clients;

	do {
		if (client != NULL && client->is_logged && \
			client->is_gfx == false)
			food_loop_client(server, client);
	} while (list_next(&client));
}