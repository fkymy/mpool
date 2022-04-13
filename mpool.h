#ifndef MPOOL_H
#define MPOOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define MPOOL_POOL_SIZ   (64 * 1024)
#define MPOOL_ALIGN_SIZE (8)

#define MPOOL_FREE(p)           \
    do {                        \
        if (p != NULL) {        \
            free(p);            \
            (p) = NULL;         \
        }                       \
    } while (false)             \

extern size_t default_pool_size;

typedef struct subpool_t {
    void *block;
    void *start;
    void *end;
    size_t size;
    uint32_t misses;
    struct subpool_t *next;
} subpool_t;

typedef struct mpool_t {
    subpool_t *pools;
    subpool_t *first;
} mpool_t;

/* Create a memory pool with a given initial size. If init_size is 0,
 * the default_pool_size is used. */
mpool_t *mpool_create (size_t init_size);

/* Returns a pointer to the allocated size bytes from the given pool */
void *mpool_alloc (mpool_t *source_pool, size_t size);

/* Deallocate all memory pools */
void mpool_free (mpool_t *source_pool);

#endif
