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

void task1()
{
	print("Execution task1 !!!");
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
	

	while (1);
}

