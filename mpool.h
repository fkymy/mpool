#ifndef MPOOL_H
#define MPOOL_H

#include <stddef.h>
#include <stdint.h>

extern size_t default_pool_size;

struct subpool {
    void *block;
    void *start;
    void *end;
    size_t size;
    uint32_t misses;
    struct subpool *next;
};

struct mpool {
    struct subpool *pools;
    struct subpool *first;
};

struct mpool *mpool_create (size_t init_size);

void *mpool_alloc (struct mpool *source_pool, size_t size);

void mpool_free (struct mpool *source_pool);

#endif
