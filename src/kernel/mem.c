#include "mem.h"

static uint32_t MMIO_BASE;
 
int mmio_init()
{
	int raspi;
    uint32_t reg;
 
    /* read the system register */
#if __aarch64__
    asm volatile ("mrs %x0, midr_el1" : "=r" (reg));
#else
    asm volatile ("mrc p15,0,%0,c0,c0,0" : "=r" (reg));
#endif
 
    /* get the PartNum, detect board and MMIO base address */
    switch ((reg >> 4) & 0xFFF) {
        case 0xB76: raspi = 1; MMIO_BASE = 0x20000000; break;
        case 0xC07: raspi = 2; MMIO_BASE = 0x3F000000; break;
        case 0xD03: raspi = 3; MMIO_BASE = 0x3F000000; break;
        case 0xD08: raspi = 4; MMIO_BASE = 0xFE000000; break;
        default:    raspi = 0; MMIO_BASE = 0x20000000; break;
    }    

	return raspi;
}

void mmio_write(uint32_t reg, uint32_t data) {
	*(volatile uint32_t*)(MMIO_BASE + reg) = data;
}

uint32_t mmio_read(uint32_t reg) {
	return *(volatile uint32_t*)(MMIO_BASE + reg);
}

void kmemcpy(void* dst, const void* src, size_t size) {
	void* const dstEnd = dst + size;
	
	while(dst != dstEnd) {
		*(uint8_t*)dst = *(uint8_t*)src;
		src++;
		dst++;
	}
}
