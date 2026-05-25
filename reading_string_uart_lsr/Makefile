CROSS = riscv64-elf
AS = $(CROSS)-as
CC = $(CROSS)-gcc
LD = $(CROSS)-ld

ASFLAGS = -march=rv64i -mabi=lp64
CFLAGS = -ffreestanding -march=rv64i -mabi=lp64 -mcmodel=medany
LDFLAGS = -T linker.ld

OBJ = startup.o main.o

all: kernel.elf

startup.o: startup.s
	$(AS) $(ASFLAGS) -o $@ $<

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

kernel.elf: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

run: kernel.elf
	qemu-system-riscv64 -machine virt -bios none -kernel kernel.elf -nographic

clean:
	rm -rf $(OBJ) kernel.elf

.PHONY: all clean run


