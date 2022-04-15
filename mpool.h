#ifndef MPOOL_H
#define MPOOL_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef MPOOL_THR_SAFE
# include <pthread.h>
#endif

#define MPOOL_ALIGNMENT (sizeof(uintptr_t))
#define MPOOL_MISS_LIMIT (8)

extern size_t default_pool_size;

typedef struct subpool_t {
    void *mem_block;    // memory block for this subpool
    void *free_start;   // start of free segment
    void *free_end;     // end of free segment
    size_t size;        // total size of the block
    uint32_t misses;    // allocation misses for this subpool
    struct subpool_t *next; // next subpool in this pool
} subpool_t;

typedef struct mpool_t {
    subpool_t *pools;   // first element in linked list
    subpool_t *first;   // first good subpool in list
#ifdef MPOOL_THR_SAFE
    pthread_mutex_t lock;
#endif
} mpool_t;

/* Create a memory pool with a given initial size. If init_size is 0,
 * the default_pool_size is used. */
mpool_t *mpool_create (size_t init_size);

/* Returns a pointer to the allocated size bytes from the given pool */
void *mpool_alloc (mpool_t *source_pool, size_t size);

/* Deallocate all memory pools */
void mpool_free (mpool_t *source_pool);

#endif
