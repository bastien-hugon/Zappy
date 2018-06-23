/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** IA Protocole
*/

#ifndef IA_PROTOCOLE_H_
	#define IA_PROTOCOLE_H_

	#include "server.h"

	#define N_FOOD ("food")
	#define N_LINEMATE ("linemate")
	#define N_DERAUMERE ("deraumere")
	#define N_SIBUR ("sibur")
	#define N_MENDIANE ("mendiane")
	#define N_PHIRAS ("phiras")
	#define N_THYSTAME ("thystame")

	bool client_forward(server_t *srv, client_t *client);
	bool client_right(server_t *srv, client_t *client);
	bool client_left(server_t *srv, client_t *client);
	bool client_inventory(server_t *srv, client_t *client);
	bool client_nb_connect(server_t *srv, client_t *client);
	bool client_take(server_t *srv, client_t *client);
	bool client_set(server_t *srv, client_t *client);
	bool client_look(server_t *srv, client_t *client);
	bool look_north(server_t *srv, client_t *client);
	bool look_west(server_t *srv, client_t *client);
	bool look_south(server_t *srv, client_t *client);
	bool look_east(server_t *srv, client_t *client);

#endif /* !IA_PROTOCOLE_H_ */
