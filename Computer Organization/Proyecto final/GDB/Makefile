ARMGNU ?= aarch64-linux-gnu

AOPS = --warn --fatal-warnings

asm : kernel.img

all : asm

clean :
	rm -f *.o
	rm -f *.img
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f memory_map.txt

app.o : app.s
	$(ARMGNU)-as -g $(AOPS) app.s -o app.o


kernel.img : memmap app.o
	$(ARMGNU)-ld app.o -T memmap -o app.elf -M > memory_map.txt
	$(ARMGNU)-objdump -D app.elf > app.list
	$(ARMGNU)-objcopy app.elf -O ihex app.hex
	$(ARMGNU)-objcopy app.elf -O binary kernel.img

runQEMU : 
	qemu-system-aarch64 -s -S -machine virt -cpu cortex-a53 -machine type=virt -nographic -smp 1 -m 64 -kernel kernel.img

runGDB: 
	gdb-multiarch -ex "set architecture aarch64" -ex "target remote localhost:1234" --ex "dashboard registers -style list 'x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 x10 x11 x12 x13 x14 x15 x16 x17 x18 x19 x20 x21 x22 x23 x24 x25 x26 x27 x28 x29 x30 sp pc cpsr'"
