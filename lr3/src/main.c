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

#if 1
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
#endif
char *get_string(int *len);


int main() {
	const char *args[] = {"./trash", NULL};
	const char* shmpath = args[1];
	struct shmbuf *shmp;
	int len;
	char *s = get_string(&len); // считываем динамическую строку
    const char name[] = "/sosal"; // Имя общей памяти
	int fd = shm_open(name, O_CREAT | O_RDWR, 0600);
	if (ftruncate(fd, sizeof(struct shmbuf)) == -1)
    	errExit("ftruncate");
	shmp = mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE,
                           MAP_SHARED, fd, 0);

	if (shmp == MAP_FAILED)
		errExit("mmap");

	if (sem_init(&shmp->sem1, 1, 0) == -1)
        errExit("sem_init-sem1");
    if (sem_init(&shmp->sem2, 1, 0) == -1)
        errExit("sem_init-sem2");
	if (sem_init(&shmp->sem3, 1, 0) == -1)
        errExit("sem_init-sem3");

	shmp->cnt = len;
    memcpy(shmp->buf, s, len); // записываем строку в общую память
    sem_post(&shmp->sem1); // Разрешаем чтение первому ребенку 

	pid_t pId1, pId2;
	pId1 = fork();
	if (pId1 == 0) {
		int status = execv("./child1", (char **)args);
		exit(status);
	}

	if (pId1){
		pId2 = fork();
	}

	if (pId2 == 0){
		int status = execv("./child2", (char **)args);
		exit(status);
	}
	if (sem_post(&shmp->sem2) == -1)
        errExit("sem_post");

	sem_wait(&shmp->sem3);

    printf("Received array of size %ld: %s\n", strlen(shmp->buf), shmp->buf);


	munmap(shmp, sizeof(struct shmbuf));
	shm_unlink(name);
	free(s);

	return 0;
}
