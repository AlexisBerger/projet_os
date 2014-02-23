OBJ=kernel
CC=gcc -Wall -fno-stack-protector

all: $(OBJ) 

kernel: kernel.o screen.o lib.o gdt.o idt.o interrupt.o int.o pic.o acsii_art.o syscalls.o
	ld --oformat binary -Ttext 1000 $^ -o $@

int.o: int.asm
	nasm -f elf -o $@ $^ 

.o: .c 
	$(CC) -c $^


