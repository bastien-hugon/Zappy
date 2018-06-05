/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** circular_buffer functions
*/

/*!
** @brief circular_buffer functions
** @file circular_buffer.c
*/

#include <errno.h>
#include <string.h>
#include "circular_buffer.h"

/**
*@brief init a circular buffer
*
* @param buffer the buffer to init
*/
void circular_buffer_init(circular_buffer_t *buffer)
{
	memset(buffer, 0, sizeof(*buffer));
}

/**
* @brief read in a circular buffer
* the caller need to log if there is an error
*
* @param buffer the buffer to init
* @param fd the file descriptor to read
*/
bool circular_buffer_read(circular_buffer_t *buffer, int fd)
{
	const char *buffer_end = (&buffer->buffer + sizeof(buffer->buffer));
	size_t readed = 0;

	if (buffer->head == NULL)
		buffer->head = &buffer->buffer;
	if (buffer->tail == NULL) {
		readed = read(fd, buffer->buffer, sizeof(buffer->buffer));
		return ((readed != -1) ? true : false);
	}
	if (buffer->tail <= buffer->head) {
		readed = read(fd, buffer->buffer, buffer_end - buffer->head);
		if (readed == -1 && errno != EAGAIN)
			return (false);
		buffer->head += readed;
		if (buffer->head == buffer_end)
			buffer->head = &buffer->buffer;
	} else {
		readed = read(fd, buffer->buffer, buffer->tail - buffer->head);
		if (readed == -1 && errno != EAGAIN)
			return (false);
	}
	return (true);
}

/**
* @brief retrieve string from buffer
* the caller need to log if there is an error
*
* @param buffer the buffer to init
* @param to the end of the string to retrieve
* @return a string to free after use
* @error can return CIRCULAR_BUFFER_NOT_FOUND and
*	CIRCULAR_BUFFER_ALLOCATION_ERROR
*/
char *circular_buffer_get_to(circular_buffer_t *buffer, char *to)
{
	char *str;
	char *ret;
	const char *buff_end = (&buffer->buffer + sizeof(buffer->buffer));

	if (buffer->head == NULL)
		return (CIRCULAR_BUFFER_NOT_FOUND);
	if (buffer->tail == NULL)
		buffer->tail = &buffer->buffer;
	if (str = strnstr(buffer->tail, to, buff_end - buffer->tail)) {
		ret = strndup(buffer->tail, buffer->tail - str);
		buffer->tail = str + strlen(to);
		return (ret);
	}
	if (str = strnstr(&buffer->buffer, to, sizeof(buffer->buffer))) {
		ret = malloc((buff_end - buffer->tail) + buffer->buffer - str);
		memcpy(ret, buffer->tail, (buff_end - buffer->tail));
		((char *)memcpy(ret + (buff_end - buffer->tail), \
		&buffer->buffer, str - &buffer->buffer))[1] = '\0';
		buffer->tail = str + strlen(to);
		return (ret);
	}
	return (CIRCULAR_BUFFER_NOT_FOUND);
}