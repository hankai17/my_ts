#include <stdlib.h>
#include <string.h>
#include "ts/ink_thread.h"
#include "ts/ink_queue.h"

#define NTHREADS 64
InkFreeList *flist = NULL;

void *
test(void *d)
{
    int id;
    void *m1, *m2, *m3;

    id = (intptr_t)d;

    time_t start = time(NULL);
    int count    = 0;
    for (;;) {
        m1 = ink_freelist_new(flist);
        m2 = ink_freelist_new(flist);
        m3 = ink_freelist_new(flist);

        if ((m1 == m2) || (m1 == m3) || (m2 == m3)) {
            printf("0x%08" PRIx64 "   0x%08" PRIx64 "   0x%08" PRIx64 "\n", (uint64_t)(uintptr_t)m1, (uint64_t)(uintptr_t)m2,
                   (uint64_t)(uintptr_t)m3);
            exit(1);
        }

        memset(m1, id, 64);
        memset(m2, id, 64);
        memset(m3, id, 64);

        ink_freelist_free(flist, m1);
        ink_freelist_free(flist, m2);
        ink_freelist_free(flist, m3);

        // break out of the test if we have run more then 60 seconds
        if (++count % 1000 == 0 && (start + 60) < time(NULL)) {
            return NULL;
        }
    }
}

int
main(int /* argc ATS_UNUSED */, char * /*argv ATS_UNUSED */ [])
{
    int i;

    flist = ink_freelist_create("woof", 64, 256, 8);

    for (i = 0; i < NTHREADS; i++) {
        fprintf(stderr, "Create thread %d\n", i);
        ink_thread_create(test, (void *)((intptr_t)i));
    }

    test((void *)NTHREADS);

    return 0;
}
