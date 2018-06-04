/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** generic linked list
*/

/*!
** @brief generic linked list implementation
** @file list.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

/**
* @brief add an item the end of a list
*
* @param list elem in the list
* @param data the data to copy for the element
* @param data_size the size of the data
* @return false in case of an error
*/
bool list_add_item(void **list, void *data, size_t data_size)
{
	list_t *new_node = malloc(sizeof(list_t) + data_size);
	list_t *node = (list_t *) ((*list == NULL) ? NULL : ((list_t *)(*list) - 1));

	if (new_node == NULL) {
		fprintf(stderr, "Error while allocating memory\n");
		return (false);
	}
	memcpy((((char *)new_node) + sizeof(list_t)), data, data_size);
	new_node->next = NULL;
	if (node == NULL) {
		*list = ((char *)new_node + sizeof(list_t));
		new_node->prev = NULL;
	} else {
		while (node->next != NULL) {
			node = node->next;
		}
		node->next = new_node;
		new_node->prev = node;
	}
	return (true);
}

/**
*@brief iterate to the next element in a list
*
*@param list an pointer to an element in the list
*@return true on success
*@return false on error (ex: no next element)
*/
bool list_next_item(void **list) {
	list_t *node = ((list_t *)(*list)) - 1;

	if (node->next == NULL) {
		return (false);
	}
	node = node->next;
	*list = (void *)(node + 1);
	return (true);
}

/**
*@brief iterate to the previous element in a list
*
*@param list an pointer to an element in the list
*@return true on success
*@return false on error (ex: no previous element)
*/
bool list_prev_item(void **list) {
	list_t *node = ((list_t *)(*list)) - 1;

	if (node->prev == NULL) {
		return (false);
	}
	node = node->prev;
	*list = (void *)(node + 1);
	return (true);
}

/**
* @brief delete a list
*
* @param list first element in the list
*/
void list_delete_all(void **list)
{
	list_t *node = ((list_t *)(*list)) - 1;
	list_t *tmp_node;

	while (node) {
		tmp_node = node;
		node = node->next;
		free(tmp_node);
	}
}