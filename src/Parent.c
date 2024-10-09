#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "header.h"

int main() {
	int pipeOne[2], pipeTwo[2], pipeBetween[2];  // Создание "труб" для соединения от/к родителя к детям
	if (pipe(pipeOne) == -1) {
		const char msg[] = "error: fail to create a pipe one\n";
		write(STDERR_FILENO, msg, sizeof(msg));
		exit(EXIT_FAILURE);
	}
	if (pipe(pipeTwo) == -1) {
		const char msg[] = "error: fail to create a pipe two\n";
		write(STDERR_FILENO, msg, sizeof(msg));
		exit(EXIT_FAILURE);
	}
	if (pipe(pipeBetween) == -1) {
		const char msg[] = "error: fail to create a pipe between children\n";
		write(STDERR_FILENO, msg, sizeof(msg));
		exit(EXIT_FAILURE);
	}
	pid_t pidOne, pidTwo = fork(), fork();  // Создание дочерних процессов
	if (pidOne < 0) {
		perror("fork failed for child one\n");
		exit(EXIT_FAILURE);
	}
	if (pidOne == 0) {
		close(pipeOne[1]);  // Закрываем неиспользуемый кусок памяти под пайп
		dup2(pipeTwo[1], STDOUT_FILENO);  // Передаем поток в pipe 2
		close(pipeTwo[1]);
		StringToLower(pipeOne[0], pipeBetween[0]);
		exit(0);
	}
	waitpid(pidOne, NULL, 0);
	if (pidTwo < 0) {
		perror("fork failed for child two\n");
		exit(EXIT_FAILURE);
	}
	if (pidTwo == 0) {
		close(pipeTwo[1]);
		dup2(pipeTwo[1], STDIN_FILENO);
		close(pipeOne[0]);
		RemoveSpaces(pipeBetween[0], pipeTwo[0]);
		exit(0);
	}
	waitpid(pidTwo, NULL, 0);
	char output[256];
	read(pipeTwo[0], output, sizeof(output));
	write(STDIN_FILENO, output, sizeof(output));
}