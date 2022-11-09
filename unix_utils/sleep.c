#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


/*
 *
 * time taken 25 mins
 *
 *
 *
 */

int
main (int argc, char *argv[])
{
    int t;
    if(argc != 2)
    {
        fprintf(2, "sleep X\n");
        exit(1);
    }
    t = atoi(argv[1]);
    sleep(t);
    exit(0);
}
