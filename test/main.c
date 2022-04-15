#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

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

    mpool_test01();
    mpool_test02();
    mpool_test03();
    mpool_test04();
    mpool_test05();

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
        assert(*toss == DTOC(i % 10));
        assert(isaligned(toss));
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
            assert(isaligned(toss));
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
    assert(strncmp(s1, s[0], strlen(s1)) == 0);
    assert(strncmp(s2, s[1], strlen(s2)) == 0);
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
    assert(*b   == true);
    assert(*s   == 2);
    assert(*c   == 'a');
    assert(*uc  == 'b');
    assert(*n   == 5);
    assert(*un  == 255);
    assert(*l   == 550);
    assert(*ul  == 333);
    assert(*ll  == 950);
    assert(*ull == 111);
    assert(*f   == 113.5);
    assert(*d   == 50.8);
    assert(*ld  == 115.3);
    assert(*t   == 123);
    assert(*ot  == 22);
    assert(*ipt == 33);
    assert(*siz == 55);
    assert(*pdt == 150);

    assert(isaligned(b));
    assert(isaligned(s));
    assert(isaligned(c));
    assert(isaligned(uc));
    assert(isaligned(n));
    assert(isaligned(un));
    assert(isaligned(l));
    assert(isaligned(ul));
    assert(isaligned(ll));
    assert(isaligned(ull));
    assert(isaligned(f));
    assert(isaligned(d));
    assert(isaligned(ld));
    assert(isaligned(t));
    assert(isaligned(ot));
    assert(isaligned(ipt));
    assert(isaligned(siz));
    assert(isaligned(pdt));
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

    assert(test->n == 5);
    assert(test->c == 'a');
    assert(*n == 10);

    assert(isaligned(test));
    assert(isaligned(n));

    mpool_free(pool);
}
