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
*@param fd The fd used to print on it
*@param file The current filename
*@param line The current line number
*@param color The color to use
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
*@param file The current filename
*@param line The current line number
*@param format The format to print
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
*@param file The current filename
*@param line The current line number
*@param format The format to print
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
*@param file The current filename
*@param line The current line number
*@param format The format to print
*@param ... The format params
*/
bool log_error(char *file, int line, char *format, ...)
{
	va_list args;

	va_start(args, format);
	print_current_info(stderr, file, line, "\x1B[31m");
	printf("\x1B[31m");
	vfprintf(stdout, format, args);
	va_end(args);
	printf("\n\x1B[37m");
	return (true);
}

/**
*@brief Print a perror log
*
*@param file The current filename
*@param line The current line number
*@param format The format to print
*@param ... The format params
*/
bool log_perror(char *file, int line, char *format, ...)
{
	va_list args;

	va_start(args, format);
	print_current_info(stderr, file, line, "\x1B[31m");
	printf("\x1B[31m");
	vfprintf(stdout, format, args);
	write(2, ": ", 2);
	perror(NULL);
	va_end(args);
	printf("\n\x1B[37m");
	return (true);
}