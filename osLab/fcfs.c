#include <stdio.h>

// Define a structure to represent a process
struct Process {
    int pid; // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

// Function to sort processes based on arrival time
void sort(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                // Swap processes
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to calculate completion time, turnaround time, and waiting time
void calculateTimes(struct Process p[], int n) {
    int currentTime = 0;
    float totalWT = 0, totalTAT = 0, totalCT = 0;

    for (int i = 0; i < n; i++) {
        // If the current time is less than the arrival time, move to the arrival time
        if (currentTime < p[i].at) {
            currentTime = p[i].at;
        }
        // Completion time is current time + burst time
        currentTime += p[i].bt;
        p[i].ct = currentTime; // Set completion time
        p[i].tat = p[i].ct - p[i].at; // Turnaround time = Completion time - Arrival time
        p[i].wt = p[i].tat - p[i].bt; // Waiting time = Turnaround time - Burst time

        // Sum totals for averages
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
        totalCT += p[i].ct;
    }

    // Print averages
    printf("\nAverage Waiting Time   : %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Completion Time: %.2f\n", totalCT / n);
}

// Function to print process details
void printProcessDetails(struct Process p[], int n) {
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process p[n]; // Declare an array of processes

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1; // Assign process ID
        printf("Enter the arrival time for Process %d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter the burst time for Process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);
    }

    // Sort processes based on arrival time
    sort(p, n);

    // Print sorted processes
    printf("\nProcesses sorted by arrival time:\n");
    printf("PID\tArrival Time\tBurst Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", p[i].pid, p[i].at, p[i].bt);
    }

    // Calculate completion, turnaround, and waiting times
    calculateTimes(p, n);

    // Print process details
    printProcessDetails(p, n);

    return 0;
}
