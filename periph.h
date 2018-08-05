#ifndef PERIPH_H
#define PERIPH_H
#include <stdint.h>

#define PG_SIZE 4096

struct peripheral {
    	uintptr_t addr_p;
    	int mem_fd;
    	uint32_t*map;
};


void periph_map(struct peripheral *p);

void periph_unmap(struct peripheral *p);

#endif /* PERIPH_H */
