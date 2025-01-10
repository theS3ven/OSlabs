UNAME_S := $(shell uname -s)

CFLAGS = -g -Iinclude

build_requirements:
	mkdir -p bin

log: build_requirements
	gcc $(CFLAGS) -c src/log.c -o bin/log.o

child1: build_requirements log
	gcc $(CFLAGS) -c src/ChildOne.c -o bin/child1.o
	gcc $(CFLAGS) bin/log.o bin/child1.o -o bin/child1

child2: build_requirements log
	gcc $(CFLAGS) -c src/ChildTwo.c -o bin/child2.o
	gcc $(CFLAGS) bin/log.o bin/child2.o -o bin/child2

main:  build_requirements log
	gcc $(CFLAGS) -c src/main.c -o bin/main.o
	gcc $(CFLAGS) bin/log.o bin/main.o -o bin/main
	

build: build_requirements child1 child2 main

run: build
	cd bin && ./main

debug: build

ifeq ($(UNAME_S),Darwin)
debug: 
	cd bin && lldb ./main
endif
ifeq ($(UNAME_S),Linux)
debug: 
	cd bin && gdb ./main
endif




strace: build
	cd bin && strace -f ./main