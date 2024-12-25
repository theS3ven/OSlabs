#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
	char buffer[128];
	char resultString[128];
	// int log_file = create_log_file("child2");
	// log_to_file(log_file, "Dodik is working, pid %d", getpid());
	ssize_t bytes = 0;
	while ((bytes = read(STDIN_FILENO, buffer, 128))) {
		// log_to_file(log_file, "Dodik with pid %d got \'%s\', bytes read %d", getpid(), buffer, bytes);
		if (buffer[0] == '\n') {
			// log_to_file(log_file, "Dodik exitiing");
			break;
		}
		int j = 0;
		for (int i = 0; buffer[i] != '\0'; i++) {
			if (!(buffer[i] == ' ' && buffer[i + 1] == ' ')) {
				resultString[j++] = buffer[i];
			}
		}
		resultString[j] = '\0';
		// log_to_file(log_file, "Dodik with pid %d wrote \'%s\'", getpid(), resultString);
		write(STDOUT_FILENO, resultString, strlen(resultString));
	}
	// write(log_file, "", 1);
	// close(log_file);
	return 0;
}