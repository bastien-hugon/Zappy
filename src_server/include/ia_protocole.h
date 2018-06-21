/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** IA Protocole
*/

#ifndef IA_PROTOCOLE_H_
	#define IA_PROTOCOLE_H_

	#include "server.h"

	bool client_forward(server_t *srv, client_t *client);
	bool client_right(server_t *srv, client_t *client);
	bool client_left(server_t *srv, client_t *client);

#endif /* !IA_PROTOCOLE_H_ */
