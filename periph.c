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

void periph_map(struct peripheral *p)
{
        p -> mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
        if(p -> mem_fd < 0) {
                strerror(errno);
                perror(PRG_NAME);
                exit(EXIT_FAILURE);
        }
        p -> map = (uint32_t*)mmap(
                        NULL,
                        PG_SIZE,
                        (PROT_READ | PROT_WRITE),
                        MAP_SHARED,
                        p -> mem_fd,
                        p -> addr_p
                        );
        if(p -> map == MAP_FAILED) {
                strerror(errno);
                perror(PRG_NAME);
                exit(EXIT_FAILURE);
        }

}

void periph_unmap(struct peripheral *p)
{
        munmap(p -> map, PG_SIZE);
        close(p -> mem_fd);
}
