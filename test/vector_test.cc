#include <stdint.h>
#include <stdio.h>
#include "ts/ink_assert.h"
#include "ts/Vec.h"

static void
test_append()
{
    static const char value[] = "this is a string";
    unsigned int len          = (int)sizeof(value) - 1;

    Vec<char> str;

    str.append(value, 0);
    ink_assert(str.length() == 0);

    str.append(value, len);
    ink_assert(memcmp(&str[0], value, len) == 0);
    ink_assert(str.length() == len);

    str.clear();
    ink_assert(str.length() == 0);

    for (unsigned i = 0; i < 1000; ++i) {
        str.append(value, len);
        ink_assert(memcmp(&str[i * len], value, len) == 0);
    }

    ink_assert(str.length() == 1000 * len);
}

static void
test_basic()
{
    Vec<void *> v, vv, vvv;
    int tt = 99 * 50, t = 0;

    for (size_t i = 0; i < 100; i++)
        v.add((void *)(intptr_t)i);
    for (size_t i = 0; i < 100; i++)
        t += (int)(intptr_t)v.v[i];
    ink_assert(t == tt);

    t = 0;
    for (size_t i = 1; i < 100; i++)
        vv.set_add((void *)(intptr_t)i);
    for (size_t i = 1; i < 100; i++)
        vvv.set_add((void *)(intptr_t)i);
    for (size_t i = 1; i < 100; i++)
        vvv.set_add((void *)(intptr_t)(i * 1000));
    vv.set_union(vvv);
    for (size_t i = 0; i < vv.n; i++)
        if (vv.v[i])
            t += (int)(intptr_t)vv.v[i];
    ink_assert(t == tt + 1000 * tt);

    v.clear();
    v.reserve(1000);
    t = 0;
    for (size_t i = 0; i < 1000; i++)
        v.add((void *)(intptr_t)i);
    for (size_t i = 0; i < 1000; i++)
        t += (int)(intptr_t)v.v[i];
    ink_assert(t == 999 * 500);
    printf("%zu %zu\n", v.n, v.i);

    Intervals in;
    in.insert(1);
    ink_assert(in.n == 2);
    in.insert(2);
    ink_assert(in.n == 2);
    in.insert(6);
    ink_assert(in.n == 4);
    in.insert(7);
    ink_assert(in.n == 4);
    in.insert(9);
    ink_assert(in.n == 6);
    in.insert(4);
    ink_assert(in.n == 8);
    in.insert(5);
    ink_assert(in.n == 6);
    in.insert(3);
    ink_assert(in.n == 4);
    in.insert(8);
    ink_assert(in.n == 2);

    UnionFind uf;
    uf.size(4);
    uf.unify(0, 1);
    uf.unify(2, 3);
    ink_assert(uf.find(2) == uf.find(3));
    ink_assert(uf.find(0) == uf.find(1));
    ink_assert(uf.find(0) != uf.find(3));
    ink_assert(uf.find(1) != uf.find(3));
    ink_assert(uf.find(1) != uf.find(2));
    ink_assert(uf.find(0) != uf.find(2));
    uf.unify(1, 2);
    ink_assert(uf.find(0) == uf.find(3));
    ink_assert(uf.find(1) == uf.find(3));
}

static bool
compare(void *a, void *b)
{
    return a < b;
}

static void
test_sort()
{
    Vec<void *> v;
    for (long i = 1; i <= 1000; ++i)
        v.add(reinterpret_cast<void *>(static_cast<intptr_t>(((i * 149) % 1000) + 1)));
    v.qsort(&compare);
    for (int i = 0; i < 1000; ++i)
        ink_assert(reinterpret_cast<void *>(static_cast<intptr_t>(i + 1)) == v[i]);

    v.clear();
    for (long i = 1; i <= 1000000; ++i) {
        v.add(reinterpret_cast<void *>(static_cast<intptr_t>(((i * 51511) % 1000000) + 1)));
    }
    v.qsort(&compare);

    for (long i = 0; i < 1000000; ++i) {
        ink_assert(reinterpret_cast<void *>(static_cast<intptr_t>(i + 1)) == v[i]);
    }

    v.clear();
    for (long i = 1; i <= 1000000; ++i) {
        // This should be every number 1..500000 twice.
        v.add(reinterpret_cast<void *>(static_cast<intptr_t>(((i * 199999) % 500000) + 1)));
    }
    v.qsort(&compare);

    for (long i = 0; i < 1000000; ++i) {
        ink_assert(reinterpret_cast<void *>(static_cast<intptr_t>((i / 2) + 1)) == v[i]);
    }

    // Very long array, already sorted. This is what broke before.
    v.clear();
    for (long i = 1; i <= 10000000; ++i)
        v.add(reinterpret_cast<void *>(static_cast<intptr_t>(i)));
    v.qsort(&compare);
    for (long i = 0; i < 10000000; ++i)
        ink_assert(reinterpret_cast<void *>(static_cast<intptr_t>(i + 1)) == v[i]);

    // very long, reverse sorted.
    v.clear();
    for (long i = 10000000; i >= 1; --i)
        v.add(reinterpret_cast<void *>(static_cast<intptr_t>(i)));
    v.qsort(&compare);
    for (long i = 0; i < 10000000; ++i)
        ink_assert(reinterpret_cast<void *>(static_cast<intptr_t>(i + 1)) == v[i]);
}

int
main(int /* argc ATS_UNUSED */, char ** /* argv ATS_UNUSED */)
{
    test_append();
    test_basic();
    test_sort();
    printf("test_Vec PASSED\n");
}
