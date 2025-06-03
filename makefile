ASM 			= nasm
CC				= bcc
LINKER			= ld86
FLOPPY_IMG 		= bin/floppy.img
INCLUDE_PATH	= include/
BOOTLOADER_SRC 	= src/bootloader.asm
BOOTLOADER_BIN 	= bin/bootloader.bin
KERNEL_ASM_SRC	= src/kernel.asm
KERNEL_C_SRC	= src/kernel.c
KERNEL_ASM_OBJ	= bin/kernel-asm.o
KERNEL_C_OBJ	= bin/kernel.o
KERNEL_BIN		= bin/kernel.bin
SHELL_C_SRC		= src/shell.c
SHELL_C_OBJ		= bin/shell.o
STDLIB_C_SRC	= src/std_lib.c
STDLIB_C_OBJ	= bin/std_lib.o
EMULATOR		= bochs
EMULATOR_SRC	= bochsrc.txt

prepare:
	dd if=/dev/zero of=$(FLOPPY_IMG) bs=512 count=2880

bootloader:
	$(ASM) -f bin $(BOOTLOADER_SRC) -o $(BOOTLOADER_BIN)
	dd if=$(BOOTLOADER_BIN) of=$(FLOPPY_IMG) bs=512 count=1 conv=notrunc

stdlib:
	$(CC) -I$(INCLUDE_PATH) -ansi -c $(STDLIB_C_SRC) -o $(STDLIB_C_OBJ)

shell:
	$(CC) -I$(INCLUDE_PATH) -ansi -c $(SHELL_C_SRC) -o $(SHELL_C_OBJ)

kernel:
	$(ASM) -f as86 $(KERNEL_ASM_SRC) -o $(KERNEL_ASM_OBJ)
	$(CC) -I$(INCLUDE_PATH) -ansi -c $(KERNEL_C_SRC) -o $(KERNEL_C_OBJ)
	$(LINKER) -o $(KERNEL_BIN) -d $(KERNEL_C_OBJ) $(KERNEL_ASM_OBJ) $(SHELL_C_OBJ) $(STDLIB_C_OBJ)

link:
	dd if=$(KERNEL_BIN) of=$(FLOPPY_IMG) bs=512 seek=1 conv=notrunc

build: prepare bootloader stdlib shell kernel link
	$(EMULATOR) -f $(EMULATOR_SRC)
