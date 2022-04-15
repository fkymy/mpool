#include <stdio.h>
#include <stdlib.h>
#include "mpool.h"

size_t default_pool_size = 256;

/*
 * Used internally
 */
static subpool_t *create_subpool_node (const size_t size);
static inline size_t aligned(size_t size);

/*
 * Create memory pool object
 */
mpool_t *mpool_create (size_t init_size) {
    if (init_size == 0) {
        init_size = default_pool_size;
    } else {
        init_size = aligned(init_size);
    }

    mpool_t *new_pool = (mpool_t *)malloc(sizeof(mpool_t));
    if (new_pool == NULL)
        return NULL;

    new_pool->pools = (subpool_t *)create_subpool_node(init_size);
    if (new_pool->pools == NULL)
        return NULL;

    new_pool->first = new_pool->pools;
    return new_pool;
}

/*
 * Returns a pointer to the allocated size bytes from the given pool
 */
void *mpool_alloc (mpool_t *source_pool, size_t size) {
    void *chunk = NULL;
    subpool_t *curr, *last;

    size = aligned(size);
    curr = source_pool->first;
    if (curr->misses > MPOOL_MISS_LIMIT) {
        // this subpool doesn't seem to be any good anymore
        source_pool->first = source_pool->first->next;
    }

    while (curr != NULL) {
        if (size <= (size_t)(curr->free_end - curr->free_start)) {
            // chop off a chunk of memory and return it
            chunk = curr->free_start;
            curr->free_start += size;
            break ;
        }
        // current subpool is too small
        curr->misses++;
        last = curr;
        curr = curr->next;
    }

    if (chunk == NULL) {
        // none of the existing subpools had enough room, make a new one
        size_t new_size = last->size * 2;
        if (new_size <= size) {
            new_size = size * 2;
        }
        last->next = create_subpool_node(new_size);
        curr = last->next;
        if (curr == NULL)
            return NULL;

        chunk = curr->free_start;
        curr->free_start += size;
    }

    return chunk;
}

/*
 * Deallocate all memory pools
 */
void mpool_free (mpool_t *source_pool) {
    subpool_t *curr, *last;

    curr = source_pool->pools;
    while (curr != NULL) {
        MPOOL_FREE(curr->mem_block);
        last = curr;
        curr = curr->next;
        free(last);
    }
    free(source_pool);
}

/*
 * Used internally to allocate more pool space
 */
subpool_t *create_subpool_node (const size_t size) {
    subpool_t *new_subpool;

    new_subpool = (subpool_t *)malloc(sizeof(subpool_t));
    if (new_subpool == NULL)
        return NULL;

    new_subpool->mem_block = (void *)malloc(size);
    if (new_subpool->mem_block == NULL) {
        free(new_subpool);
        return NULL;
    }

    new_subpool->free_start = new_subpool->mem_block;
    new_subpool->free_end = new_subpool->mem_block + size;
    new_subpool->size = size;
    new_subpool->misses = 0;
    new_subpool->next = NULL;

    return new_subpool;
}

/**
 * Used internally to align memory block boundary
 */
inline size_t aligned(size_t size) {
    return (size + (MPOOL_ALIGNMENT - 1)) & ~(MPOOL_ALIGNMENT - 1);
}
