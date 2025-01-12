#pragma once

#define KERNEL_NAME "CP_Kernel-x86_64-0.0.1"
#define cpu_hlt while(1) __asm__("hlt")
#define UNUSED(expr) do { (void)(expr); } while (0)

#include "ctype.h"

int memcmp(const void *a_, const void *b_, size_t size);

void *memcpy(void *s, const void *ct, size_t n);

void *memset(void *dst, int val, size_t size);

size_t strlen(const char *str);

char *strcat(char *dest, const char *src);
