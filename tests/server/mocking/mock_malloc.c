/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** malloc
*/

#include <stdlib.h>
#include "tests.h"

#undef malloc

void *malloc_test(size_t size) {
	if (stest_malloc)
		return (NULL);
	return (malloc(size));
}

#define malloc(a) malloc_test(a)
