/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Logs
*/

#include "server.h"

/**
*@brief Print and format a log line
*
*@param fd [in] The fd used to print on it
*@param file [in] The current filename
*@param line [in] The current line number
*@param color [in] The color to use
*/
static void print_current_info(FILE *fd, char *file, int line, char *color)
{
	time_t rawtime;
	struct tm *info;
	char buffer[80];

	time(&rawtime);
	info = localtime(&rawtime);
	strftime(buffer, 80, "%d-%m-%Y %T", info);
	fprintf(fd, "%s[%s] %s:%d ~ ", color, buffer, file, line);
}

/**
*@brief Print an info log
*
*@param file [in] The current filename
*@param line [in] The current line number
*@param format [in] The format to print
*@param ... The format params
*/
bool log_info(char *file, int line, char *format, ...)
{
	va_list args;

	va_start(args, format);
	print_current_info(stdout, file, line, "\x1B[37m");
	vfprintf(stdout, format, args);
	va_end(args);
	printf("\n\x1B[37m");
	return (true);
}

/**
*@brief Print an info log
*
*@param file [in] The current filename
*@param line [in] The current line number
*@param format [in] The format to print
*@param ... The format params
*/
bool log_warn(char *file, int line, char *format, ...)
{
	va_list args;

	va_start(args, format);
	print_current_info(stdout, file, line, "\x1B[33m");
	vfprintf(stdout, format, args);
	va_end(args);
	printf("\n\x1B[37m");
	return (true);
}

/**
*@brief Print an error log
*
*@param file [in] The current filename
*@param line [in] The current line number
*@param format [in] The format to print
*@param ... The format params
*/
bool log_error(char *file, int line, char *format, ...)
{
	va_list args;

	va_start(args, format);
	print_current_info(stderr, file, line, "\x1B[31m");
	fprintf(stderr, "\x1B[31m");
	vfprintf(stderr, format, args);
	va_end(args);
	fprintf(stderr, "\n\x1B[37m");
	return (true);
}

/**
*@brief Print a perror log
*
*@param file [in] The current filename
*@param line [in] The current line number
*@param format [in] The format to print
*@param ... The format params
*/
bool log_perror(char *file, int line, char *format, ...)
{
	va_list args;

	va_start(args, format);
	print_current_info(stderr, file, line, "\x1B[31m");
	fprintf(stderr, "\x1B[31m");
	vfprintf(stderr, format, args);
	write(2, ": ", 2);
	perror(NULL);
	va_end(args);
	fprintf(stderr, "\n\x1B[37m");
	return (true);
}