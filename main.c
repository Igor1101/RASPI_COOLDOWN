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

/* config file */
#define CONF "config"

char therm_path[1024];
uint32_t min_temperature;
uint32_t hysteresis;

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

void set_config_info(void)
{
        FILE *conf = fopen(CONF, "r");
        if(conf == NULL) {
                strerror(errno);
                perror(PRG_NAME);
                exit(EXIT_FAILURE);
        }
        fscanf(conf, "%s%u%u", therm_path, &min_temperature, &hysteresis);
        printf("therm_path %s min %d hyst %d\n", 
                        therm_path, 
                        min_temperature, 
                        hysteresis);
        fclose(conf);
}

int main()
{
        if(getuid() !=0 && geteuid() != 0) {
                fprintf(stderr, "please run this as root\n");
                exit(EXIT_FAILURE);
        }
        periph_map(&gpio);
        init_cooler();
        set_cooler();
        clr_cooler();
        set_config_info();
}


