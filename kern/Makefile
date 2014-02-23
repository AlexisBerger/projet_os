OBJ=kernel
CC=gcc -Wall -fno-stack-protector -m32

all: $(OBJ) 

kernel: kernel.o screen.o lib.o gdt.o idt.o interrupt.o int.o pic.o acsii_art.o syscalls.o mm.o
	ld -m elf_i386 --oformat binary -Ttext 1000 $^ -o $@

int.o: int.asm
	nasm -f elf -o $@ $^ 

.o: .c 

	$(CC) -c $^


