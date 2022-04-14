#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../mpool.h"
#include "mlist.h"

#define UNUSED(param) (void)param
#define IS_ALIGNED(p) ((uintptr_t)(p) % (MPOOL_ALIGN_SIZE) == 0)

static void mpool_test01(void);
static void mpool_test02(void);
static void mpool_test03(void);

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

    mpool_test01();
    mpool_test02();
    mpool_test03();

    return 0;

/* mlist_t *list; */
/* printf("testing mlist\n"); */
/* for (i = 0; i < 5000; i++) { */
/* list = mlist_create(); */
/* for (j = 0; j < 100000; j++) { */
/* toss = mlist_alloc(&list, sizeof(uint32_t)); */
/* } */
/* if (i % 100 == 0) { */
/* printf("%d\n", i); */
/* } */
/* mlist_free(list); */
/* } */
/* return 0; */
}

static void mpool_test01(void) {
    printf("mpool_test01\n");
    mpool_t *pool;
    pool = mpool_create(0);
    char *p1;
    p1 = mpool_alloc(pool, sizeof(*p1));
    *p1 = 'a';
    assert(*p1 == 'a');
    // assert(IS_ALIGNED(p1));
    mpool_free(pool);
}

static void mpool_test02(void) {
    printf("mpool_test02\n");
    mpool_t *pool;
    pool = mpool_create(0);
    char *p1;
    char *p2;
    char *p3;
    char *p4;
    char *p5;
    p1 = (char *)mpool_alloc(pool, sizeof(*p1));
    p2 = (char *)mpool_alloc(pool, sizeof(*p2));
    p3 = (char *)mpool_alloc(pool, sizeof(*p3));
    p4 = (char *)mpool_alloc(pool, sizeof(*p4));
    p5 = (char *)mpool_alloc(pool, sizeof(*p5));
    *p1 = 'a';
    *p2 = 'b';
    *p3 = 'c';
    *p4 = 'd';
    *p5 = 'e';
    assert(*p1 == 'a');
    assert(*p2 == 'b');
    assert(*p3 == 'c');
    assert(*p4 == 'd');
    assert(*p5 == 'e');
    mpool_free(pool);
}

static void mpool_test03(void) {
    printf("mpool_test03\n");
    mpool_t *pool;
    pool = mpool_create(0);
    const char *s[] = { "abcdef", "0123456789" };
    char *s1;
    char *s2;

    s1 = mpool_alloc(pool, strlen(s[0]) + 1);
    s2 = mpool_alloc(pool, strlen(s[1]) + 1);
    strcpy(s1, s[0]);
    strcpy(s2, s[1]);
    assert(strncmp(s1, s[0], strlen(s1)) == 0);
    assert(strncmp(s2, s[1], strlen(s2)) == 0);
    mpool_free(pool);
}
