CC = gcc
CFLAGS = -g -Wall -Werror -Wpedantic

make all: simple_pipe


pipe_pong: pipe_pong.c
	$(CC) $(CFLAGS) -o pipe_pong pipe_pong.c
	./pipe_pong

simple_pipe: simple_pipe.c
	$(CC) $(CFLAGS) -o simple_pipe simple_pipe.c
	./simple_pipe
