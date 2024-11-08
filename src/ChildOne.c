#include <config/config.h>
#include <fcntl.h>
#include <log/log.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
	char buffer[LINE_BUFFER_LEN];
	int log_file = create_log_file("child1");
	log_to_file(log_file, "Dolbaeb is working, pid %d", getpid());
	ssize_t bytes = 0;
	while ((bytes = read(STDIN_FILENO, buffer, LINE_BUFFER_LEN)) != -1) {
		log_to_file(log_file, "Dolbaeb with pid %d got \'%s\', bytes read %d", getpid(), buffer, bytes);
		if (buffer[0] == '\n') {
			log_to_file(log_file, "Dobaeb exitiing");
			write(STDOUT_FILENO, buffer, LINE_BUFFER_LEN);
			break;
		}
		for (int i = 0; buffer[i] != '\0'; i++) {
			char c = buffer[i];
			if (c >= 'A' && c <= 'Z') {
				buffer[i] += 'a' - 'A';
			}
		}
		if (write(STDOUT_FILENO, buffer, LINE_BUFFER_LEN) == -1) {
			log_to_file(log_file, "Dolbaeb with pid %d got error during writing", getpid(), buffer);
		}
		log_to_file(log_file, "Dolbaeb with pid %d wrote \'%s\'", getpid(), buffer);
	}
	write(log_file, "", 1);
	close(log_file);
	return 0;
}
