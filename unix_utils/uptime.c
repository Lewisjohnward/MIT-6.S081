#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/*
 * 
 * prints the system uptime in terms of ticks using
 * the uptime syscall
 *
 */

int
main (int argc, char *argv[])
{
    int sys_uptime = uptime();

    printf("%d\n", sys_uptime);

    exit(0);
}
