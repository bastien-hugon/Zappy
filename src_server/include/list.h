/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list
*/

#ifndef LIST_H_
	#define LIST_H_

	#include <stdbool.h>

	#ifdef STESTS
		#include "tests.h"
	#endif /* !STEST */

	/**
	*@brief generic linked list
	*/
	typedef struct list_s
	{
		struct list_s *next;
		struct list_s *prev;
	} list_t;

	bool list_add_item(void **list, void *data, size_t data_size);
	bool list_next(void **list);
	bool list_prev(void **list);
	void list_delete(void **list);

#endif /* !LIST_H_ */
