// create a symbolic alias for the UART peripheral register address/hardware address
#define UART ((volatile unsigned char *)0x10000000)
// create a symbolic alias for the UART_LSR (line status register)
#define UART_LSR ((volatile unsigned char *) 0x10000005) // 5 byte offset
#define MAXLEN 256

// function to print one char using UART
void uart_putc(char c) {
    *UART = c;        
}

// function to print a string using UART
void uart_puts(char *s) {
    while (*s) {
        uart_putc(*s++);
    }
} 

// function to get one character using UART_LSR
char uart_lsr_getc(void) {
    while (!(*UART_LSR & 0x01)); // spin wait
    return *UART; // return character received   
}

// function to get a string using UART_LSR
// stops reading at the newline
void uart_lsr_gets(char *buf, int max) {
    // create a buffer with the max length
    int bufIndex = 0;
    char c = uart_lsr_getc();
    while (bufIndex < max - 1) {
        uart_putc(c);
        if (c == '\n' || c == '\r') break;
        buf[bufIndex++] = c;
        c = uart_lsr_getc();
    }   
    buf[bufIndex] = '\0'; // null terminate so uart_puts knows when to stop 
}

void main(void) {
   char buf[MAXLEN];
   uart_puts("Enter a string: ");
   uart_lsr_gets(buf, MAXLEN);
   uart_puts("\nYou entered: ");
   uart_puts(buf);
   uart_putc('\n');
   while (1);}
