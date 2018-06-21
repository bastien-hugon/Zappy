/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** GFX Protocole
*/

#ifndef GFX_PROTOCOLE_H_
	#define GFX_PROTOCOLE_H_

	#include "server.h"

	client_t *get_gfx_client(const server_t *srv);
	bool gfx_map_size(server_t *srv, client_t *user);
	bool gfx_map_tiles(server_t *srv, client_t *user);
	bool gfx_map_tile(server_t *srv, client_t *user);
	bool gfx_ppo(server_t *srv, client_t *user);
	bool gfx_send_ppo(server_t *srv, client_t *user);

#endif /* !GFX_PROTOCOLE_H_ */