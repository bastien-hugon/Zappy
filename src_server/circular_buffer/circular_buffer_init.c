/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** circular_buffer functions
*/

/*!
** @brief circular_buffer functions
** @file circular_buffer_init.c
*/

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "logs.h"
#include "circular_buffer.h"

/**
* @brief init a circular buffer
*
* @param buffer [out] the buffer to init
*/
void circular_buffer_init(circular_buffer_t *buffer)
{
	memset(buffer, 0, sizeof(*buffer));
}
