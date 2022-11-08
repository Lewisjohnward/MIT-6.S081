#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

/*
 *
 * A program that spawns a child process and then "ping-pongs" a byte between 
 * the two processes over a pair of pipes
 *
 */



int main (void)
{
    int pipefd[2];
    pid_t cpid;
    char buf;
    char message[] = "hello from parent process";

    if(pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if(cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(cpid == 0)
    {
        close(pipefd[1]); /* close write end */
        while (read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);

        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);

    } 
    else
    {
        close(pipefd[0]); /* close read end */
        write(pipefd[1], message, strlen(message));
        close(pipefd[1]);  /*reader will rec EOF */
        wait(NULL);         /*wait for child */
        exit(EXIT_SUCCESS);
    }
    return 0;
}
