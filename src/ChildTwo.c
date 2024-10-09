#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "header.h"

void RemoveSpaces(int readFD, int writeFD) {
	char buffer[256];
	read(readFD, buffer, sizeof(buffer));
	char resultString[256];
	int j = 0;
	for (int i = 1; buffer[i]; i++) {
		if (!(buffer[i] == ' ' && buffer[i - 1] == ' ')) {
			resultString[j++] += buffer[i];
		}
	}
	resultString[j] = '\0';
	write(writeFD, resultString, sizeof(resultString));
}