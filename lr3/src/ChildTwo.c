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

	int len_cpy = 0, capacity = 2; 
    char *cpy = (char*) malloc(capacity * sizeof(char));
    cpy[0] = shmp->buf[0];

    for(int i = 0; i < shmp->cnt; i++) { 
        if (len_cpy >= capacity) {
            capacity *= 2; 
            cpy = (char*) realloc(cpy, capacity * sizeof(char));
        }

        if (!(shmp->buf[i] == ' ' && shmp->buf[i + 1] == ' ')) {
            cpy[len_cpy++] = shmp->buf[i];
        }
    }

    cpy = (char*) realloc(cpy, (capacity + 1) * sizeof(char));
    cpy[++len_cpy] = '\0';

    for(int i = 0; i < len_cpy; i++) {
        shmp->buf[i] = cpy[i];
    }

    sem_post(&shmp->sem3); // Разрешаем чтение родителю

    free(cpy);
	return 0;
}
