/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** End all sockets and free the server
*/

#include "server.h"

/**
*@brief Free the map
*
*@param srv [out] Main server_t struct
*@param map [out] The map to free
*/
static void free_map(server_t *srv, tile_t **map)
{
	for (uint y = 0; y < srv->game.height; y++)
		free(map[y]);
	free(map);
}

/**
*@brief Stop the server and kill clients
*
*@param srv [out] Main server_t struct
*@param name [out] The winning team
*/
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

/**
*@brief Check if a team won
*
*@param client [out] The client to check
*@param name [out] The team name
*@return true The team won
*@return false The team haven't won
*/
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

/**
*@brief Check the end of the game
*
*@param srv The main server_t struct
*@return true The game's ending
*@return false The game's continuing
*/
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