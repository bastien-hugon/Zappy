/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Main Server Header
*/

#ifndef SERVER_H_
	#define SERVER_H_

	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <stdbool.h>
	#include <string.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <signal.h>
	#include <time.h>

	#include <sys/socket.h>
	#include <netdb.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <sys/epoll.h>

	#undef EXIT_FAILURE

	#define EXIT_FAILURE (84)
	#define MAX_EVENTS (1024)
	#define BUFF_SIZE (1024)
	#define NB_CMD_QUEUE (10)

	typedef unsigned int uint;

	/**
	*@brief Socket structure
	*/
	typedef struct socket_s
	{
		int fd;
		struct sockaddr_in s_in;
	} socket_t;

	/**
	*@brief Team structure
	*/
	typedef struct team_s
	{
		char *name;
		uint free_slots;
	} team_t;

	/**
	*@brief Direction Enum
	*/
	typedef enum
	{
		NORTH, \
		SOUTH, \
		EAST, \
		WEST
	} dir_e;

	/**
	*@brief Ressource Enum
	*/
	typedef enum
	{
		LINEMATE, \
		DERAUMERE, \
		SIBUR, \
		MENDIANE, \
		PHIRAS, \
		THYSTAME, \
		NB_RESSOURCE
	} ressource_e;

	/**
	*@brief Command Enum
	*/
	typedef enum
	{
		FORWARD, \
		NB_CMDS
	} cmd_e;

	/**
	*@brief Client Structure
	*/
	typedef struct client_s
	{
		socket_t socket;
		team_t *team;
		dir_e dir;
		uint inventory[NB_RESSOURCE];
		char buffer[BUFF_SIZE];
		char *cmd_queue[NB_CMD_QUEUE];
		uint tick_left;
	} client_t;

	/**
	*@brief Egg Structure
	*/
	typedef struct egg_s
	{
		uint tile_x;
		uint tile_y;
		team_t *team;
		uint tick_left;
	} egg_t;

	/**
	*@brief Tile structure
	*/
	typedef struct tile_s
	{
		client_t *player;
		uint inventory[NB_RESSOURCE];
		egg_t *egg;
	} tile_t;


	/**
	*@brief Game Structure
	*/
	typedef struct game_s
	{
		uint width;
		uint height;
		tile_t **map;
		uint frequence;
		client_t *clients;
		team_t *teams;
		egg_t *egg;
	} game_t;

	/**
	*@brief Epoll Structure
	*/
	typedef struct epoll_s
	{
		socket_t socket;
		struct epoll_event ev;
		struct epoll_event events[MAX_EVENTS];
		uint port;
		int epollfd;
	} epoll_t;

	/**
	*@brief Server Structure
	*/
	typedef struct server_s
	{
		epoll_t srv_epoll;
		game_t game;
	} server_t;

	bool handle_help(int argc, char **argv);
	bool handle_args(server_t *server, int argc, char **argv);

#endif /* !SERVER_H_ */
