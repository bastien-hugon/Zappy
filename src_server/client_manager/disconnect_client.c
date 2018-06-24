/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Disconnect client
*/

#include "server.h"

/**
*@brief Disconnect a client from his fd
*
*@param srv [in] The main server_t struct
*@param fd [in] The client fd
*@return true Disconnected
*@return false Not disconnected
*/
bool disconnect_c_client(server_t *srv, int fd)
{
	client_t *client = get_client_for_fd(srv, fd);
	client_t *gfx = get_gfx_client(srv);

	if (gfx && !client->is_gfx) {
		send_message(gfx->socket.fd, "pdi %d\n", \
		client->id);
	}
	close(client->socket.fd);
	epoll_ctl(srv->srv_epoll.epollfd, EPOLL_CTL_DEL, \
		fd, &(srv->srv_epoll.ev));
	if (client->team)
		client->team->free_slots++;
	list_remove(&client);
	if (client == srv->game.clients || client == NULL)
		srv->game.clients = NULL;
	WARN("Client fd #%d cleanly closed", fd);
	return (true);
}