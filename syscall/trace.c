
/*
 *
 * time taken: 3hr
 *
 * I was making the silly mistake of printing trace before the
 * system calls returned
 *
 *
 * This big additions to xv6 are below but there is also an addition
 * in proc where you copy the mask from parent to child process
 *
 *
 */




/*
 *
 * 
 * sysproc.c
 * 
 *
 */

uint64
sys_trace(void)
{
    int mask;
    if(argint(0, &mask) < 0)
        return -1;
    myproc()->mask = mask;
    return 0;
}

/*
 *
 *
 * syscall .c 
 *
 *
 * */

char *syscallnames[] = {"fork", "exit", "wait", "pipe", "read", "kill", "exec", "fstat", "chdir", "dup", "getpid", "sbrk", "sleep", "uptime", "open", "write", "mknod", "unlink", "link", "mkdir", "close", "trace"};
//

void printtrace(int mask, int syscall, struct proc *p)
{
    int returnval, pid;
    /* syscall puts return value in a0 */
    returnval = p->trapframe->a0;
    pid = p->pid;

    if((mask>>syscall) & 1)
        printf("%d: syscall %s -> %d\n", pid, syscallnames[syscall - 1], returnval);

}


/* Everytime a system call is made it comes through here */
    void
syscall(void)
{

    int num, mask;
    struct proc *p = myproc();

    /* get system call number */
    num = p->trapframe->a7;

    if(num > 0 && num < NELEM(syscalls) && syscalls[num]) {
        p->trapframe->a0 = syscalls[num]();
    } else {
        printf("%d %s: unknown sys call %d\n", p->pid, p->name, num);
        p->trapframe->a0 = -1;
    }

    /* get mask */
    mask = p->mask;

    /* If tracemask is non zero then trace active */
    if(mask)
        printtrace(mask, num, p);
}
