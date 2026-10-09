



#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

static const char *state_description(char state) {
    switch (state) {
        case 'R': return "Running";
        case 'S': return "Sleeping";
        case 'D': return "Uninterruptible sleep";
        case 'T': return "Stopped";
        case 't': return "Tracing stop";
        case 'Z': return "Zombie";
        case 'X':
        case 'x': return "Dead";
        case 'I': return "Idle";
        case 'P': return "Parked";
        default:  return "Unknown";
    }
}

int main(void) {
    char filter;

    printf("========================================\n");
    printf("       MiniSys Process Analyzer         \n");
    printf("========================================\n");
    printf("Filter by process state:\n");
    printf("A - All processes\n");
    printf("R - Running or runnable\n");
    printf("S - Sleeping\n");
    printf("D - Uninterruptible sleep\n");
    printf("T - Stopped\n");
    printf("Z - Zombie\n");
    printf("Enter choice: ");

    if (scanf(" %c", &filter) != 1) {
        fprintf(stderr, "Unable to read filter.\n");
        return EXIT_FAILURE;
    }

    filter = (char)toupper((unsigned char)filter);

    if (filter != 'A' && filter != 'R' && filter != 'S'
        && filter != 'D' && filter != 'T' && filter != 'Z') {
        fprintf(stderr, "Invalid filter. Choose A, R, S, D, T or Z.\n");
        return EXIT_FAILURE;
    }

    DIR *proc_dir = opendir("/proc");

    if (proc_dir == NULL) {
        perror("Unable to open /proc");
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    int count = 0;

    printf("\n%-10s %-24s %s\n", "PID", "PROCESS NAME", "STATE");
    printf("----------------------------------------------------\n");

    while ((entry = readdir(proc_dir)) != NULL) {
        const char *name = entry->d_name;
        int is_pid = (*name != '\0');

        for (int i = 0; is_pid && name[i] != '\0'; i++) {
            if (!isdigit((unsigned char)name[i])) {
                is_pid = 0;
            }
        }

        if (!is_pid) {
            continue;
        }

        char *endptr;
        long pid = strtol(name, &endptr, 10);

        if (*endptr != '\0' || pid <= 0 || pid > INT_MAX) {
            continue;
        }

        char path[64];
        int written = snprintf(path, sizeof(path),
                               "/proc/%ld/stat", pid);

        if (written < 0 || (size_t)written >= sizeof(path)) {
            continue;
        }

        FILE *file = fopen(path, "r");
        if (file == NULL) {
            continue;
        }

        char line[4096];

        if (fgets(line, sizeof(line), file) != NULL) {
            char *open_paren = strchr(line, '(');
            char *close_paren = strrchr(line, ')');

            if (open_paren != NULL && close_paren != NULL
                && close_paren > open_paren
                && close_paren[1] == ' '
                && close_paren[2] != '\0') {

                char state = close_paren[2];

                if (filter == 'A' || state == filter) {
                    char process_name[256];
                    size_t length =
                        (size_t)(close_paren - open_paren - 1);

                    if (length >= sizeof(process_name)) {
                        length = sizeof(process_name) - 1;
                    }

                    memcpy(process_name, open_paren + 1, length);
                    process_name[length] = '\0';

                    printf("%-10ld %-24.24s %s\n",
                           pid, process_name,
                           state_description(state));
                    count++;
                }
            }
        }

        fclose(file);
    }

    closedir(proc_dir);

    printf("----------------------------------------------------\n");
    printf("Processes listed: %d\n", count);

    return EXIT_SUCCESS;
}
