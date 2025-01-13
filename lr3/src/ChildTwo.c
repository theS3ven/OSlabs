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
   	sem_wait(&shmp->sem2); 
	char* resultString;
	int j = 0;	
	for (int i = 0; shmp->buf[i] != '\0'; i++) {
		if (!(shmp->buf[i] == ' ' && shmp->buf[i + 1] == ' ')) {
			resultString[j++] = shmp->buf[i];
		}
	}
	resultString[j] = '\0';
	write(STDOUT_FILENO, resultString, strlen(resultString));
	return 0;
}