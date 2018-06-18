/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** GFX Protocole
*/

#ifndef GFX_PROTOCOLE_H_
	#define GFX_PROTOCOLE_H_

	#include "server.h"

	bool gfx_map_size(const server_t *srv, const client_t *user, \
	const char * const *cmd);
	bool gfx_map_tiles(const server_t *srv, const client_t *user, \
	const char * const *cmd);
	bool gfx_map_tile(const server_t *srv, const client_t *user, \
	const char * const *cmd);
	bool gfx_ppo(const server_t *srv, const client_t *user, \
	const char * const *cmd);

#endif /* !GFX_PROTOCOLE_H_ */