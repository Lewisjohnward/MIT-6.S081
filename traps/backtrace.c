
/*
 * time taken 2 hrs
 *
 * notes: I was initially generating only the memory addresses of the 
 *        previous stack frames but not getting the return addresses
 *
 */

void 
backtrace(void)
{
    uint64 addr, pagetop;
    addr = r_fp();
    pagetop = PGROUNDUP(addr);
    do printf("%p\n", *(uint64 *) (addr - 8));
    while((addr = *(uint64 *)(addr - 16)) != pagetop);
}
