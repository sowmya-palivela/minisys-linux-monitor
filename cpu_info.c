
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    FILE *file;
    unsigned long long user, nice, system, idle;
    unsigned long long iowait, irq, softirq, steal;
    unsigned long long total1, idle1, total2, idle2;

    printf("=================================\n");
    printf("        MiniSys CPU Monitor     \n");
    printf("=================================\n");
    printf("Measuring CPU usage for 1 second...\n");

    file = fopen("/proc/stat", "r");
    if (file == NULL) {
        perror("Unable to open /proc/stat");
        return EXIT_FAILURE;
    }

    if (fscanf(file, "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
               &user, &nice, &system, &idle,
               &iowait, &irq, &softirq, &steal) != 8) {
        fprintf(stderr, "Could not read CPU statistics.\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);

    total1 = user + nice + system + idle
           + iowait + irq + softirq + steal;
    idle1 = idle + iowait;

    sleep(1);

    file = fopen("/proc/stat", "r");
    if (file == NULL) {
        perror("Unable to reopen /proc/stat");
        return EXIT_FAILURE;
    }

    if (fscanf(file, "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
               &user, &nice, &system, &idle,
               &iowait, &irq, &softirq, &steal) != 8) {
        fprintf(stderr, "Could not read CPU statistics.\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);

    total2 = user + nice + system + idle
           + iowait + irq + softirq + steal;
    idle2 = idle + iowait;

    unsigned long long total_delta = total2 - total1;
    unsigned long long idle_delta = idle2 - idle1;

    if (total_delta == 0) {
        printf("CPU usage could not be calculated.\n");
        return EXIT_SUCCESS;
    }

    double usage = 100.0 *
        (1.0 - (double)idle_delta / (double)total_delta);

    printf("CPU Usage: %.2f%%\n", usage);

    return EXIT_SUCCESS;
}
