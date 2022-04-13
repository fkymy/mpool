#include <stdlib.h>
#include <stdio.h>

#include "mpool.h"

size_t default_pool_size = 256;
uint32_t miss_limit = 8;

static struct subpool *create_subpool_node (size_t size);

struct mpool *mpool_create (size_t init_size) {
    if (init_size == 0) {
        init_size = default_pool_size;
    }

    struct mpool *new_pool = malloc(sizeof(struct mpool));
    if (new_pool == NULL)
        return NULL;

    new_pool->pools = create_subpool_node(init_size);
    new_pool->first = new_pool->pools;

    if (new_pool->first == NULL)
        return NULL;

    return new_pool;
}

void *mpool_alloc (struct mpool *source_pool, size_t size) {
    struct subpool *curr, *last;
    void *chunk = NULL;

    curr = source_pool->first;
    if (curr->misses > miss_limit) {
        source_pool->first = source_pool->first->next;
    }

    do {
        if (size <= (size_t)(curr->end - curr->start)) {
            chunk = curr->start;
            curr->start += size;
            curr->misses = 0;
        } else {
            curr->misses++;
        }

        last = curr;
        curr = curr->next;
    } while (curr != NULL && chunk == NULL);

    if (chunk == NULL) {
        size_t new_size = last->size * 2;
        if (new_size <= size) {
            new_size = size * 2;
        }
        last->next = create_subpool_node(new_size);
        curr = last->next;
        if (curr == NULL)
            return NULL;

        chunk = curr->start;
        curr->start += size;
    }

    return chunk;
}

void mpool_free (struct mpool *source_pool) {
    struct subpool *curr, *last;

    curr = source_pool->pools;
    while (curr != NULL) {
        free(curr->block);
        last = curr;
        curr = curr->next;
        free(last);
    }
    free(source_pool);
}

struct subpool *create_subpool_node (size_t size) {
    struct subpool *new_subpool;

    new_subpool = malloc(sizeof(struct subpool));
    if (new_subpool == NULL)
        return NULL;

    new_subpool->block = malloc(size);
    if (new_subpool->block == NULL) {
        free(new_subpool);
        return NULL;
    }

    new_subpool->start = new_subpool->block;
    new_subpool->end = new_subpool->block + size;
    new_subpool->size = size;
    new_subpool->misses = 0;
    new_subpool->next = NULL;

    return new_subpool;
}
