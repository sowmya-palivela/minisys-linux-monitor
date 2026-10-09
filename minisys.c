
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int choice;

    while (1) {
        printf("\n=================================\n");
        printf("          MiniSys Monitor        \n");
        printf("=================================\n");
        printf("1. System Information\n");
        printf("2. Memory Information\n");
        printf("3. CPU Usage\n");
        printf("4. Process Analyzer\n");
        printf("5. Exit\n");
        printf("---------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* Discard invalid input. */
            }

            if (ch == EOF) {
                break;
            }

            continue;
        }

        switch (choice) {
            case 1:
                printf("\nLaunching System Information...\n");
                system("./system_info");
                break;

            case 2:
                printf("\nLaunching Memory Monitor...\n");
                system("./memory_info");
                break;

            case 3:
                printf("\nLaunching CPU Monitor...\n");
                system("./cpu_info");
                break;

            case 4:
                printf("\nLaunching Process Analyzer...\n");
                system("./process_info");
                break;

            case 5:
                printf("\nExiting MiniSys. Goodbye!\n");
                return EXIT_SUCCESS;

            default:
                printf("\nInvalid choice. Select 1 to 5.\n");
        }
    }

    return EXIT_SUCCESS;
}
