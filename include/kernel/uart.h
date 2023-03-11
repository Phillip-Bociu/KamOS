#pragma once

enum {

    // The GPIO registers base address.
    GPIO_BASE = 0x200000,

	GPFSEL0		 = (GPIO_BASE + 0x0),
	GPFSEL1		 = (GPIO_BASE + 0x4),
	GPFSEL2		 = (GPIO_BASE + 0x8),
	GPFSEL3		 = (GPIO_BASE + 0xC),
	GPFSEL4		 = (GPIO_BASE + 0x10),
	GPFSEL5		 = (GPIO_BASE + 0x14),
	GPSET0		 = (GPIO_BASE + 0x1C),
	GPSET1		 = (GPIO_BASE + 0x20),
	GPCLR0		 = (GPIO_BASE + 0x28),
	GPLEV0		 = (GPIO_BASE + 0x34),
	GPLEV1		 = (GPIO_BASE + 0x38),
	GPEDS0		 = (GPIO_BASE + 0x40),
	GPEDS1       = (GPIO_BASE + 0x44),
	GPHEN0       = (GPIO_BASE + 0x64),
	GPHEN1       = (GPIO_BASE + 0x68),
    GPPUD        = (GPIO_BASE + 0x94),
    GPPUDCLK0    = (GPIO_BASE + 0x98),
    GPPUDCLK1    = (GPIO_BASE + 0x9C),

    // The base address for UART (UART0)
    UART0_BASE = (GPIO_BASE + 0x100),

    UART0_DR     = (UART0_BASE + 0x00),
    UART0_RSRECR = (UART0_BASE + 0x04),
    UART0_FR     = (UART0_BASE + 0x18),
    UART0_ILPR   = (UART0_BASE + 0x20),
    UART0_IBRD   = (UART0_BASE + 0x24),
    UART0_FBRD   = (UART0_BASE + 0x28),
    UART0_LCRH   = (UART0_BASE + 0x2C),
    UART0_CR     = (UART0_BASE + 0x30),
    UART0_IFLS   = (UART0_BASE + 0x34),
    UART0_IMSC   = (UART0_BASE + 0x38),
    UART0_RIS    = (UART0_BASE + 0x3C),
    UART0_MIS    = (UART0_BASE + 0x40),
    UART0_ICR    = (UART0_BASE + 0x44),
    UART0_DMACR  = (UART0_BASE + 0x48),
    UART0_ITCR   = (UART0_BASE + 0x80),
    UART0_ITIP   = (UART0_BASE + 0x84),
    UART0_ITOP   = (UART0_BASE + 0x88),
    UART0_TDR    = (UART0_BASE + 0x8C),

	// Auxiliary peripherals base
	AUX_BASE     = 0x00215000,
	AUX_ENABLE   = (AUX_BASE  + 0x4),
	
	// Auxiliary mini UART addresses (UART1)

	UART1_IO     = (AUX_BASE + 0x40),
	UART1_IER    = (AUX_BASE + 0x44),
	UART1_IIR    = (AUX_BASE + 0x48),
	UART1_LCR    = (AUX_BASE + 0x4C),
	UART1_MCR    = (AUX_BASE + 0x50),
	UART1_LSR    = (AUX_BASE + 0x54),
	UART1_MSR    = (AUX_BASE + 0x58),
	UART1_SCRATCH= (AUX_BASE + 0x5C),
	UART1_CNTL   = (AUX_BASE + 0x60),
	UART1_STAT   = (AUX_BASE + 0x64),
	UART1_BAUD   = (AUX_BASE + 0x68),

    // The offsets for Mailbox registers
    MBOX_BASE    = 0xB880,
    MBOX_READ    = (MBOX_BASE + 0x00),
    MBOX_STATUS  = (MBOX_BASE + 0x18),
    MBOX_WRITE   = (MBOX_BASE + 0x20)
};

void muart_init();
void muart_putc(char c);
char muart_getc();
void muart_puts(const char* str);

void uart_init();
void uart_putc(char c);
char uart_getc();
void uart_puts(const char* str);

