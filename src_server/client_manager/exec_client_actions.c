/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Exec Client Actions
*/

#include "server.h"

/**
* @brief Get the associated client for a socket fd
*
* @param srv [in] the server
* @param fd [in] the client file descriptor
* @return client_t * the client
*/
client_t *get_client_for_fd(server_t *srv, int fd)
{
	client_t *client = srv->game.clients;

	if (!client)
		return (NULL);
	do {
		if (client->socket.fd == fd)
			return (client);
	} while (list_next(&client));
	return (NULL);
}

/**
*@brief remove the first command in the client cmd_queue
*
*@param client [out] the client
*/
static void remove_first_command_from_queue(client_t *client)
{
	memmove(&client->cmd_queue[0], &client->cmd_queue[1], \
		sizeof(NB_CMD_QUEUE - 1) * sizeof(char *));
	client->cmd_queue[NB_CMD_QUEUE - 1] = NULL;
}

/**
* @brief start a command from the command queue
*
* @param client [out] the client
*/
static void start_command_from_queue(client_t *client)
{
	command_t *command;

	if (client->cmd_queue[0] == NULL) {
		client->cmd = NULL;
		return ;
	}
	command = get_command_from_str(client->cmd_queue[0]);
	if (command == NULL) {
		send_message(client->socket.fd, "ko\n");
		remove_first_command_from_queue(client);
		return ;
	}
	client->cmd = command;
	client->tick_left = command->time;
}

/**
*@brief cancel the current command exectution of a client
*
*@param client [out] the client
*/
void cancel_client_action(client_t *client)
{
	remove_first_command_from_queue(client);
	client->cmd = NULL;
	client->tick_left = 0;
}

/**
*@brief exec the actions of all the client
*
*@param srv [out] the server
*/
void exec_clients_actions(server_t *srv)
{
	client_t *client = srv->game.clients;
	refill_map(&(srv->game));
	while (client) {
		if (client->cmd == NULL)
			start_command_from_queue(client);
		while (client->cmd != NULL && client->tick_left <= 0) {
			client->cmd->func(srv, client);
			if (client->tick_left <= 0) {
				remove_first_command_from_queue(client);
				start_command_from_queue(client);
			}
		}
		if (client->cmd)
			client->tick_left--;
		if (false == list_next(&client))
			break;
	}
	eggs_loop(srv);
	food_loop(srv);
}
