#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "header.h"

void StringToLower(int readFD, int writeFD) {
	char buffer[256];
	read(readFD, buffer, sizeof(buffer));  // Чтение строки от parrent
	for (int i = 0; buffer[i] != '\0'; i++) {
		char c = buffer[i];
		if (c >= 'a' && c <= 'z') {
			buffer[i] -= 'a' - 'A';
		} else if (c >= 'A' && c <= 'Z') {
			buffer[i] += 'a' - 'A';
		}
	}
	write(writeFD, buffer, sizeof(buffer));
}
