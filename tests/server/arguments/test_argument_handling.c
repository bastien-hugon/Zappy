/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_argument_handling
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
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

Test(argument, help)
{
	char *argv[] = {"./server", "-p", "7000", \
		"-x", "15", "-help", "20", "-f", "12"};
	char *argv2[] = {"./server", "-p", "7000", \
		"-x", "15", "-y", "20", "-f", "12"};

	cr_redirect_stdout();
	cr_assert_eq(handle_help(9, argv), true);
	cr_assert_eq(handle_help(9, argv2), false);
}


Test(argument, argument_handling_unknow_argument)
{
	server_t server;
	char *argv[] = {"./server", "-p", "7000", \
		"-u", "15", "-y", "20", "-f", "12"};

	cr_redirect_stdout();
	cr_assert_eq(handle_args(&server, 9, argv), false);
}

Test(argument, argument_handling_team)
{
	server_t server;
	team_t *team;

	char *argv[] = {"./server", "-p", "7000", \
		"-x", "15", "-y", "20", "-f", "12", \
		"-n", "coucou", "qwerty", "azerty", "-c", "19"};

	cr_redirect_stdout();
	handle_args(&server, 15, argv);
	team = server.game.teams;
	cr_assert_str_eq(team->name, "coucou");
	cr_assert_eq(team->free_slots, 19);
	list_next(&team);
	cr_assert_str_eq(team->name, "qwerty");
	cr_assert_eq(team->free_slots, 19);
	list_next(&team);
	cr_assert_str_eq(team->name, "azerty");
	cr_assert_eq(team->free_slots, 19);
}
