/*
** EPITECH PROJECT, 2018
** MyFTP - Server
** File description:
** Explode function
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**
*@brief free a wordtab
*
*@param wt [in] the wordtab
*/
void free_wordtab(char **wt)
{
	for (int i = 0; wt[i] != NULL; i++) {
		free(wt[i]);
	}
	free(wt);
}

static bool is_lim(char c, char *lim)
{
	for (int i = 0; lim[i]; i++)
		if (lim[i] == c)
			return (true);
	return (false);
}

static int count_words(char *str, char *lim)
{
	int words = 0;

	for (int i = 0; str[i]; ) {
		while (str[i] && is_lim(str[i], lim))
			i++;
		if (str[i]) {
			words++;
			while (str[i] && !is_lim(str[i], lim))
				i++;
		}
	}
	return (words);
}

static int word_len(char *str, char *lim)
{
	int len = 0;

	for (int i = 0; str[i]; i++) {
		if (is_lim(str[i], lim))
			return (len);
		len++;
	}
	return (len);
}

/**
*@brief explode a string
*
*@param str [in] the string
*@param lim [in] the limiters
*@return char** the exploded string
*/
char **explode(char *str, char *lim)
{
	int len;
	int j = 0;
	int words = count_words(str, lim);
	char **tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	tab[words] = NULL;
	for (int i = 0; str[i]; j++) {
		while (str[i] && is_lim(str[i], lim))
			i++;
		if (str[i]) {
			len = word_len(str + i, lim);
			tab[j] = malloc(sizeof(char) * (len + 1));
			strncpy(tab[j], str + i, len);
			tab[j][len] = '\0';
			i += len;
		}
	}
	return (tab);
}