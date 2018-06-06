/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** circular_buffer
*/

#ifndef CIRCULAR_BUFFER_H_
	#define CIRCULAR_BUFFER_H_

	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>

	#define CIRCULAR_BUFFER_ALLOCATION_ERROR (NULL)
	#define CIRCULAR_BUFFER_NOT_FOUND ((char *)-1)
	#define BUFF_SIZE (2048)

	typedef struct circular_buffer_s
	{
		char buffer[BUFF_SIZE];
		char *head;
		char *tail;
	} circular_buffer_t;

	void circular_buffer_init(circular_buffer_t *buffer);
	bool circular_buffer_read(circular_buffer_t *buffer, int fd);
	char *circular_buffer_get_to(circular_buffer_t *buffer, char *to);

#endif /* !CIRCULAR_BUFFER_H_ */
