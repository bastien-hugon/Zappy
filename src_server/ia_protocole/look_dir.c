/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Look in dir
*/

#include "server.h"

char *realloc_concat(char *s1, char *s2)
{
	size_t a = strlen(s1);
	size_t b = strlen(s2);
	int ab = a + b + 1;

	s1 = realloc(s1, ab);
	memcpy(s1 + a, s2, b + 1);
	return (s1);
}

tile_t get_tile(server_t *srv, int x, int y)
{
	if (x < 0)
		x = (srv->game.width - (-1 * (0 - x)));
	x %= srv->game.width;
	if (y < 0)
		x = (srv->game.height - (-1 * (0 - y)));
	y %= srv->game.height;
	return (srv->game.map[y][x]);
}

char *add_tile_to_buff(server_t *srv, int x, int y, char *buffer)
{
	tile_t tile = get_tile(srv, x, y);
	client_t *client = tile.player;
	bool space = false;
	char obj[7][10] = {"food", "linemate", "deraumere", "sibur", \
	"mendiane", "phiras", "thystame"};
	while (client != NULL) {
		(space) ? buffer = realloc_concat(buffer, " ") : 0;
		buffer = realloc_concat(buffer, "player");
		space = true;
		if (list_next(&client) == false)
			break;
	}
	for (int i = 0; i < NB_RESSOURCE; i++)
		for (int j = 0; j < tile.inventory[i]; j++) {
			(space) ? buffer = realloc_concat(buffer, " ") : 0;
			space = true;
			buffer = realloc_concat(buffer, obj[i]);
		}
	buffer = realloc_concat(buffer, ", ");
	return (buffer);
}

bool look_north(server_t *srv, client_t *client)
{
	char *buffer = malloc(sizeof(char) * 1);

	if (!buffer)
		return (false);
	buffer[0] = '\0';
	buffer = (realloc_concat(buffer, "[ "));
	for (int i = 0; i <= client->level; i++)
		for (uint j = 0; j < 1 + 2 * i; j++)
			buffer = add_tile_to_buff(srv, client->pos.x - i + j, \
			client->pos.y, buffer);
 	buffer[strlen(buffer) - 2] = ' ';
	buffer[strlen(buffer) - 1] = ']';
	return (send_message(client->socket.fd, realloc_concat(buffer, "\n")));
}

bool look_east(server_t *srv, client_t *client)
{
	char *buffer = malloc(sizeof(char) * 1);

	if (!buffer)
		return (false);
	buffer[0] = '\0';
	buffer = (realloc_concat(buffer, "[ "));
	for (int i = 0; i <= client->level; i++)
		for (uint j = 0; j < 1 + 2 * i; j++)
			buffer = add_tile_to_buff(srv, client->pos.x - i + j, \
			client->pos.y, buffer);
 	buffer[strlen(buffer) - 2] = ' ';
	buffer[strlen(buffer) - 1] = ']';
	return (send_message(client->socket.fd, realloc_concat(buffer, "\n")));
}

bool look_south(server_t *srv, client_t *client)
{
	char *buffer = malloc(sizeof(char) * 1);

	if (!buffer)
		return (false);
	buffer[0] = '\0';
	buffer = (realloc_concat(buffer, "[ "));
	for (int i = 0; i <= client->level; i++)
		for (uint j = 0; j < 1 + 2 * i; j++)
			buffer = add_tile_to_buff(srv, client->pos.x - i + j, \
			client->pos.y, buffer);
 	buffer[strlen(buffer) - 2] = ' ';
	buffer[strlen(buffer) - 1] = ']';
	return (send_message(client->socket.fd, realloc_concat(buffer, "\n")));
}

bool look_west(server_t *srv, client_t *client)
{
	char *buffer = malloc(sizeof(char) * 1);

	if (!buffer)
		return (false);
	buffer[0] = '\0';
	buffer = (realloc_concat(buffer, "[ "));
	for (int i = 0; i <= client->level; i++)
		for (uint j = 0; j < 1 + 2 * i; j++)
			buffer = add_tile_to_buff(srv, client->pos.x - i + j, \
			client->pos.y, buffer);
 	buffer[strlen(buffer) - 2] = ' ';
	buffer[strlen(buffer) - 1] = ']';
	return (send_message(client->socket.fd, realloc_concat(buffer, "\n")));
}