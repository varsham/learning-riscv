#define UART ((volatile unsigned char *) 0x10000000)
#define UART_LSR ((volatile unsigned char *) 0x10000005)

// define a function to print out one character, uses UART
void uart_putc(char c) {
	// trigger UART output by accessing the peripheral address
	*UART = c;
}

void uart_puts(char *s) {
	while (*s) {
		uart_putc(*s++);
	}
}

// create a getc function using the line status register
char uart_getc(void) {
	// spinning wait to wait for bit 0 of the UART LSR to turn high
	while (!(*UART_LSR & 0x01));	
	return *UART_LSR;
}

void main(void) {
	uart_puts("Type in a character: ");
	char c = uart_getc();
	uart_puts("\nYou entered this character: ");
	uart_putc(c);
	uart_putc('\n');
	while(1);
}	
