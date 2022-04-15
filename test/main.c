#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "../mpool.h"
#include "mlist.h"

#define UNUSED(param) (void)param
#define CTOD(c) ((c) - '0')
#define DTOC(d) ((d) + '0')

static bool isaligned(void *p);
static void mpool_test01(void);
static void mpool_test02(void);
static void mpool_test03(void);
static void mpool_test04(void);
static void mpool_test05(void);

int main(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);

    CU_pSuite suite_mpool;
    CU_initialize_registry();
    suite_mpool = CU_add_suite("mpool", NULL, NULL);
    CU_add_test(suite_mpool, "mpool_test01", mpool_test01);
    CU_add_test(suite_mpool, "mpool_test02", mpool_test02);
    CU_add_test(suite_mpool, "mpool_test03", mpool_test03);
    CU_add_test(suite_mpool, "mpool_test04", mpool_test04);
    CU_add_test(suite_mpool, "mpool_test05", mpool_test05);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return EXIT_SUCCESS;
}

static bool isaligned(void *p) {
    return (uintptr_t)p % MPOOL_ALIGNMENT == 0;
}

static void mpool_test01(void) {
    printf("mpool_test01\n");
    mpool_t *pool;
    char *toss;

    pool = mpool_create(0);
    for (int i = 0; i < 1000; i++) {
        toss = (char *)mpool_alloc(pool, sizeof(*toss));
        *toss = DTOC(i % 10);
        CU_ASSERT(*toss == DTOC(i % 10));
        CU_ASSERT(isaligned(toss));
    }
    mpool_free(pool);
}

static void mpool_test02(void) {
    printf("mpool_test02\n");
    mpool_t *pool;
    uint32_t i, j, *toss;

    for (i = 0; i < 5000; i++) {
        pool = mpool_create(0);
        for (j = 0; j < 100000; j++) {
            toss = mpool_alloc(pool, sizeof(uint32_t));
            CU_ASSERT(isaligned(toss));
        }
        if (i % 100 == 0) {
            // printf("%d\n", i);
        }
        mpool_free(pool);
    }
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
    CU_ASSERT(strncmp(s1, s[0], strlen(s1)) == 0);
    CU_ASSERT(strncmp(s2, s[1], strlen(s2)) == 0);
    mpool_free(pool);
}

static void mpool_test04(void) {
    printf("mpool_test04\n");
    mpool_t *pool;
    pool = mpool_create(16);
    bool               *b;
    short              *s;
    char               *c;
    unsigned char      *uc;
    int                *n;
    unsigned int       *un;
    long               *l;
    unsigned long      *ul;
    long long          *ll;
    unsigned long long *ull;
    float              *f;
    double             *d;
    long double        *ld;
    time_t             *t;
    off_t              *ot;
    intptr_t           *ipt;
    size_t             *siz;
    ptrdiff_t          *pdt;

    b   = mpool_alloc(pool, sizeof(*b));
    s   = mpool_alloc(pool, sizeof(*s));
    c   = mpool_alloc(pool, sizeof(*c));
    uc  = mpool_alloc(pool, sizeof(*uc));
    n   = mpool_alloc(pool, sizeof(*n));
    un  = mpool_alloc(pool, sizeof(*un));
    l   = mpool_alloc(pool, sizeof(*l));
    ul  = mpool_alloc(pool, sizeof(*ul));
    ll  = mpool_alloc(pool, sizeof(*ll));
    ull = mpool_alloc(pool, sizeof(*ull));
    f   = mpool_alloc(pool, sizeof(*f));
    d   = mpool_alloc(pool, sizeof(*d));
    ld  = mpool_alloc(pool, sizeof(*ld));
    t   = mpool_alloc(pool, sizeof(*t));
    ot  = mpool_alloc(pool, sizeof(*ot));
    ipt = mpool_alloc(pool, sizeof(*ipt));
    siz = mpool_alloc(pool, sizeof(*siz));
    pdt = mpool_alloc(pool, sizeof(*pdt));
    *b   = true;
    *s   = 2;
    *c   = 'a';
    *uc  = 'b';
    *n   = 5;
    *un  = 255;
    *l   = 550;
    *ul  = 333;
    *ll  = 950;
    *ull = 111;
    *f   = 113.5;
    *d   = 50.8;
    *ld  = 115.3;
    *t   = 123;
    *ot  = 22;
    *ipt = 33;
    *siz = 55;
    *pdt = 150;
    CU_ASSERT(*b   == true);
    CU_ASSERT(*s   == 2);
    CU_ASSERT(*c   == 'a');
    CU_ASSERT(*uc  == 'b');
    CU_ASSERT(*n   == 5);
    CU_ASSERT(*un  == 255);
    CU_ASSERT(*l   == 550);
    CU_ASSERT(*ul  == 333);
    CU_ASSERT(*ll  == 950);
    CU_ASSERT(*ull == 111);
    CU_ASSERT(*f   == 113.5);
    CU_ASSERT(*d   == 50.8);
    CU_ASSERT(*ld  == 115.3);
    CU_ASSERT(*t   == 123);
    CU_ASSERT(*ot  == 22);
    CU_ASSERT(*ipt == 33);
    CU_ASSERT(*siz == 55);
    CU_ASSERT(*pdt == 150);

    CU_ASSERT(isaligned(b));
    CU_ASSERT(isaligned(s));
    CU_ASSERT(isaligned(c));
    CU_ASSERT(isaligned(uc));
    CU_ASSERT(isaligned(n));
    CU_ASSERT(isaligned(un));
    CU_ASSERT(isaligned(l));
    CU_ASSERT(isaligned(ul));
    CU_ASSERT(isaligned(ll));
    CU_ASSERT(isaligned(ull));
    CU_ASSERT(isaligned(f));
    CU_ASSERT(isaligned(d));
    CU_ASSERT(isaligned(ld));
    CU_ASSERT(isaligned(t));
    CU_ASSERT(isaligned(ot));
    CU_ASSERT(isaligned(ipt));
    CU_ASSERT(isaligned(siz));
    CU_ASSERT(isaligned(pdt));
}

static void mpool_test05(void) {
    printf("mpool_test05\n");
    mpool_t *pool;
    pool = mpool_create(10);

    struct test_s {
        int  n;
        char c;
    } test_s;

    struct test_s *test;
    int *n;
    test = mpool_alloc(pool, sizeof(*test));
    n = mpool_alloc(pool, sizeof(*n));

    test->n = 5;
    test->c = 'a';
    *n = 10;

    CU_ASSERT(test->n == 5);
    CU_ASSERT(test->c == 'a');
    CU_ASSERT(*n == 10);

    CU_ASSERT(isaligned(test));
    CU_ASSERT(isaligned(n));

    mpool_free(pool);
}
