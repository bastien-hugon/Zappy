/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Join a team
*/

#include "server.h"

static bool egg_hatching(server_t *server, client_t *client, egg_t *egg)
{
	bool ret;

	client->dir = (dir_e) rand() % 4;
	client->pos = egg->pos;
	send_message(client->socket.fd, \
		"%d %d\n", egg->pos.x, egg->pos.y);
	client->team->free_slots--;
	INFO("Client #%d just logged-in in team #%s (egg)", \
	client->id, client->team->name);
	client->team->free_slots--;
	ret = list_push(&(server->game.map[egg->pos.y][egg->pos.x]\
		.player), &client);
	list_remove(&egg);
	if (server->game.egg == egg || egg == NULL)
		server->game.egg = NULL;
	return (ret);
}

static bool place_with_egg(server_t *server, client_t *client)
{
	egg_t *egg = server->game.egg;

	do {
		if (egg != NULL && egg->team == client->team \
			&& egg->tick_left == 0) {
			return (egg_hatching(server, client, egg));
		}
	} while (list_next(&egg));
	return (false);
}

/**
*@brief Place a client in the map
*
*@param srv [out] Main server_t struct
*@param client [out] The client to place
*@param team [out] The team of the client
*/
static void place_client_on_map(server_t *srv, client_t *client, team_t *team)
{
	int x = rand() % srv->game.width;
	int y = rand() % srv->game.height;

	if (place_with_egg(srv, client))
		return ;
	if (team->free_slots > 0) {
		client->dir = (dir_e) rand() % 4;
		list_push(&(srv->game.map[y][x].player), &client);
		client->pos = (pos_t) {x, y};
		send_message(client->socket.fd, "%d %d\n", x, y);
		INFO("Client #%d just logged-in in team #%s", client->id, \
		team->name);
		team->free_slots--;
		gfx_pnw(srv, client);
		return ;
	}
	send_message(client->socket.fd, "ko\n");
	WARN("Client #%d cannot join #%s, the team is full", client->id, \
	team->name);
}

/**
*@brief Join a player to a team
*
*@param srv [out] Main server_t
*@param client [out] The client to join
*@param str [out] The team name
*/
void join_team(server_t *srv, client_t *client, char *str)
{
	team_t *list = srv->game.teams;
	if (!strcmp(str, "GFX_CLIENT")) {
		client->is_logged = true;
		client->is_gfx = true;
		LOG("GFX Client just logged-in");
		return ;
	}
	while (list != NULL) {
		if (!strcmp(list->name, str)) {
			client->team = list;
			client->is_logged = true;
			send_message(client->socket.fd, "%d\n", \
			client->team->free_slots - 1);
			place_client_on_map(srv, client, list);
			return ;
		}
		list_next(&list);
	}
	WARN("Cannot connect #%d, team #%s doesn't exists", client->id, str);
	send_message(client->socket.fd, "ko\n");
}