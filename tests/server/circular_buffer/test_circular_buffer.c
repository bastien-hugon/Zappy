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

Test(circular_buffer, init)
{
	circular_buffer_t buff;
	char *ptr = (char *)&buff;

	memset(&buff, 2, sizeof(buff));
	circular_buffer_init(&buff);
	for (size_t i = 0; i < sizeof(buff); i++) {
		cr_assert_eq(*ptr, 0);
	}
}

Test(circular_buffer, read)
{
	circular_buffer_t buff;
	char c;
	int fd[2];

	circular_buffer_init(&buff);
	cr_assert_eq(pipe(fd), 0);
	for (size_t i = 0; i < BUFF_SIZE; i++) {
		c = (char)('a' + i % 26);
		cr_assert_neq(write(fd[1], &c, 1), -1);
	}
	circular_buffer_read(&buff, fd[0]);
	for (size_t i = 0; i < BUFF_SIZE; i++) {
		c = (char)('a' + i % 26);
		cr_assert_eq(buff.buffer[i], c);
	}
	close(fd[0]);
	close(fd[1]);
}

Test(circular_buffer, read2times)
{
	circular_buffer_t buff;
	int fd[2];

	circular_buffer_init(&buff);
	cr_assert_eq(pipe(fd), 0);
	cr_assert_neq(write(fd[1], "abcdef", 6), -1);
	circular_buffer_read(&buff, fd[0]);
	cr_assert_neq(write(fd[1], "ghijkl", 6), -1);
	circular_buffer_read(&buff, fd[0]);
	for (char c = 'a'; c <= 'l'; c++)
		cr_assert_eq(buff.buffer[(c - 'a')], c);
	close(fd[0]);
	close(fd[1]);
}

Test(circular_buffer, get)
{
	circular_buffer_t buff;
	char *str;
	int fd[2];

	circular_buffer_init(&buff);
	cr_assert_eq(pipe(fd), 0);
	cr_assert_neq(write(fd[1], "abcdefghijkl", 12), -1);
	circular_buffer_read(&buff, fd[0]);
	fprintf(stderr, "bite err\n");
	str = circular_buffer_get_to(&buff, "ij");
	cr_assert_eq(strncmp("abcdefgh", str, 8), 0);
	free(str);
	close(fd[0]);
	close(fd[1]);
}
