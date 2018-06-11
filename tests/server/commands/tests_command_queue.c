/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** tests_command_queue
*/

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <sys/types.h>
#include <unistd.h>
#include "server.h"

Test(command_queue, register_command)
{
	char *cmd = "je suis une commande";
	client_t client;

	memset(&client, 0, sizeof(client));
	cr_assert_eq(register_command(&client, cmd), true);
	cr_assert_eq(client.cmd_queue[0], cmd);
}

Test(command_queue, register_command_fail)
{
	char *cmd = "je suis une commande";
	client_t client;

	memset(&client.cmd_queue, 1, sizeof(client.cmd_queue));
	cr_assert_eq(register_command(&client, cmd), false);
}

