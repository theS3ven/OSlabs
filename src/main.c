#include <config/config.h>
#include <fcntl.h>
#include <log/log.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *get_string(int *len) {
	*len = 0;
	int capacity = 1;
	char *s = (char *)malloc(sizeof(char));

	char c = getchar();

	while (c != '\n' && c != EOF) {
		s[(*len)++] = c;

		if (*len >= capacity) {
			capacity *= 2;  // увеличиваем ёмкость строки в два раза
			s = (char *)realloc(s, capacity * sizeof(char));  // перевыделяем память на строку с увеличенной ёмкостью
		}

		c = getchar();
	}

	s[*len] = '\0';  // завершаем строку символом конца строки

	return s;
}

int main() {
	const char *args[] = {"./trash", NULL};

	int pipe1[2], pipe2[2], pipe3[2];
	pipe(pipe3);
	pipe(pipe1);
	pipe(pipe2);

	pid_t pId1 = fork();

	if (pId1 == 0) {
		dup2(pipe1[0], STDIN_FILENO);   // Redirect standard input to read from pipe1
		dup2(pipe3[1], STDOUT_FILENO);  // Redirect standard output to write to pipe3
		close(pipe1[1]);
		close(pipe3[0]);

		int status = execv("./child1", (char **)args);

		exit(status);
	}
	//
	pid_t pId2 = fork();
	if (pId2 == 0) {
		dup2(pipe3[0], STDIN_FILENO);   // Redirect standard input to read from pipe3
		dup2(pipe2[1], STDOUT_FILENO);  // Redirect standard output to write to pipe2
		close(pipe2[0]);
		close(pipe3[1]);

		int status = execv("./child2", (char **)args);
		exit(status);
	}

	close(pipe2[1]);
	close(pipe1[0]);
	// dup2(STDOUT_FILENO, pipe2[0]);
	int log_file = create_log_file("main");
	int len = 0;
	do {
		char buffer[128];
		// char *data = get_string(&len);
		char data2[128];
		ssize_t read_b = read(STDIN_FILENO, data2, 128);
		if (read_b == -1) {
			break;
		}

		write(pipe1[1], data2, strlen(data2));
		if (data2[0] == '\n') {
			break;
		}
		// free(data);
		ssize_t bytes = read(pipe2[0], buffer, 128);
		if (bytes == -1) {
			break;
		}
		log_to_file(log_file, "got %ld bytes\n", bytes);

		char str_buff[128];
		snprintf(str_buff, 128, "Got output: %s\n", buffer);
		write(STDOUT_FILENO, str_buff, strlen(str_buff));
		log_to_file(log_file, "got %s", buffer);
		// printf("Got output: %s\n", buffer);
	} while (true);

	waitpid(pId1, NULL, 0);
	waitpid(pId2, NULL, 0);
	close(pipe1[1]);
	close(pipe2[0]);
	close(pipe3[1]);
	return 0;
}
