#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "pshm_ucase.h"

int main() {
	const char name[] = "/sosal";
	struct shmbuf *shmp;
	int fd = shm_open(name, O_RDWR, 0);
    shmp = mmap(NULL, sizeof(shmp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	sem_wait(&shmp->sem1);
	int len = strlen(shmp->buf);
	for (int i = 0; i < len; i++) {
			char c = shmp->buf[i];
			if (c >= 'A' && c <= 'Z') {
				shmp->buf[i] += 'a' - 'A';
			}
		}
		if (write(STDOUT_FILENO, shmp->buf, len) == -1) {
			// log_to_file(log_file, "Dolbaeb with pid %d got error during writing", getpid(), buffer);
		}
		// log_to_file(log_file, "Dolbaeb with pid %d wrote \'%s\'", getpid(), buffer);
	// write(log_file, "", 1);
	// close(log_file);
	return 0;
}
