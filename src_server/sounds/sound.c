/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** sound functions
*/

/*!
** @brief sound functions
** @file sound.c
*/

#include <math.h>
#include "server.h"

/**
* @brief send a sound to a client
*
* @param server the server
* @param sender the sender
* @param sound the sound message
* @param receiver the receiver of the message
*/
static bool send_sound_to_client(server_t *server, client_t *sender, char *sound, client_t *receiver)
{
	int lower_x;
	int lower_y;

	// si le modulo est supérieur a la taille de la map
	int abs_dist_send_rec_x = abs((int)(receiver->pos.x - sender->pos.x));
	if (abs_dist_send_rec_x % server->game.width > receiver->pos.x - sender->pos.x) {
		lower_x = receiver->pos.x - sender->pos.x % server->game.width;
	} else {
		lower_x = receiver->pos.x - sender->pos.x;
	}

	// with y
	int abs_dist_send_rec_y = abs((int)(receiver->pos.y - sender->pos.y));
	if (abs_dist_send_rec_y % server->game.width > receiver->pos.y - sender->pos.y) {
		lower_y = receiver->pos.y - sender->pos.y % server->game.width;
	} else {
		lower_y = receiver->pos.y - sender->pos.y;
	}

	int coef_directeur = ( lower_y ) / ( lower_x );

	if (coef_directeur == 1 || coef_directeur == -1) {
		// DIAGONALE
		if (lower_y > 0 && lower_x > 0) {
			return (2);
		} else {
			return (6);
		}
		if (lower_y < 0) {
			return (8);
		} else {
			return (4);
		}
	} else {
		// AUTRE
		if (1 < coef_directeur && coef_directeur > -1) {
			if (lower_x < 0)
				return (5);
			else
				return (1);
		}
		if (2 < coef_directeur) {
			if (lower_y < 0)
				return (7);
			else
				return (3);
		}
	}
	return (-1);
}

/**
* @brief send the sound to all the player at a position
*
* @param server the server
* @param sender the sender
* @param sound the sound message
* @param pos the position
*/
bool send_sound_to_tile(server_t *server, client_t *sender, char *sound, pos_t pos)
{
	client_t *client = server->game.clients;

	do {
		if (client)
			send_message_to_client(server, sender, sound, client);
	} while (list_next(&client));
}

/**
*@brief send a sound to all clients
*
*@param server the server
*@param sender the sender
*@param sound the message
*/
bool send_sound(server_t *server, client_t *sender, char *sound)
{
	pos_t pos = {0, 0};

	for (pos = (pos_t){0, 0}; pos.y < server->game.height; pos.y++) {
		for ( ; pos.x < server->game.width; pos.x++) {
			send_sound_to_tile(server, sender, sound, pos);
		}
	}
	return (true);
}