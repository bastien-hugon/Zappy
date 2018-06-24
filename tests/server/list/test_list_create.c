/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_list_create
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "list.h"

Test(list, add_item)
{
	int *elem = NULL;
	int a = 5;
	list_t *l;

	list_push(&elem, &a);
	a++;
	list_push(&elem, &a);
	cr_assert_eq(5, *elem);
	l = (list_t *)(((char *)elem - sizeof(list_t)));
	l = l->next;
	elem = (int *)(((char *)l + sizeof(list_t)));
	cr_assert_eq(6, *elem);
	list_delete(&elem);
}

Test(list, add_item_memory_error) {
	stest_malloc = true;
	int a = 5;
	int *elem = NULL;

	char buffer[2000];
	cr_redirect_stderr();
	FILE *ferr = cr_get_redirected_stderr();
	cr_assert_eq(list_push(&elem, &a), false);
	cr_assert_null(elem);
	stest_malloc = false;
	fread(buffer, sizeof(buffer), sizeof(char), ferr);
	cr_assert_not_null(strstr(buffer, \
		"Error while allocating memory\n"));
}
