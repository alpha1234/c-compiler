
CFLAGS=-std=c++14
CC=g++

all: main

main: build/compiler.o build/common.o build/preprocessor.o build/lex.o
	$(CC) $(CFLAGS) build/compiler.o build/common.o build/preprocessor.o build/lex.o $(file)

build/compiler.o: compiler.cpp
	$(CC) $(CFLAGS) -c -o build/compiler.o compiler.cpp

build/common.o: common.cpp
	$(CC) $(CFLAGS) -c -o build/common.o common.cpp

build/preprocessor.o: preprocessor.cpp
	$(CC) $(CFLAGS) -c -o build/preprocessor.o preprocessor.cpp

build/lex.o: lex.cpp
	$(CC) $(CFLAGS) -c -o build/lex.o lex.cpp

.PHONY: clean

clean:
	del /Q build
