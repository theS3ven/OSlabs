#include <log/log.h>

int create_log_file(const char* name) {
	char path[PATH_MAX];
	snprintf(path, PATH_MAX, "%s.log", name);
	return open(path, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0600);
}

void log_to_file(int file, char* fmt, ...) {
	char buff[LOG_BUFFER_SIZE];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buff, LOG_BUFFER_SIZE, fmt, args);
	write(file, buff, strlen(buff));
	write(file, "\n", 1);
	va_end(args);
}