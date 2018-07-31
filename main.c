#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "bcm2836.h"
#include "periph.h"

#define PRG_NAME "RPI usermode cool down driver"
#define PG_SIZE 4096

struct bcm_peripheral gpio = {GPIO_BASE};

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

int main()
{
        if(getuid() !=0 && geteuid() != 0) {
                fprintf(stderr, "please run this as root\n");
                exit(EXIT_FAILURE);
        }
        periph_map(&gpio);
        set_cooler();
}


