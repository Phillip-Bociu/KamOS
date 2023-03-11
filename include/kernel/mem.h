#pragma once
#include <stdint.h>
#include <stddef.h>

// Mailbox I/O
int mmio_init();
void mmio_write(uint32_t address, uint32_t data);
uint32_t mmio_read(uint32_t address);

void kmemcpy(void* dst, const void* src, size_t size);
