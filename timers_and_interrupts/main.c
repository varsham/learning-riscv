#define UART ((volatile unsigned char *) 0x10000000)
#define UART_LSR ((volatile unsigned char *) 0x10000005)

#define MTIME ((volatile unsigned long *) 0x200BFF8)
#define MTIMECMP ((volatile unsigned long *) 0x2004000)
#define INTERVAL 10000000UL // 1 second at 10 MHz

void uart_putc(char c) { *UART = c; }
void uart_puts(char *s) {
    while (*s) uart_putc(*s++);
}

void trap_handler(void) {
    uart_puts("Timer fired!\n");
    *MTIMECMP = *MTIME + INTERVAL; // schedule next interrupt (based on timer)
}

void main(void) {
    extern void trap_entry(void);

    asm volatile("csrw mtvec, %0" :: "r"(trap_entry));

    *MTIMECMP = *MTIME + INTERVAL; // schedule interrupt 1 second from now

    asm volatile("csrw mie, %0" :: "r"(0x80UL));
    asm volatile("csrsi mstatus, 0x8");

	uart_puts("Waiting for timer...\n");
	while(1);
}
