/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Take and set objects
*/

#include <strings.h>
#include "server.h"

/**
* @brief take an object on a tile
*
* @param srv [in] the server
* @param user [in] the user who is taking an object
* @param map [in] the map
* @param res [in] the resource
*/
static bool take_object(server_t *srv, client_t *user, tile_t **map, \
	ressource_e res)
{
	client_t *gfx = get_gfx_client(srv);

	if (map[user->pos.y][user->pos.x].inventory[res] > 0) {
		map[user->pos.y][user->pos.x].inventory[res]--;
		user->inventory[res]++;
		if (gfx)
			gfx_send_tile(srv, gfx->socket.fd, user->pos.x, \
			user->pos.y);
		return (true);
	}
	return (false);
}

/**
*@brief Take an object
*
*@param srv [out] The main server_t struct
*@param user [in] The user who takes something
*@return true If the message is sent
*@return false If the message isn't sent
*/
bool client_take(server_t *srv, client_t *user)
{
	char obj[7][10] = {"food", "linemate", "deraumere", "sibur", \
	"mendiane", "phiras", "thystame"};
	char **cmd = explode(user->cmd_queue[0], " ");
	bool take = false;

	if (!cmd[1])
		return (send_message(user->socket.fd, "ko\n"));
	for (int i = 0; i < 7; i++)
		if (!strcasecmp(obj[i], cmd[1]))
			take = take_object(srv, user, srv->game.map, i);
	return (send_message(user->socket.fd, "%s\n", (take) ? "ok" : "ko"));
}

/**
*@brief drop an object on a tile
*
*@param srv [in] the server
*@param user [in] the user
*@param map [in] the map
*@param res [in] the resources
*@return true on ok 
*@return false  on ko
*/
static bool set_object(server_t *srv, client_t *user, tile_t **map, \
	ressource_e res)
{
	client_t *gfx = get_gfx_client(srv);

	if (user->inventory[res] > 0) {
		map[user->pos.y][user->pos.x].inventory[res]++;
		user->inventory[res]--;
		if (gfx)
			gfx_send_tile(srv, gfx->socket.fd, user->pos.x, \
			user->pos.y);
		return (true);
	}
	return (false);
}

/**
*@brief Set an object
*
*@param srv [out] The main server_t struct
*@param user [in] The user who set something
*@return true If the message is sent
*@return false If the message isn't sent
*/
bool client_set(server_t *srv, client_t *user)
{
	char obj[7][10] = {"food", "linemate", "deraumere", "sibur", \
	"mendiane", "phiras", "thystame"};
	char **cmd = explode(user->cmd_queue[0], " ");
	bool set = false;

	if (!cmd[1])
		return (send_message(user->socket.fd, "ko\n"));
	for (int i = 0; i < 7; i++)
		if (!strcasecmp(obj[i], cmd[1]))
			set = set_object(srv, user, srv->game.map, i);
	return (send_message(user->socket.fd, "%s\n", (set) ? "ok" : "ko"));
}