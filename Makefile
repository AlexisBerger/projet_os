OBJ=debug

all: $(OBJ) 

debug: bootsect kernel
	cat ./boot/bootsect ./kern/kernel /dev/zero | dd of=./debug/debug.img bs=512 count=2880

bootsect: 
	make -C boot

kernel: 
	make -C kern
	
clean:
	rm -rf kern/*.o

floppy: bootsect kernel
	cat ./boot/bootsect ./kern/kernel /dev/zero | dd of=/dev/fd0 bs=512 count=2880
	 