#pragma once

#include "ctype.h"

#define close_interrupt __asm__ volatile("cli":::"memory")
#define open_interrupt __asm__ volatile("sti":::"memory")

static inline void io_out8(uint16_t port, uint8_t data) {
    __asm__ volatile("outb %b0, %w1" : : "a"(data), "Nd"(port));
}

static inline uint8_t io_in8(uint16_t port) {
    uint8_t data;
    __asm__ volatile("inb %w1, %b0" : "=a"(data) : "Nd"(port));
    return data;
}

static inline uint16_t io_in16(uint16_t port) {
    uint16_t data;
    __asm__ volatile("inw %w1, %w0" : "=a"(data) : "Nd"(port));
    return data;
}

static inline void io_out16(uint16_t port, uint16_t data) {
    __asm__ volatile("outw %w0, %w1" : : "a"(data), "Nd"(port));
}

static inline void flush_tlb(uint64_t addr) {
    __asm__ volatile("invlpg (%0)"::"r" (addr) : "memory");
}

static inline void set_cr3(uint64_t cr0) {
    __asm__ volatile("mov %0, %%cr0" : : "r"(cr0));
}

static inline uint64_t get_cr3(void) {
    uint64_t cr0;
    __asm__ volatile("mov %%cr3, %0" : "=r"(cr0));
    return cr0;
}

static inline void mmio_write32(uint32_t * addr, uint32_t data) {
    *(volatile uint32_t *) addr = data;
}

static inline uint32_t mmio_read32(void* addr) {
    return *(volatile uint32_t *) addr;
}

static inline uint64_t rdmsr(uint32_t msr) {
    uint32_t eax, edx;
    __asm__ volatile("rdmsr" : "=a"(eax), "=d"(edx) : "c"(msr));
    return ((uint64_t) edx << 32) | eax;
}

static inline void wrmsr(uint32_t msr, uint64_t value) {
    uint32_t eax = (uint32_t)value;
    uint32_t edx = value >> 32;
    __asm__ volatile("wrmsr" : : "c"(msr), "a"(eax), "d"(edx));
}
