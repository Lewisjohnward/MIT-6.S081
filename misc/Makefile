CC = gcc
CFLAGS = -g -Wall -Werror -Wpedantic
DEST = ../builds/

make all: simple_pipe


pipe_pong: pipe_pong.c
	$(CC) $(CFLAGS) -o $(DEST)pipe_pong pipe_pong.c
	./pipe_pong

simple_pipe: simple_pipe.c
	$(CC) $(CFLAGS) -o $(DEST)simple_pipe simple_pipe.c
	./simple_pipe
