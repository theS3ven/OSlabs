#ifndef LOG_H
#define LOG_H

#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define LOG_BUFFER_SIZE 1024
int create_log_file(const char* name);
void log_to_file(int file, char* fmt, ...);

#endif