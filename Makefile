ASM=nasm
CC=x86_64-elf-gcc
LD=x86_64-elf-ld

ASMFLAGS=-f elf32
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c -I src/include
LDFLAGS=-T src/linker.ld -melf_i386

OBJECTS=obj/boot.o obj/kernel.o obj/memory.o obj/process.o obj/syscall.o obj/idt.o obj/idt_load.o obj/isr.o obj/isr_asm.o obj/interrupt.o obj/interrupt_asm.o

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

obj/isr.o: src/kernel/isr.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $< -o $@

obj/isr_asm.o: src/kernel/isr_asm.asm
	@mkdir -p obj
	nasm -f elf32 $< -o $@

# Add compilation rules for interrupt files
obj/interrupt.o: src/kernel/interrupt.c
	$(CC) $(CFLAGS) $< -o $@

obj/interrupt_asm.o: src/kernel/interrupt_asm.asm
	nasm -f elf32 $< -o $@

# Update assembly file compilation rules
obj/%.o: src/boot/%.asm
	nasm -f elf32 $< -o $@

obj/%.o: src/kernel/%.asm
	nasm -f elf32 $< -o $@

# Update the linking rule to include the new object files
bin/shawonos.bin: obj/boot.o obj/kernel.o obj/memory.o obj/process.o obj/syscall.o obj/idt.o obj/idt_load.o obj/isr.o obj/isr_asm.o obj/interrupt.o obj/interrupt_asm.o
	@mkdir -p bin
	$(LD) $(LDFLAGS) $^ -o $@

clean:
	rm -rf obj bin

run: bin/shawonos.bin
	qemu-system-i386 -kernel bin/shawonos.bin -monitor stdio -no-reboot -no-shutdown
