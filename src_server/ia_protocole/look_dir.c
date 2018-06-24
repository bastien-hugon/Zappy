/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Look in dir
*/

#include "server.h"

/**
*@brief Look north
*
*@param srv [in] main server_t struct
*@param client [out] The client to send the vision
*@return true Message sent
*@return false Message not sent
*/
bool look_north(server_t *srv, client_t *client)
{
	char *buffer = malloc(sizeof(char) * 1);

	if (!buffer)
		return (false);
	buffer[0] = '\0';
	buffer = (realloc_concat(buffer, "[ "));
	for (int i = 0; i <= client->level; i++)
		for (uint j = 0; j < (uint) 1 + 2 * i; j++)
			buffer = add_tile_to_buff(srv, client->pos.x - i + j, \
			client->pos.y - i, buffer);
	buffer[strlen(buffer) - 2] = ' ';
	buffer[strlen(buffer) - 1] = ']';
	if (!send_message(client->socket.fd, realloc_concat(buffer, "\n")))
		return (send_message(client->socket.fd, "ko\n"));
	return (true);
}

/**
*@brief Look north
*
*@param srv [in] main server_t struct
*@param client [in] The client to send the vision
*@return true Message sent
*@return false Message not sent
*/
bool look_west(server_t *srv, client_t *client)
{
	char *buffer = malloc(sizeof(char) * 1);

	if (!buffer)
		return (false);
	buffer[0] = '\0';
	buffer = (realloc_concat(buffer, "[ "));
	for (int i = 0; i <= client->level; i++)
		for (int j = 2 * i; j >= 0; j--) {
			buffer = add_tile_to_buff(srv, client->pos.x + i, \
			client->pos.y - i + j, buffer);
		}
	buffer[strlen(buffer) - 2] = ' ';
	buffer[strlen(buffer) - 1] = ']';
	if (!send_message(client->socket.fd, realloc_concat(buffer, "\n")))
		return (send_message(client->socket.fd, "ko\n"));
	return (true);
}

/**
*@brief Look north
*
*@param srv [in] main server_t struct
*@param client [out] The client to send the vision
*@return true Message sent
*@return false Message not sent
*/
bool look_south(server_t *srv, client_t *client)
{
	char *buffer = malloc(sizeof(char) * 1);

	if (!buffer)
		return (false);
	buffer[0] = '\0';
	buffer = (realloc_concat(buffer, "[ "));
	for (int i = 0; i <= client->level; i++)
		for (int j = 2 * i; j >= 0; j--)
			buffer = add_tile_to_buff(srv, client->pos.x - i + j, \
			client->pos.y + i, buffer);
	buffer[strlen(buffer) - 2] = ' ';
	buffer[strlen(buffer) - 1] = ']';
	if (!send_message(client->socket.fd, realloc_concat(buffer, "\n")))
		return (send_message(client->socket.fd, "ko\n"));
	return (true);
}

/**
*@brief Look north
*
*@param srv [in] main server_t struct
*@param client [out] The client to send the vision
*@return true Message sent
*@return false Message not sent
*/
bool look_east(server_t *srv, client_t *client)
{
	char *buffer = malloc(sizeof(char) * 1);

	if (!buffer)
		return (false);
	buffer[0] = '\0';
	buffer = (realloc_concat(buffer, "[ "));
	for (int i = 0; i <= client->level; i++)
		for (uint j = 0; j < (uint) 1 + 2 * i; j++) {
			buffer = add_tile_to_buff(srv, client->pos.x + i, \
			client->pos.y - i + j, buffer);
		}
	buffer[strlen(buffer) - 2] = ' ';
	buffer[strlen(buffer) - 1] = ']';
	if (!send_message(client->socket.fd, realloc_concat(buffer, "\n")))
		return (send_message(client->socket.fd, "ko\n"));
	return (true);
}