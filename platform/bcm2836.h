/*
 * BSD 3-Clause License
 * Copyright (c) 2018, Igor Muravyov
 * All rights reserved.
 */


#ifndef BCM2836_H
#define BCM2836_H
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "periph.h"


#ifdef RPI_V1
#define BCM2708_PERI_BASE       0x20000000
#elif defined RPI_V2 || defined RPI_V3
#define BCM2708_PERI_BASE       0x3F000000
#endif /* RPI_VERSION */


#define GPIO_BASE               (BCM2708_PERI_BASE + 0x200000)	
 
#define GPIO_VIRT_BASE (void*)(gpio.map)
#define BLOCK_SIZE 		(4*1024)
 
#define      GPFSEL0                   *(uint32_t*)(GPIO_VIRT_BASE + 0x0000)
#define      GPFSEL1                   *(uint32_t*)(GPIO_VIRT_BASE + 0x0004)
#define      GPFSEL2                   *(uint32_t*)(GPIO_VIRT_BASE + 0x0008)
#define      GPFSEL3                   *(uint32_t*)(GPIO_VIRT_BASE + 0x000C)
#define      GPFSEL4                   *(uint32_t*)(GPIO_VIRT_BASE + 0x0010)
#define      GPFSEL5                   *(uint32_t*)(GPIO_VIRT_BASE + 0x0014)
#define      GPSET0                    *(uint32_t*)(GPIO_VIRT_BASE + 0x001C)
#define      GPSET1                    *(uint32_t*)(GPIO_VIRT_BASE + 0x0020)
#define      GPCLR0                    *(uint32_t*)(GPIO_VIRT_BASE + 0x0028)
#define      GPCLR1                    *(uint32_t*)(GPIO_VIRT_BASE + 0x002C)
#define      GPLEV0                    *(uint32_t*)(GPIO_VIRT_BASE + 0x0034)
#define      GPLEV1                    *(uint32_t*)(GPIO_VIRT_BASE + 0x0038)
#define      GPEDS0                    *(uint32_t*)(GPIO_VIRT_BASE + 0x0040)
#define      GPEDS1                    *(uint32_t*)(GPIO_VIRT_BASE + 0x0044)
#define      GPREN0                    *(uint32_t*)(GPIO_VIRT_BASE + 0x004C)
#define      GPREN1                    *(uint32_t*)(GPIO_VIRT_BASE + 0x0050)
#define      GPFEN0                    *(uint32_t*)(GPIO_VIRT_BASE + 0x0058)
#define      GPFEN1                    *(uint32_t*)(GPIO_VIRT_BASE + 0x005C)

extern struct peripheral gpio;

inline void init_cooler(void)
{
        /* GPIO 17 as output */
        GPFSEL1 |= (0b001)<<21;
        GPFSEL1 &= ~((0b110)<<21);
}

inline void set_cooler(void)
{
        GPSET0 = 1<<17;
}

inline void clr_cooler(void)
{
        GPCLR0 = 1<<17;
}

#endif /* BCM2836_H */
