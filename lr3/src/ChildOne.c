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
    sem_post(&shmp->sem2);
	return 0;
}
