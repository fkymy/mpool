#include <stdio.h>
#include <stdlib.h>
#include "mpool.h"

#define UNUSED(para) (void)para

int main(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);

    mpool_t *pool;
    uint32_t i, j, *toss;

    printf("testing mpool\n");
    for (i = 0; i < 5000; i++) {
        pool = mpool_create(0);
        for (j = 0; j < 100000; j++) {
            toss = mpool_alloc(pool, sizeof(uint32_t));
        }
        if (i % 100 == 0) {
            printf("%d\n", i);
        }
        mpool_free(pool);
    }

    return 0;
}
