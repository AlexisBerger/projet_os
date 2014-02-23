OBJ=/dev/fd0

all: $(OBJ) 

/dev/fd0: bootsect kernel
	cat ./boot/bootsect ./kern/kernel /dev/zero | dd of=/dev/fd0 bs=512 count=2880

bootsect: 
	make -C boot

kernel: 
	make -C kern


