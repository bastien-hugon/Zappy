/*
** EPITECH PROJECT, 2018
** Zappy - Server
** File description:
** Logs System
*/

#ifndef LOGS_H_
	#define LOGS_H_

	#include "server.h"

	#define __FILENAME__ \
	(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

	#define LOG(a, ...) \
	(log_info(__FILENAME__, __LINE__, a, ##__VA_ARGS__))

	#define INFO(a, ...) \
	(log_info(__FILENAME__, __LINE__, a, ##__VA_ARGS__))

	#define WARN(a, ...) \
	(log_warn(__FILENAME__, __LINE__, a, ##__VA_ARGS__))

	#define ERROR(a, ...) \
	(log_error(__FILENAME__, __LINE__, a, ##__VA_ARGS__))

	#define PERROR(a, ...) \
	(log_perror(__FILENAME__, __LINE__, a, ##__VA_ARGS__))

	bool log_info(char *file, int line, char *format, ...);
	bool log_warn(char *file, int line, char *format, ...);
	bool log_error(char *file, int line, char *format, ...);
	bool log_perror(char *file, int line, char *format, ...);

#endif /* !LOGS_H_ */
