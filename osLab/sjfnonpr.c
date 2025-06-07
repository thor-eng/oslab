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

// Sort by arrival time and burst time
void sort(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at || (p[j].at == p[j + 1].at && p[j].bt > p[j + 1].bt)) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Calculate CT, TAT, WT, and show averages
void calculateTimes(struct Process p[], int n) {
    int currentTime = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    while (completed < n) {
        int idx = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].bt < min_bt && p[i].ct == 0) {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        if (idx != -1) {
            currentTime += p[idx].bt;
            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;
            completed++;
        } else {
            currentTime++;
        }
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
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

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the arrival time for Process %d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter the burst time for Process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);
        p[i].ct = 0;
    }

    sort(p, n);

    printf("\nProcesses sorted by arrival and burst time (for SJF):\n");
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t--\t\t--\t\t--\n", p[i].pid, p[i].at, p[i].bt);
    }

    calculateTimes(p, n);
    printProcessDetails(p, n);

    return 0;
}





// Processes sorted by arrival and burst time (for SJF):
// PID     Arrival Time    Burst Time      Completion Time Turnaround Time Waiting Time
// 1       0               6               --              --              --
// 2       1               8               --              --              --
// 3       2               7               --              --              --
// 4       3               3               --              --              --

// Average Waiting Time: 5.25
// Average Turnaround Time: 10.25

// PID     Arrival Time    Burst Time      Completion Time Turnaround Time Waiting Time
// 1       0               6               6               6               0
// 4       3               3               9               6               3
// 3       2               7               16              14              7
// 2       1               8               24              23              15
