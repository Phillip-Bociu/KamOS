#include "uart.h"
#include "mem.h"
#include "time.h"

volatile unsigned int  __attribute__((aligned(16))) mbox[9] = {
    9*4, 0, 0x38002, 12, 8, 2, 3000000, 0 ,0
};

void uart_init() {

	int raspi = mmio_init();

    mmio_write(UART0_CR, 0x00000000);
    mmio_write(GPPUD, 0x00000000);
    delay(150);

    mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);

    mmio_write(GPPUDCLK0, 0x00000000);
    mmio_write(UART0_ICR, 0x7FF);
	if (raspi >= 3) {
		// UART_CLOCK = 30000000;
		unsigned int r = (((unsigned int)(&mbox) & ~0xF) | 8);
		// wait until we can talk to the VC
		while ( mmio_read(MBOX_STATUS) & 0x80000000 ) { }
		// send our message to property channel and wait for the response
		mmio_write(MBOX_WRITE, r);
		while ( (mmio_read(MBOX_STATUS) & 0x40000000) || mmio_read(MBOX_READ) != r ) { }
	}

    mmio_write(UART0_IBRD, 1);
    mmio_write(UART0_FBRD, 40);

    mmio_write(UART0_LCRH, 
			(1 << 4) | (1 << 5) | (1 << 6));

    mmio_write(UART0_IMSC, 
			(1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

    mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}

void uart_putc(char c) {
	while(mmio_read(UART0_FR) & (1 << 5)) {}
	mmio_write(UART0_DR, c);
}

char uart_getc() {
	while(mmio_read(UART0_FR) & (1 << 4)) {}
	return mmio_read(UART0_DR);
}

void uart_puts(const char* s) {
	for(; *s != '\0'; s++) {
		uart_putc(*s);
	}
}

void muart_init() {
	// TODO: this is written for raspi3, handle other boards using raspi
	int raspi = mmio_init();
	(void) raspi;

	register unsigned int r;

	mmio_write(AUX_ENABLE, mmio_read(AUX_ENABLE) | 1); // enable UART1
	mmio_write(UART1_CNTL, 0); 
	mmio_write(UART1_LCR, 3); // 8 bit mode
	mmio_write(UART1_MCR, 0);
	mmio_write(UART1_IER, 0);
	mmio_write(UART1_IIR, 0xC6); // disable interrupts
	mmio_write(UART1_BAUD, 270); // 115200 baud

	// map UART1 to GPIO pins
	r = mmio_read(GPFSEL1);
	r = r & ~((7 << 12) | (7 << 15)); // gpio14 and gpio15
	r = r | (2 << 12) | (2 << 15);
	mmio_write(GPFSEL1, r);
	mmio_write(GPPUD, 0);
	delay(150);
	mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
	delay(150);
	mmio_write(GPPUDCLK0, 0); // flush GPIO setup
	mmio_write(UART1_CNTL, 3); // enable TX, RX
}

void muart_putc(char c) {
	while(!(mmio_read(UART1_LSR) & 0x20)) {}
	mmio_write(UART1_IO, c);
}

char muart_getc() {
	char r;
	while(!(mmio_read(UART1_LSR) & 0x01)) {}
	r = (char)mmio_read(UART1_IO);
	return r;
}

void muart_puts(const char* str) {
	for(; *str != '\0'; str++) {
		// LF => CRLF
		if(*str == '\n') {
			muart_putc('\r');
		}
		muart_putc(*str);
	}
}

