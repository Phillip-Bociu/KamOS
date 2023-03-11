#include <stddef.h>
#include <stdint.h>
#include "uart.h"
#include "mem.h"
#include "atags.h"

//Provide __stack_chk_guard with a random value in c file, avoid using regular values like all zero's or FF's because the stack can easily get these values during any memory operation. Wiki on providing magic number implementation. This __stack_chk_guard will be placed at the top and bottom of the stack, which will be checked during every stack access. Any change in the value implies a corrupted stack and returns with error providing the stack protection.

unsigned long __stack_chk_guard;
void __stack_chk_guard_setup(void)
{
     __stack_chk_guard = 0xA5A5A5A5;//provide some magic numbers
}

void __stack_chk_fail(void)                         
{
 /* Error message */                                 
}// will be called when guard variable is corrupted 


void utoa(char* buffer, size_t buffCap, uint32_t num) {
	uint8_t index = 0;
	if(buffCap < 2) {
		return;
	}
	
	do {
		buffer[index] = '0' + (num % 10);
		num /= 10;
		index++;
	} while(num != 0 && index != buffCap - 1);

	for(uint8_t aux = 0; aux != index / 2; aux++) {
		char t = buffer[aux];
		buffer[aux] = buffer[index - aux];
		buffer[index - aux] = t;
	}
	buffer[index] = '\0';
}

void print_num(int32_t num) {
	char res[64] = {0};
	int i = 0;
	do {
		res[i] = ('0' + (num % 10));
		i++;
		num = num / 10;
	} while(num != 0);
	i--;
	while(i >= 0) {
		muart_putc(res[i]);
		i--;
	}
}

void kernel_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3) {
	int raspi = mmio_init();

	muart_init();
	muart_puts("Raspberry Pi version: ");
	muart_putc('0' + raspi);
	muart_putc('\n');

	while(1) {
		char c = muart_getc();

		if(c == '\r') {
			muart_puts("\n");
		} else {
			muart_putc(c);
		}
	}
}

