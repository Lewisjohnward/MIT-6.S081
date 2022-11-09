#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

/*
 * time taken 2:25
 *
 * Implementation of xargs
 * 
 *
 *
 * NOTES
 *
 * calls exec(*char, *args[]);
 *
 * when using exec *args[] must have NULL as last arg
 * args[0] is the name of the program being executed
 *
 * fork() returns 0 in child j
 *
 */

int
main (int argc, char *argv[])
{
    char *p;
    char buffer[512];
    char *args[MAXARG];

    p = buffer;

    int i = 0;
    for(; i < argc - 1; i++)
    {
        args[i] = argv[i + 1];
    }

    args[i] = p;
    i++;
    while(read(0, p, 1) > 0){
        if(*p == '\n')
        {
            *p++ = 0;
            args[i] = 0;

            if(fork() == 0)
            {
                exec(argv[1], args);
                exit(0);
            }else{
                wait(0);
            }
        }
        p++;
    }
    exit(0);
}
