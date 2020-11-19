#include "ts/ink_platform.h"
#include "ts/ink_defs.h"
#include "ts/ink_file.h"

// This isn't really a unit test. It's just a dumb little program to probe the disk
// geometry of an arbitrary device file. That's useful when figuring out how ATS will
// perceive different devices on differen operating systems.

int
main(int argc, const char **argv)
{
    for (int i = 1; i < argc; ++i) {
        int fd;
        ink_device_geometry geometry;

        fd = open(argv[i], O_RDONLY);
        if (fd == -1) {
            fprintf(stderr, "open(%s): %s\n", argv[i], strerror(errno));
            continue;
        }

        if (ink_file_get_geometry(fd, geometry)) {
            printf("%s:\n", argv[i]);
            printf("\ttotalsz: %" PRId64 "\n", geometry.totalsz);
            printf("\tblocksz: %u\n", geometry.blocksz);
            printf("\talignsz: %u\n", geometry.alignsz);
        } else {
            printf("%s: %s (%d)\n", argv[i], strerror(errno), errno);
        }

        close(fd);
    }

    return 0;
}
