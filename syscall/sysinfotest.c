
/*
 * time taken: 2hrs 10
 *
 *
 *  sysproc.c
 *
 *  I found this one easier than trace as the momentum was already there 
 *  from that part. 
 *
 *  on to the next one!
 */

int
popsysinfo (uint64 addr)
{
    struct proc *p = myproc();
    struct sysinfo si;
    si.nproc = proccount();
    si.freemem = kfreecount();
    if(copyout(p->pagetable, addr, (char *)&si, sizeof(si)) < 0)
        return -1;
    return 0;
}

uint64
sys_sysinfo(void)
{
    uint64 addr;
    if(argaddr(0, &addr) < 0)
        return -1;
    if (popsysinfo(addr) < 0)
        return -1;
    return 0;
}


/*
 *
 * kalloc.c
 *
 *
 */

uint64
kfreecount(void)
{
    struct run *r;
    int count = 1;
    r = kmem.freelist;
    if(r == 0)
        return 0;
    while((r = r->next) != 0)
        count++;
    return count * PGSIZE;
}

/*
 *
 * proc.c
 *
 *
 */

uint64 
proccount(void)
{
    int count = 0;
    struct proc *p;

    printf("\n");
    for(p = proc; p < &proc[NPROC]; p++){
        if(p->state != UNUSED)
            count++;
    }
    return count;
}


