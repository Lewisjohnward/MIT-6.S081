CC = gcc
CFLAGS = -g -Wall -Werror -Wpedantic
DEST = ../builds

make all: pipe_pong


pipe_pong: pipe_pong.c
	$(CC) $(CFLAGS) -o $(DEST)/pipe_pong pipe_pong.c
	$(DEST)/pipe_pong

simple_pipe: simple_pipe.c
	$(CC) $(CFLAGS) -o $(DEST)/simple_pipe simple_pipe.c
	$(DEST)/simple_pipe
