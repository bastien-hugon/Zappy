/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_circular_buffer
*/

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

Test(circular_buffer, get)
{
	circular_buffer_t buff;
	char *str;
	int fd[2];

	circular_buffer_init(&buff);
	cr_assert_eq(pipe(fd), 0);
	cr_assert_neq(write(fd[1], "abcdefghijkl", 12), -1);
	circular_buffer_read(&buff, fd[0]);
	str = circular_buffer_get_to(&buff, "ij");
	cr_assert_eq(strncmp("abcdefgh", str, 8), 0);
	free(str);
	close(fd[0]);
	close(fd[1]);
}

Test(circular_buffer, readgetandread)
{
	circular_buffer_t buff;
	char *str;
	int fd[2];

	circular_buffer_init(&buff);
	cr_assert_eq(pipe(fd), 0);
	for (int i = 0; i < BUFF_SIZE; i++)
		write(fd[1], (i != (BUFF_SIZE / 2)) ? "a" : "\n", 1);
	circular_buffer_read(&buff, fd[0]);
	str = circular_buffer_get_to(&buff, "\n");
	for (int i = 0; i < BUFF_SIZE / 2; i++)
		cr_assert_eq('a', str[i]);
	free(str);
	for (int i = 0; i < BUFF_SIZE / 2 + 1; i++)
		write(fd[1], "b", 1);
	circular_buffer_read(&buff, fd[0]);
	for (int i = 0; i < BUFF_SIZE; i++)
		cr_assert_eq(buff.buffer[i], (i <= (BUFF_SIZE / 2)) ? 'b': 'a');
	close(fd[0]);
	close(fd[1]);
}

Test(circular_buffer, getbeforeread)
{
	circular_buffer_t buff;
	char *str;

	circular_buffer_init(&buff);
	str = circular_buffer_get_to(&buff, "\n");
	cr_assert_eq(CIRCULAR_BUFFER_NOT_FOUND, str);
}

Test(circular_buffer, notfound)
{
	circular_buffer_t buff;
	char *str;
	int fd[2];

	circular_buffer_init(&buff);
	cr_assert_eq(pipe(fd), 0);
	cr_assert_neq(write(fd[1], "abcdefghijkl", 12), -1);
	circular_buffer_read(&buff, fd[0]);
	str = circular_buffer_get_to(&buff, "\n");
	cr_assert_eq(CIRCULAR_BUFFER_NOT_FOUND, str);
}

Test(circular_buffer, get_hard)
{
	circular_buffer_t buff;
	char *str;
	int fd[2];

	circular_buffer_init(&buff);
	cr_assert_eq(pipe(fd), 0);
	for (int i = 0; i < BUFF_SIZE; i++)
		write(fd[1], (i != (BUFF_SIZE / 2 + 60)) ? "a" : "\n", 1);
	for (int i = 0; i < (BUFF_SIZE / 2 + 60); i++)
		write(fd[1], "b", 1);
	write(fd[1], "\n", 1);
	circular_buffer_read(&buff, fd[0]);
	str = circular_buffer_get_to(&buff, "\n");
	for (int i = 0; i < BUFF_SIZE / 2 + 60; i++)
		cr_assert_eq('a', str[i]);
	free(str);
	circular_buffer_read(&buff, fd[0]);
	str = circular_buffer_get_to(&buff, "\n");
	for (int i = 0; i < BUFF_SIZE - 1; i++)
		cr_assert_eq(str[i], (i < (BUFF_SIZE / 2 - 61)) ? 'a' : 'b');
}
