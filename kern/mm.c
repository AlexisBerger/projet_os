#include "types.h"
#include "screen.h"

#define	PAGING_FLAG	0x80000000	/* CR0 - bit 31 */

#define PD0_ADDR 0x20000	/* addr. page directory kernel */
#define PT0_ADDR 0x21000	/* addr. page table[0] kernel */

/* cree un mapping tel que vaddr = paddr sur 4Mo */
void init_mm(void)
{
    u32 *pd0;	/* kernel page directory */
    u32 *pt0;	/* kernel page table */
    u32 page_addr;
    int i;

    /* Creation du Page Directory */
    pd0 = (u32 *) PD0_ADDR;
    pd0[0] = PT0_ADDR;
    pd0[0] |= 3;
    for (i = 1; i < 1024; i++)
        pd0[i] = 0;


    /* Creation de la Page Table[0] */
    pt0 = (u32 *) PT0_ADDR;
    page_addr = 0;
    for (i = 0; i < 1024; i++) {
        pt0[i] = page_addr;
        pt0[i] |= 3;
        page_addr += 4096;
    }
    //print("enabled paging start\n");
    asm("	mov $0, %%eax    \n \
		mov %%eax, %%cr3 \n \
		mov %%cr0, %%eax \n \
		or $1, %%eax     \n \
		mov %%eax, %%cr0" :: "i"(PD0_ADDR), "i"(PAGING_FLAG));
    //print("enabled paging end\n");
}