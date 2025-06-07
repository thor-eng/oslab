#include <stdio.h>

// Define a structure to represent a process
struct Process {
    int pid; // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int rt;  // Remaining Time (if needed)
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

void roundrobin(struct Process p[], int n) {
    int array[n], sum = 0;
    for (int i = 0; i < n; i++) {
        array[i] = 0;  // Initialize all processes as not completed
    }

    int tq; // Time Quantum
    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    int time = 0;
    int complete = 0;
    int start[n], finish[n], response[n];
    for (int i = 0; i < n; i++) {
        start[i] = -1;
        finish[i] = 0;
        response[i] = 0;
    }

    printf("\nTime\tRunning Process\n");

    while (complete < n) {
        int doneInCycle = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                doneInCycle = 1;

                if (start[i] == -1) {
                    start[i] = time;
                    response[i] = time - p[i].at;
                }

                if (p[i].rt > tq) {
                    printf("%d\tP%d\n", time, p[i].pid);
                    time += tq;
                    p[i].rt -= tq;
                } else {
                    printf("%d\tP%d\n", time, p[i].pid);
                    time += p[i].rt;
                    p[i].rt = 0;
                    finish[i] = time;
                    complete++;
                }
            }
        }

        if (!doneInCycle) {
            printf("%d\tIDLE\n", time);
            time++;
        }
    }

    float totalTAT = 0, totalWT = 0, totalRT = 0;
    for (int i = 0; i < n; i++) {
        int tat = finish[i] - p[i].at;
        int wt = tat - p[i].bt;
        totalTAT += tat;
        totalWT += wt;
        totalRT += response[i];
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Waiting Time   : %.2f\n", totalWT / n);
    printf("Average Response Time  : %.2f\n", totalRT / n);
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
        p[i].rt = p[i].bt;  // Initialize remaining time with burst time
    }

    // Sort processes based on arrival time
    sort(p, n);

    // Print sorted processes
    printf("\nProcesses sorted by arrival time:\n");
    printf("PID\tArrival Time\tBurst Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", p[i].pid, p[i].at, p[i].bt);
    }

    // Run round robin scheduling
    roundrobin(p, n);

    return 0;
}



// Enter the number of processes: 3
// Enter arrival time for Process 1: 0
// Enter burst time for Process 1: 5
// Enter arrival time for Process 2: 1
// Enter burst time for Process 2: 3
// Enter arrival time for Process 3: 2
// Enter burst time for Process 3: 4
// Enter the time quantum: 2

// Time    Running Process
// 0       P1
// 2       P2
// 4       P3
// 6       P1
// 8       P2
// 9       P3
// 11      P1
// 12      P3

// Average Turnaround Time: 8.33
// Average Waiting Time   : 3.33
// Average Response Time  : 1.67







