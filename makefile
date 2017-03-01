CC=g++
CFLAGS=-std=c++14.

compiler: hellomake.o hellofunc.o
     $(CC) hellomake.o hellofunc.o -I.