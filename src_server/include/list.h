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

	#define list_push(a, b) list_add_item((void **)a, b, sizeof(*(b)))
	bool list_add_item(void **list, void *data, size_t data_size);

	#define list_next(a) list_next_item((void **)a)
	bool list_next_item(void **list);

	#define list_prev(a) list_prev_item((void **)a)
	bool list_prev_item(void **list);

	#define list_delete(a) list_delete_all((void **)a)
	void list_delete_all(void **list);

	#define list_remove(a) list_delete_item((void **)a)
	void list_delete_item(void **list);

#endif /* !LIST_H_ */
