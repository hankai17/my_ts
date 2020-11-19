#include "ts/Arena.h"
#include <stdio.h>

void
fill_test_data(char *ptr, int size, int seed)
{
    char a = 'a' + (seed % 52);

    for (int i = 0; i < size; i++) {
        ptr[i] = a;
        a      = (a + 1) % 52;
    }
}

int
check_test_data(char *ptr, int size, int seed)
{
    int fail = 0;
    char a   = 'a' + (seed % 52);

    for (int i = 0; i < size; i++) {
        if (ptr[i] != a) {
            fail++;
        }
        a = (a + 1) % 52;
    }

    return fail;
}

int
test_block_boundries()
{
    const int sizes_to_test   = 12;
    const int regions_to_test = 1024 * 2;
    char **test_regions       = new char *[regions_to_test];
    int failures              = 0;
    Arena *a                  = new Arena();

    for (int i = 0; i < sizes_to_test; i++) {
        int test_size = 1 << i;

        // Clear out the regions array
        int j = 0;
        for (j = 0; j < regions_to_test; j++) {
            test_regions[j] = NULL;
        }

        // Allocate and fill the array
        for (j = 0; j < regions_to_test; j++) {
            test_regions[j] = (char *)a->alloc(test_size);
            fill_test_data(test_regions[j], test_size, j);
        }

        // Now check to make sure the data is correct
        for (j = 0; j < regions_to_test; j++) {
            int f = check_test_data(test_regions[j], test_size, j);

            if (f != 0) {
                fprintf(stderr, "block_boundries test failed.  size %d region %d\n", test_size, j);
                failures++;
            }
        }

        // Now free the regions
        for (j = 0; j < regions_to_test; j++) {
            a->free(test_regions[j], test_size);
        }

        a->reset();
    }

    delete[] test_regions;
    delete a;
    return failures;
}

int
main()
{
    int failures = 0;

    failures += test_block_boundries();

    if (failures) {
        return 1;
    } else {
        return 0;
    }
}
