#ifndef __MALLOC_H__
#define __MALLOC_H__

#include "stm32f4xx_hal.h"

#ifndef NULL
#define NULL 0
#endif

#define SRAMIN 0
#define SRAMCCM 1
#define SRAMEX 2

#define MT_TYPE uint32_t

#define SRAMBANK 3

#define MEM1_BLOCK_SIZE 64
#define MEM1_MAX_SIZE 80 * 1024
#define MEM1_ALLOC_TABLE_SIZE MEM1_MAX_SIZE / MEM1_BLOCK_SIZE

#define MEM2_BLOCK_SIZE 64
#define MEM2_MAX_SIZE 60 * 1024
#define MEM2_ALLOC_TABLE_SIZE MEM2_MAX_SIZE / MEM2_BLOCK_SIZE

#define MEM3_BLOCK_SIZE 64
#define MEM3_MAX_SIZE 28912 * 1024
#define MEM3_ALLOC_TABLE_SIZE MEM3_MAX_SIZE / MEM3_BLOCK_SIZE

struct _m_mallco_dev
{
    void (*init)(uint8_t);
    uint16_t (*perused)(uint8_t);
    uint8_t *membase[SRAMBANK];
    uint32_t *memmap[SRAMBANK];
    uint8_t memrdy[SRAMBANK];
};

extern struct _m_mallco_dev mallco_dev;

void my_mem_set(void *s, uint8_t c, uint32_t count);
void my_mem_copy(void *des, void *src, uint32_t n);
void my_mem_init(uint8_t memx);
uint32_t my_mem_malloc(uint8_t memx, uint32_t size);
uint8_t my_mem_free(uint8_t memx, uint32_t offset);
uint16_t my_mem_perused(uint8_t memx);

void myfree(uint8_t memx, void *ptr);
void *mymalloc(uint8_t memx, uint32_t size);
void *myrealloc(uint8_t memx, void *ptr, uint32_t size);

#endif /* __MALLOC_H__ */
