
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *file = fopen("/proc/meminfo", "r");

    if (file == NULL) {
        perror("Unable to open /proc/meminfo");
        return EXIT_FAILURE;
    }

    char line[256];
    unsigned long total_kb = 0;
    unsigned long available_kb = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "MemTotal: %lu kB", &total_kb) == 1) {
            continue;
        }

        if (sscanf(line, "MemAvailable: %lu kB", &available_kb) == 1) {
            break;
        }
    }

    fclose(file);

    if (total_kb == 0 || available_kb == 0) {
        fprintf(stderr, "Could not read memory statistics.\n");
        return EXIT_FAILURE;
    }

    unsigned long used_kb = total_kb - available_kb;

    printf("=================================\n");
    printf("       MiniSys Memory Info       \n");
    printf("=================================\n");
    printf("Total Memory     : %.2f GB\n",
           total_kb / 1024.0 / 1024.0);
    printf("Available Memory : %.2f GB\n",
           available_kb / 1024.0 / 1024.0);
    printf("Estimated Used   : %.2f GB\n",
           used_kb / 1024.0 / 1024.0);

    return EXIT_SUCCESS;
}
