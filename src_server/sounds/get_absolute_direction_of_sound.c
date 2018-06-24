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
#include <stdio.h>
#include "server.h"

/**
*@brief calculate the lower x value
*
*@param sender [in] the sender of the message
*@param receiver [in] the receiver of the message
*@return int the lower x
*/
int calc_lower_x(server_t *server, client_t *sender, client_t *receiver)
{
	int lower_x;
	int abs_dist_send_rec_x = abs((int)(receiver->pos.x - sender->pos.x));

	if ((int)(abs_dist_send_rec_x % server->game.width) > \
		(int)(receiver->pos.x - sender->pos.x)) {
		lower_x = receiver->pos.x - sender->pos.x % server->game.width;
	} else {
		lower_x = receiver->pos.x - sender->pos.x;
	}
	return (lower_x);
}

/**
*@brief calculate the lower y value
*
*@param sender [in] the sender of the message
*@param receiver [in] the receiver of the message
*@return int the lower y
*/
int calc_lower_y(server_t *server, client_t *sender, client_t *receiver)
{
	int lower_y;
	int abs_dist_send_rec_y = abs((int)(receiver->pos.y - sender->pos.y));

	if ((int)(abs_dist_send_rec_y % server->game.width) > \
		(int)(receiver->pos.y - sender->pos.y)) {
		lower_y = receiver->pos.y - sender->pos.y % server->game.width;
	} else {
		lower_y = receiver->pos.y - sender->pos.y;
	}
	return (lower_y);
}

/**
*@brief return the direction for a diagonale
*
*@param lower_x [in] lower x value
*@param lower_y [in] lower y value
*@return int 
*/
int calc_for_diagonale(int lower_x, int lower_y)
{
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
	return (-1);
}

/**
*@brief return the direction for a line
*
*@param lower_x [in] lower x value
*@param lower_y [in] lower y value
*@return int 
*/
int calc_for_others(int lower_x, int lower_y, int coef_directeur)
{
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
	return (-1);
}

/**
* @brief send a sound to a client
*
* @param server [in] the server
* @param sender [in] the sender
* @param receiver [in] the receiver of the message
*/
int get_absolute_direction_of_sound(server_t *server, client_t *sender,\
	client_t *receiver)
{
	int lower_x = calc_lower_x(server, sender, receiver);
	int lower_y = calc_lower_y(server, sender, receiver);
	int coef_directeur = ( lower_y ) / ((lower_x == 0 ? -1 : lower_x));

	if (lower_x == 0)
		return (-1);
	if (coef_directeur == 1 || coef_directeur == -1) {
		return (calc_for_diagonale(lower_x, lower_y));
	} else {
		return (calc_for_others(lower_x, lower_y, coef_directeur));
	}
	return (-1);
}
