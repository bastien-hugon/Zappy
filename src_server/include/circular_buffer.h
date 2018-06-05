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

	#include "server.h";

	#define CIRCULAR_BUFFER_ALLOCATION_ERROR (NULL)
	#define CIRCULAR_BUFFER_NOT_FOUND ((char *)-1)

	typedef struct circular_buffer_s
	{
		char buffer[BUFF_SIZE];
		char *head;
		char *tail;
	} circular_buffer_t;

#endif /* !CIRCULAR_BUFFER_H_ */
