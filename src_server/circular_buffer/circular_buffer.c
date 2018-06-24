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
#include <unistd.h>
#include "logs.h"
#include "circular_buffer.h"

/**
*@brief strstr with max len
*
* @param buffer [in] the string
* @param the [in] substring to locate
* @param length [in] the max len
*/
char *sstrstr(char *buffer, char *find, size_t length)
{
	size_t find_length = strlen(find);
	size_t i;

	for (i = 0; i < length; i++)
	{
		if (strncmp(&buffer[i], find, find_length) == 0)
			return &buffer[i];
	}
	return NULL;
}

/**
* @brief read in a circular buffer
* the caller need to log if there is an error
*
* @param buffer [out] the buffer to init
* @param fd [in] the file descriptor to read
*/
bool circular_buffer_read(circular_buffer_t *buffer, int fd)
{
	const char *buff_end = (((char *)&buffer->buffer) + BUFF_SIZE);
	int readed = 0;

	if (buffer->head == NULL)
		buffer->head = (char *)&buffer->buffer;
	if (buffer->tail == NULL)
		buffer->tail = (char *)&buffer->buffer;
	if (buffer->tail <= buffer->head) {
		readed = read(fd, buffer->head, buff_end - buffer->head);
		if (readed == 0 || (readed == -1 && errno != EAGAIN))
			return (false);
	} else {
		readed = read(fd, buffer->buffer, buffer->tail - buffer->head);
		if (readed == 0 || (readed == -1 && errno != EAGAIN))
			return (false);
	}
	buffer->head += readed;
	if (buffer->head == buff_end) {
			buffer->head = (char *)&buffer->buffer;
			circular_buffer_read(buffer, fd);
	}
	return (true);
}

/**
* @brief get the data if the data is between the end \
*	and the start of the buffer
*
* @param buffer [in] the buffer
* @param to [in] the end of the string
* @param buff_end [in] the end of the buffer
* @param str [in] the substring
* @return char *the string to the delimiter
*/
static char *circular_buffer_get_end(circular_buffer_t *buffer, char *to, \
	const char *buff_end, char *str)
{
	char *ret = malloc((size_t)(buff_end - buffer->tail + \
		(size_t)((buff_end - buffer->tail) + str - \
		(((char *)&buffer->buffer)) + 1)));

	if (ret == NULL)
		return (CIRCULAR_BUFFER_ALLOCATION_ERROR);
	memcpy(ret, buffer->tail, (buff_end - buffer->tail));
	memcpy(ret + (buff_end - buffer->tail), \
		&buffer->buffer, str - ((char *)&buffer->buffer));
	ret[((size_t)((buff_end - buffer->tail) + str - \
		(((char *)&buffer->buffer))))] = '\0';
	buffer->tail = str + strlen(to);
	memset(buffer->tail - strlen(to), 0, strlen(to));
	return (ret);
}

/**
* @brief get a standard string between tail and end
*
* @param buffer [in] the buffer
* @param to [in] the end of the string
* @param str [the] pointer to the start of to in buffer
* @return char *the allocated string
*/
char *circular_buffer_get_standard(circular_buffer_t *buffer, char *to, \
	char *str)
{
	char *ret = strndup(buffer->tail, str - buffer->tail);

	if (ret == NULL)
		return (CIRCULAR_BUFFER_ALLOCATION_ERROR);
	buffer->tail = (char *)(str + strlen(to));
	memset(buffer->tail - strlen(to), 0, strlen(to));
	return (ret);
}

/**
* @brief retrieve string from buffer
* the caller need to log if there is an error
*
* @param buffer [in] the buffer
* @param to [in] the end of the string to retrieve
* @return a string to free after use
* @error can return CIRCULAR_BUFFER_NOT_FOUND and
*	CIRCULAR_BUFFER_ALLOCATION_ERROR
*/
char *circular_buffer_get_to(circular_buffer_t *buffer, char *to)
{
	char *str;
	const char *buff_end = (((char *)&buffer->buffer) + BUFF_SIZE);

	if (buffer->head == NULL) {
		return (CIRCULAR_BUFFER_NOT_FOUND);
	}
	if ((buffer->head > buffer->tail || \
		buffer->head == (char *)&buffer->buffer) && \
		(str = sstrstr(buffer->tail, to, ((int)(((buffer->head == \
		(char *)&buffer->buffer) ? buff_end : buffer->head) - \
		buffer->tail)))) != NULL)
		return (circular_buffer_get_standard(buffer, to, str));
	if (buffer->head <= buffer->tail && (str = sstrstr(\
		(char *)&buffer->buffer, to, buffer->head - \
		(char *)&buffer->buffer)))
		return (circular_buffer_get_end(buffer, to, buff_end, str));
	return (CIRCULAR_BUFFER_NOT_FOUND);
}
