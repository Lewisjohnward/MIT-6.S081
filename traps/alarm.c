/*
 *
 * Time : 2hrs
 *
 * Way easier than pagetables
 *
 *
 */


/* trap.c */
if(which_dev == 2)
{
    if(!p->handling && p->alarmint && p->tickcount++ == p->alarmint)
    {
        p->handling = 1;
        p->tickcount = 0;
        savetrapframe();
        p->trapframe->epc = p->alarmhandler;

    }
    yield();
}

/* syscall.c */
uint64
sys_sigalarm(void)
{
    int ticks;
    uint64 fun;
  if(argint(0, &ticks) < 0)
    return -1;
  if(argaddr(1, &fun) < 0)
    return -1;
  myproc()->alarmint = ticks;
  myproc()->alarmhandler = fun;
  return 0;
}

uint64
sys_sigreturn(void)
{
    struct proc *p = myproc();
   p->trapframe->kernel_satp = p->rettrapframe.kernel_satp;
   p->trapframe->kernel_sp = p->rettrapframe.kernel_sp;
   p->trapframe->kernel_trap = p->rettrapframe.kernel_trap;
   p->trapframe->epc = p->rettrapframe.epc;
   p->trapframe->kernel_hartid = p->rettrapframe.kernel_hartid;
   p->trapframe->ra = p->rettrapframe.ra;
   p->trapframe->sp = p->rettrapframe.sp;
   p->trapframe->gp = p->rettrapframe.gp;
   p->trapframe->tp = p->rettrapframe.tp;
   p->trapframe->t0 = p->rettrapframe.t0;
   p->trapframe->s0 = p->rettrapframe.s0;
   p->trapframe->s1 = p->rettrapframe.s1;
   p->trapframe->a0 = p->rettrapframe.a0;
   p->trapframe->a1 = p->rettrapframe.a1;
   p->trapframe->a2 = p->rettrapframe.a2;
   p->trapframe->a3 = p->rettrapframe.a3;
   p->trapframe->a4 = p->rettrapframe.a4;
   p->trapframe->a5 = p->rettrapframe.a5;
   p->trapframe->a6 = p->rettrapframe.a6;
   p->trapframe->a7 = p->rettrapframe.a7;
   p->trapframe->s2 = p->rettrapframe.s2;
   p->trapframe->s3 = p->rettrapframe.s3;
   p->trapframe->s4 = p->rettrapframe.s4;
   p->trapframe->s5 = p->rettrapframe.s5;
   p->trapframe->s6 = p->rettrapframe.s6;
   p->trapframe->s7 = p->rettrapframe.s7;
   p->trapframe->s8 = p->rettrapframe.s8;
   p->trapframe->s9 = p->rettrapframe.s9;
   p->trapframe->s10 = p->rettrapframe.s10;
   p->trapframe->s11 = p->rettrapframe.s11;
   p->trapframe->t3 = p->rettrapframe.t3;
   p->trapframe->t4 = p->rettrapframe.t4;
   p->trapframe->t5 = p->rettrapframe.t5;
   p->trapframe->t6 = p->rettrapframe.t6;
   p->handling = 0;
  return 0; 
}
