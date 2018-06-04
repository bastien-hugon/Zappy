/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_list_next_prev
*/

#include <criterion/criterion.h>
#include <sys/types.h>
#include <unistd.h>
#include "list.h"

Test(list, next)
{
	int *elem = NULL;
	int i;

	for (i = 0; i <= 5; i++) {
		list_add_item((void **)&elem, &i, sizeof(i));
	}
	for (i = 0; i <= 5; i++) {
		cr_assert_eq(*elem, i);
		list_next((void **)&elem);
	}
	cr_assert_eq(list_next((void **)&elem), false);
	cr_assert_eq(*elem, 5);
	list_delete((void **)&elem);
}

Test(list, prev)
{
	int *elem = NULL;
	int i;

	for (i = 0; i <= 5; i++) {
		list_add_item((void **)&elem, &i, sizeof(i));
	}
	for (i = 0; i < 4; i++) {
		list_next((void **)&elem);
	}
	for (i = 4; i >= 0; i--) {
		cr_assert_eq(*elem, i);
		list_prev((void **)&elem);
	}
	cr_assert_eq(list_prev((void **)&elem), false);
	cr_assert_eq(*elem, 0);
	list_delete((void **)&elem);
}