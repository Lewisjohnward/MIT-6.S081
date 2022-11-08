#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/resource.h>



int main (void)
{
    int pipefd0[2], pipefd1[2];
    pid_t cpid;
    char ball = 'o';
    char buf;

    time_t start, stop;
    start = time(NULL);


    if(pipe(pipefd0) == -1 || pipe(pipefd1) == -1)
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
        clock_t c_start, c_stop;
        double count = 0;
        double r_time;
        close(pipefd0[1]); /* this is the writing end */
        c_start = clock();
        while(read(pipefd0[0], &buf, 1) > 0)
        {
            write(pipefd1[1], &buf, 1);
            count++;
            stop = time(NULL);
            if(stop - start > 1)
            {
                c_stop = clock();
                r_time = (c_stop - c_start);
                printf("clock() time: %.2fs\n", r_time / CLOCKS_PER_SEC);
                printf("exchanges in a second: %ld\n", (unsigned long) count);
                printf("average RTT %f\n", (1 / count) * 1000);
                close(pipefd1[1]);
                _exit(EXIT_SUCCESS);
            }
        }

    }
    else
    {
        close(pipefd0[0]); /*close read end */
        write(pipefd0[1], &ball, 1);
        while(read(pipefd1[0], &buf, 1) > 0)
        {
            write(pipefd0[1], &ball, 1);
            stop = time(NULL);
            if(stop - start > 1)
            {
                close(pipefd0[1]);
                _exit(EXIT_SUCCESS);
            }
        }
   }


}
