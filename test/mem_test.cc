#include "stdio.h"
#include "ts/ink_memory.h"

int main() {
    int page_size = 0;
    void* ptr = ats_memalign(1024 * 4, 1024 * 8);
    if (ptr == NULL) {
        printf("memalign address failed\n");
        return 0;
    }
    ats_memalign_free(ptr);

    page_size = ats_pagesize();
    printf("ats_pagesize: %d\n", page_size);
    {
        printf("addr 1023: %d\n", 1023 & ~(page_size - 1));
        printf("addr 1023: %d\n", 4097 & ~(page_size - 1));
    }


    return 0;
}
