/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** End all sockets and free the server
*/

#include "server.h"

static void free_map(server_t *srv, tile_t **map)
{
	for (uint y = 0; y < srv->game.height; y++)
		free(map[y]);
	free(map);
}

void stop_server(server_t *srv, char *name)
{
	client_t *client = srv->game.clients;
	client_t *gfx = get_gfx_client(srv);

	if (gfx && name)
		send_message(gfx->socket.fd, "seg %s\n", name);
	while (client) {
		kill_client(srv, client);
		if (list_next(&client) == false)
			break;
	}
	free_map(srv, srv->game.map);
	ERROR("Killing server due to SIGINT");
	exit(0);
}

static bool team_won(client_t *client, char *name)
{
	client_t *list = client;
	int nb = 0;

	while (list) {
		if (!strcmp(list->team->name, name) && list->level >= 8)
			nb++;
		if (list_next(&list) == false)
			break;
	}
	return (nb >= 6);
}

bool check_end(server_t *srv)
{
	client_t *list = srv->game.clients;

	while (list) {
		if (team_won(list, list->team->name))
			stop_server(srv, list->team->name);
		if (list_next(&list) == false)
			break;
	}
	return (false);
}