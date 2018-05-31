/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_argument_handling
*/

#include <criterion/criterion.h>
#include <sys/types.h>
#include <unistd.h>
#include "server.h"

Test(argument, argument_handling)
{
	server_t server;
	char *argv[] = {"./server", "-p", "7000", \
		"-x", "15", "-y", "20", "-f", "12"};

	handle_args(&server, 9, argv);
	cr_assert_eq(server.srv_epoll.port, 7000);
	cr_assert_eq(server.game.width, 15);
	cr_assert_eq(server.game.height, 20);
	cr_assert_eq(server.game.frequence, 12);
}
