#include <stdio.h>
#include <limits.h>

// Structure to store process details
struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

void calculateSRTF(struct Process processes[], int n) {
    int currentTime = 0, completed = 0, shortest = -1;
    int minRemainingTime = INT_MAX;

    int startTime[n], finishTime[n], isStarted[n];
    int responseTime[n];
    for (int i = 0; i < n; i++) {
        isStarted[i] = 0;
        startTime[i] = -1;
        finishTime[i] = 0;
        responseTime[i] = 0;
    }

    printf("\nExecution Timeline:\n");

    while (completed != n) {
        // Find process with shortest remaining time at current time
        minRemainingTime = INT_MAX;
        shortest = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && 
                processes[i].remainingTime > 0 && 
                processes[i].remainingTime < minRemainingTime) {
                minRemainingTime = processes[i].remainingTime;
                shortest = i;
            }
        }

        // If no process is found, increment time
        if (shortest == -1) {
            printf("Time %d: CPU is idle\n", currentTime);
            currentTime++;
            continue;
        }

        // First response time
        if (isStarted[shortest] == 0) {
            startTime[shortest] = currentTime;
            responseTime[shortest] = currentTime - processes[shortest].arrivalTime;
            isStarted[shortest] = 1;
        }

        // Execute process for 1 time unit
        printf("Time %d: Process P%d is running\n", currentTime, processes[shortest].pid);
        processes[shortest].remainingTime--;
        currentTime++;

        // If process is completed
        if (processes[shortest].remainingTime == 0) {
            finishTime[shortest] = currentTime;
            completed++;
        }
    }

    // Calculate averages
    float totalTAT = 0, totalWT = 0, totalRT = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        int tat = finishTime[i] - processes[i].arrivalTime;
        int wt = tat - processes[i].burstTime;
        totalTAT += tat;
        totalWT += wt;
        totalRT += responseTime[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
               processes[i].pid, 
               processes[i].arrivalTime, 
               processes[i].burstTime, 
               finishTime[i], 
               tat, 
               wt, 
               responseTime[i]);
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Waiting Time   : %.2f\n", totalWT / n);
    printf("Average Response Time  : %.2f\n", totalRT / n);
}

int main() {
    int n;
    
    // User input for number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Taking user input for processes
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].pid = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Perform SRTF Scheduling
    calculateSRTF(processes, n);

    return 0;
}


/