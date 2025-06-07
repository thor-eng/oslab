#include <stdio.h>
#include <stdbool.h>

#define P 2 // Number of processes
#define R 2 // Number of resources

// Function to check if the system is in a safe state
bool isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    bool finish[P] = {0};
    int safeSeq[P];
    int work[R];
    int count = 0;

    // Calculate the need matrix
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];

    // Initialize work with available resources
    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    // Find a safe sequence
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                // Check if need can be satisfied with current work
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    // Simulate allocation
                    for (int j = 0; j < R; j++)
                        work[j] += allot[p][j];
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");
    return true;
}

// Function to request resources
bool requestResources(int process, int request[], int avail[], int max[][R], int allot[][R]) {
    // Check if request is less than max need
    for (int i = 0; i < R; i++) {
        if (request[i] > max[process][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    // Check if request is less than available
    for (int i = 0; i < R; i++) {
        if (request[i] > avail[i]) {
            printf("Process is waiting as resources are not available.\n");
            return false;
        }
    }

    // Pretend to allocate resources
    for (int i = 0; i < R; i++) {
        avail[i] -= request[i];
        allot[process][i] += request[i];
    }

    // Check if the system is in a safe state
    if (isSafe((int[]){0, 1}, avail, max, allot)) {
        return true;
    } else {
        // Rollback
        for (int i = 0; i < R; i++) {
            avail[i] += request[i];
            allot[process][i] -= request[i];
        }
        printf("Request cannot be granted as it leads to an unsafe state.\n");
        return false;
    }
}

int main() {
    int processes[] = {0, 1};
    int avail[R]; // Available instances of resources
    int max[P][R]; // Maximum R that can be allocated to processes
    int allot[P][R]; // Resources allocated to processes

    // User input for available resources
    printf("Enter available resources (space-separated): ");
    for (int i = 0; i < R; i++) {
        scanf("%d", &avail[i]);
    }

    // User input for maximum resources
    printf("Enter maximum resources for each process (2x2 matrix, space-separated):\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // User input for allocated resources
    printf("Enter allocated resources for each process (2x2 matrix, space-separated):\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &allot[i][j]);
        }
    }

    // Request resources for a process
    int process, request[R];
    printf("Enter process number (0 or 1) requesting resources: ");
    scanf("%d", &process);
    printf("Enter request for resources (space-separated): ");
    for (int i = 0; i < R; i++) {
        scanf("%d", &request[i]);
    }

    // Attempt to request resources
    if (requestResources(process, request, avail, max, allot)) {
        printf("Resources allocated successfully.\n");
    } else {
        printf("Resources could not be allocated.\n");
    }

    return 0;
}