
/*
 *
 * time taken 2hrs
 *
 * Notes
 * pagetable is an array of 2^9 PTEs 
 *
 *
 * tables dont go further than 3 levels so need to check
 *
 *
 */


void print(pagetable_t pagetable, int *depth)
{
    /* There are 2^9 = 512 PTEs in a page table */
    for(int i =  0; i < 512; i++)
    {
        /* entry - 64bit address */
        pte_t pte = pagetable[i];
        pte_t pa = PTE2PA(pte);
        /* if pte is valid */
        if(pte & PTE_V){
            for(int j = 0; j < *depth; j++)
                printf(".. ");
            printf("..%d: pte %p pa %p\n", i, pte, pa);
            (*depth)++;
            if(*depth < 3)
                print((pagetable_t) pa, depth);
            (*depth)--;
        }
    }
}

void
vmprint(pagetable_t pagetable)
{
    int depth = 0;
    /* pagetable is an array of 512 PTEs - addresses*/
    printf("page table: %p\n", pagetable);
    print(pagetable, &depth);
}
