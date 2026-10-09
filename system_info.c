#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>

int main(void) {
    struct utsname system_info;

    printf("=================================\n");
    printf("       MiniSys System Info       \n");
    printf("=================================\n");

    if (uname(&system_info) == -1) {
        perror("uname failed");
        return EXIT_FAILURE;
    }

    printf("Operating System : %s\n", system_info.sysname);
    printf("Hostname         : %s\n", system_info.nodename);
    printf("Kernel Release   : %s\n", system_info.release);
    printf("Machine Type     : %s\n", system_info.machine);

    return EXIT_SUCCESS;
}
