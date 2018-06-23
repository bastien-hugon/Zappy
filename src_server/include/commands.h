/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** commands header
*/

#ifndef COMMANDS_H_
	#define COMMANDS_H_

	#include "server.h"

	typedef struct command_s
	{
		char cmd_str[40];
		cmd_e command;
		uint time;
		bool (*func)(server_t *server, client_t *client);
	} command_t;

	bool register_command(client_t *client, char *command);
	command_t *get_command_from_str(char *str);
	char **explode(char *str, char *lim);
	void free_wordtab(char **str);
	bool send_sound(server_t *server, client_t *sender, char *sound);
	int get_direction_by_player(int direction, client_t *receiver);
	void eggs_loop(server_t *server);
	void food_loop(server_t *server);

	bool send_message_command(server_t *server, client_t *client);
	bool drop_egg_command(server_t *server, client_t *client);

#endif /* !COMMANDS_H_ */
