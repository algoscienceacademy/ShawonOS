ASM=nasm
CC=x86_64-elf-gcc
LD=x86_64-elf-ld

ASMFLAGS=-f elf32
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c -I src/include
LDFLAGS=-T src/linker.ld -melf_i386

OBJECTS=obj/boot.o obj/kernel.o obj/memory.o obj/process.o obj/syscall.o obj/idt.o obj/idt_load.o

.PHONY: all clean run

all: bin/shawonos.bin

obj/boot.o: src/boot/boot.asm
	@mkdir -p obj
	$(ASM) $(ASMFLAGS) $< -o $@

obj/kernel.o: src/kernel/kernel.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $< -o $@

obj/memory.o: src/kernel/memory.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $< -o $@

obj/process.o: src/kernel/process.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $< -o $@

obj/syscall.o: src/kernel/syscall.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $< -o $@

obj/idt.o: src/kernel/idt.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $< -o $@

# Update assembly file compilation rules
obj/%.o: src/boot/%.asm
	nasm -f elf32 $< -o $@

obj/%.o: src/kernel/%.asm
	nasm -f elf32 $< -o $@

bin/shawonos.bin: $(OBJECTS)
	@mkdir -p bin
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf obj bin

run: bin/shawonos.bin
	qemu-system-i386 -kernel bin/shawonos.bin -monitor stdio -no-reboot -no-shutdown
