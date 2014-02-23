#include "types.h"
#include "io.h"

#define __SCREEN__
#include "screen.h"


/* 
 * 'scrollup' scrolle l'ecran (la console mappee en ram) vers le haut
 * de n lignes (de 0 a 25).
 */
void scrollup(unsigned int n)
{
	unsigned char *video, *tmp;

	for (video = (unsigned char *) RAMSCREEN;
	     video < (unsigned char *) SCREENLIM; video += 2) {
		tmp = (unsigned char *) (video + n * 160);

		if (tmp < (unsigned char *) SCREENLIM) {
			*video = *tmp;
			*(video + 1) = *(tmp + 1);
		} else {
			*video = 0;
			*(video + 1) = 0x07;
		}
	}

	kY -= n;
	if (kY < 0)
		kY = 0;
}

void putcar(uchar c)
{
	unsigned char *video;

	if (c == 10) {		/* CR-NL */
		kX = 0;
		kY++;
	} else if (c == 9) {	/* TAB */
		kX = kX + 8 - (kX % 8);
	} else if (c == 13) {	/* CR */
		kX = 0;
	} else if(c == 8){ /* BS */
		c = 32;

		kX--;
		if (kX < 0) {
			
			if(kY){
				kX = 79;
				kY--;
			}
		}
		
		video = (unsigned char *) (RAMSCREEN + 2 * kX + 160 * kY);
		*video = c;
		*(video + 1) = kattr;

		
	} else {		/* autres caracteres */

		video = (unsigned char *) (RAMSCREEN + 2 * kX + 160 * kY);
		*video = c;
		*(video + 1) = kattr;

		kX++;
		if (kX > 79) {
			kX = 0;
			kY++;
		}
	}

	if (kY > 24)
		scrollup(kY - 24);
}

/*
 * 'print' affiche a l'ecran, a la position courante du curseur, une chaine
 * de caracteres terminee par \0.
 */
void print(char *string)
{
	while (*string != 0) {	/* tant que le caractere est different de 0x0 */
		putcar(*string);
		string++;
	}
}

/*
 * Affiche la valeur des n octets a l'adresse indiquee
 */
void dump(uchar* addr, int n)
{
	char c1, c2;
	char *tab = "0123456789ABCDEF";

	while(n--) {
		c1 = tab[(*addr & 0xF0)>>4];
		c2 = tab[*addr & 0x0F];
		addr++;
		putcar(c1);
		putcar(c2);
	}
}

void move_cursor(u8 x, u8 y)
{
	u16 c_pos;

	c_pos = y * 80 + x;

	outb(0x3d4, 0x0f);
	outb(0x3d5, (u8) c_pos);
	outb(0x3d4, 0x0e);
	outb(0x3d5, (u8) (c_pos >> 8));
}

void show_cursor(void)
{
	move_cursor(kX, kY);
}

void hide_cursor(void)
{
	move_cursor(-1, -1);
}




void print_u32_hex(u32 n)
{
    s32 tmp;

    

    char noZeroes = 1;

    int i;

	print("0x");

    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
	    putcar(tmp-0xA+'a');
        }
        else
        {
            noZeroes = 0;
            putcar(tmp+'0');
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        putcar (tmp-0xA+'a');
    }
    else
    {
	putcar (tmp+'0');
    }

}

void print_u32_dec(u32 n)
{
    s32 acc = (s32)n;
    char c[32];
    int i = 0;
    char c2[32];
    int j = 0;

    if (n == 0)
    {
        putcar('0');
        return;
    }


    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    
    c2[i--] = 0;
   
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    print(c2);

}


