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
#include "periph.h"

#if defined RPI_V1 || defined RPI_V2 || defined RPI_V3
#include "bcm2836.h"
#endif /* PLATFORM */

/* config file */
#define DEFAULT_CONF "config"
#define DEFAULT_CONF_2 "/etc/cooldown/config"

char therm_path[1024];
char conf_path[256];
int therm_fd;
uint32_t min_temperature;
uint32_t hysteresis;

struct peripheral gpio = {GPIO_BASE};



void set_config_info(void)
{
        /* if console given: */
        FILE *conf = fopen(conf_path, "r");
        /* try opening one file */
        if(conf == NULL) {
                conf = fopen(DEFAULT_CONF, "r");
        }
        /* another (if driver is already installed) */
        if(conf == NULL) {
                conf = fopen(DEFAULT_CONF_2, "r");
        }
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

void open_temp(void)
{
        therm_fd = open(therm_path, O_RDONLY);
        if(therm_fd < 0 ) {
                strerror(errno);
                perror(PRG_NAME);
                exit(EXIT_FAILURE);
        }
}
int reopen_temp(void)
{
        if(close(therm_fd)) {
                strerror(errno);
                perror(PRG_NAME);
                return(EXIT_FAILURE);
        }
        open_temp();
        return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
        if(getuid() !=0 && geteuid() != 0) {
                fprintf(stderr, "please run this as root\n");
                exit(EXIT_FAILURE);
        }
        periph_map(&gpio);
        init_cooler();
        /* let user know, that driver is started */
        set_cooler();
        sleep(2);
        clr_cooler();

        set_config_info();
        open_temp();
        /* start therm verification */

        static char temp[10];
        static uint32_t current_temp;
        while(1) {
                reopen_temp();
                ssize_t size = 
                        read(therm_fd, temp,/* amount of digits */ 7);
                temp[size] = '\0';
                sscanf(temp, "%u", &current_temp);
                printf("current T = %d\n", current_temp);
                if(current_temp > min_temperature)
                        set_cooler();
                if(current_temp < min_temperature - hysteresis)
                        clr_cooler();
                sleep(1);
        }
}


