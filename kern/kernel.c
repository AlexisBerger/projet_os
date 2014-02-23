#include "types.h"
#include "gdt.h"
#include "screen.h"
#include "io.h"
#include "idt.h"
#include "lib.h"
#include "acsii_art.h"

void init_pic(void);


int main(void);

void _start(void)
{
	kY = 3;
	kattr = 0x0E;
	scrollup(25);

	init_idt();
	print("kernel : idt loaded\n");

	init_pic();
	print("kernel : pic configured\n");

	/* Initialisation de la GDT et des segments */
	init_gdt();
	print("kernel : gdt loaded\n");
	
	/* Initialisation du TSS */
	asm("	movw $0x38, %ax \n \
		ltr %ax");
	print("kernel : tr loaded\n");

	/* Initialisation du pointeur de pile %esp */
	asm("	movw $0x18, %ax \n \
		movw %ax, %ss \n \
		movl $0x20000, %esp");
/*
	sti; //active les interruption sti != cli 
	kattr = 0x47;
	print("kernel : allowing interrupt\n");
*/


	main();
}

void task1(void)
{
	//print("Execution task1 !!!");
	
	char *msg = (char*) 0x100; /* le message sera stocké en 0x30100 */
	msg[0] = 't';
	msg[1] = 'a';
	msg[2] = 's';
	msg[3] = 'k';
	msg[4] = '1';
	msg[5] = '\n';
	msg[6] = 0;

       asm("mov %0, %%ebx; mov $0x01, %%eax; int $0x30" :: "m" (msg));

	while(1);	
	return;
}

int main(void)
{
	
	kattr = 0x07;
	/*
	acsii_art_wds();
	show_cursor();
	*/
	hide_cursor();
	
	/* Copie de la fonction a son adresse */
	memcpy((char*) 0x30000, &task1, 100);	//copie de 100 instructions en 0x30000 de task1 
	
	kattr = 0x47;
	print("Passage en mode utilisateur (ring3 mode)\n");
	kattr = 0x07;
	asm("   cli \n \
		push $0x33 \n \
		push $0x30000 \n \
		pushfl \n \
		popl %%eax \n \
		orl $0x200, %%eax \n \
		and $0xFFFFBFFF, %%eax \n \
		push %%eax \n \
		push $0x23 \n \
		push $0x0 \n \
		movl $0x20000, %0 \n \
		movw $0x2B, %%ax \n \
		movw %%ax, %%ds \n \
		iret": "=m"(default_tss.esp0):);

	/* Jamais atteint ! */
	print("Erreur Critique, Arret du systeme\n");
	asm("hlt");
	//while (1);
}


