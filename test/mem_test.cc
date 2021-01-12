#include "stdio.h"
#include "ts/ink_memory.h"

#define ALIGN(size, boundary) (((size) + ((boundary)-1)) & ~((boundary)-1)) // 向上取整

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
        printf("addr 1023: %d\n", 1023 & ~(page_size - 1)); // 向下取整
        printf("addr 4097: %d\n", 4097 & ~(page_size - 1));
        printf("addr 8193: %d\n", 8193 & ~(page_size - 1));
    }

    printf("align(2049, 1024): %d\n", ALIGN(2049, 1024));
    return 0;
}
