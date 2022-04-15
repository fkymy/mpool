#include <stdio.h>
#include <stdlib.h>
#ifdef MPOOL_THR_SAFE
# include <pthread.h>
#endif

#include "mpool.h"

#define UNUSED(param) (void)param

#ifdef MPOOL_THR_SAFE
static void *thread_routine(void *arg);
#endif

int main(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);

    mpool_t *pool;
    uint32_t i, j, *toss;

    printf("testing mpool\n");
    for (i = 0; i < 1000; i++) {
        pool = mpool_create(0);
        for (j = 0; j < 100000; j++) {
            toss = mpool_alloc(pool, sizeof(uint32_t));
        }
        if (i % 100 == 0) {
            printf("%d\n", i);
        }
        mpool_free(pool);
    }

#ifdef MPOOL_THR_SAFE
    pthread_t threads[10];
    pool = mpool_create(8);

    for (i = 0; i < 10; i++)
        pthread_create(&threads[i], NULL, thread_routine, (void *)pool);
    for (i = 0; i < 10; i++)
        pthread_join(threads[i], NULL);

    mpool_free(pool);
#endif

    return 0;
}

#ifdef MPOOL_THR_SAFE
void *thread_routine(void *arg) {
    mpool_t *pool = (mpool_t *)arg;
    uint32_t i, *toss;

    for (i = 0; i < 1000; i++) {
        toss = mpool_alloc(pool, sizeof(uint32_t));
        if (i % 100 == 0) {
            printf("%d\n", i);
        }
    }
    return NULL;
}
#endif
