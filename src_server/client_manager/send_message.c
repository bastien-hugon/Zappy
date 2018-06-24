/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Send message function's
*/

#include "server.h"

/**
* @brief Send a specific message to an FD
*
* @param fd [out] The fd to send the message on it
* @param format [in] The message to send
* @param ... [in] The va args params to send
* @return true If the message is sent
* @return false If the message isn't sent
*/
bool send_message(int fd, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	if (vdprintf(fd, format, args) < 0) {
		WARN("Message not transmitted to fd #%d", fd);
		return (false);
	} else {
		LOG("Sending message:");
		vprintf(format, args);
	}
	va_end(args);
	return (true);
}

/**
* @brief Send a message to all connected users
*
* @param srv [in] The main server_t struct
* @param format [in] The message to send
* @param ... [in] The va args params to send
* @return true If the message is sent
* @return false If the message isn't sent
*/
bool broadcast(const server_t *srv, const char *format, ...)
{
	va_list args;
	client_t *client = srv->game.clients;

	va_start(args, format);
	while (client != NULL) {
		if (send_message(client->socket.fd, format, args) == false) {
			WARN("Broadcast not sent to all users");
			return (false);
		}
		list_next(&client);
	}
	va_end(args);
	return (true);
}