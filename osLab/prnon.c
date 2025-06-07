#include <stdio.h>
#include <stdbool.h>

// Define a structure to represent a process
struct Process {
    int pid; // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int pr;  // Priority
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

// Function to sort processes based on arrival time and priority
void sort(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Sort by arrival time first, then by priority
            if (p[j].at > p[j + 1].at || 
                (p[j].at == p[j + 1].at && p[j].pr > p[j + 1].pr)) {
                // Swap processes
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to calculate completion time, turnaround time, waiting time, and print averages
void calculateTimes(struct Process p[], int n) {
    int currentTime = 0;
    int completed = 0;
    bool isCompleted[n];

    // Initialize completion status
    for (int i = 0; i < n; i++) {
        isCompleted[i] = false; // Mark all processes as not completed
    }

    while (completed < n) {
        int idx = -1;
        int minPr = 9999; // Initialize to a large value

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !isCompleted[i] && p[i].pr < minPr) {
                minPr = p[i].pr;
                idx = i;
            }
        }

        if (idx != -1) {
            // Execute the process with the highest priority
            currentTime += p[idx].bt; // Update current time
            p[idx].ct = currentTime; // Set completion time
            p[idx].tat = p[idx].ct - p[idx].at; // Turnaround time
            p[idx].wt = p[idx].tat - p[idx].bt; // Waiting time
            isCompleted[idx] = true; // Mark process as completed
            completed++; // Increment completed processes
        } else {
            // If no process is found, move time forward
            currentTime++;
        }
    }

    // Calculate and print averages
    float totalWT = 0, totalTAT = 0, totalCT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
        totalCT += p[i].ct;
    }
    printf("\nAverage Waiting Time     : %.2f\n", totalWT / n);
    printf("Average Turnaround Time  : %.2f\n", totalTAT / n);
    printf("Average Completion Time  : %.2f\n", totalCT / n);
}

// Function to print process details
void printProcessDetails(struct Process p[], int n) {
    printf("\nPID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               p[i].pid, p[i].at, p[i].bt, p[i].pr, p[i].ct, p[i].tat, p[i].wt);
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
        printf("Enter the priority for Process %d (lower number indicates higher priority): ", p[i].pid);
        scanf("%d", &p[i].pr);
    }

    // Sort processes based on arrival time and priority
    sort(p, n);

    // Print sorted processes
    printf("\nProcesses sorted by arrival time and priority:\n");
    printf("PID\tArrival Time\tBurst Time\tPriority\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].pr);
    }

    // Calculate completion, turnaround, and waiting times
    calculateTimes(p, n);

    // Print process details
    printProcessDetails(p, n);

    return 0;
}





// Processes sorted by arrival time and priority:
// PID     Arrival Time    Burst Time      Priority
// 1       0               5               2
// 2       1               3               1
// 3       2               8               4
// 4       3               6               3

// Average Waiting Time     : 4.25
// Average Turnaround Time  : 10.25
// Average Completion Time  : 11.50

// PID     Arrival Time    Burst Time      Priority        Completion Time Turnaround Time  Waiting Time
// 1       0               5               2               14              14              9
// 2       1               3               1               4               3               0
// 3       2               8               4               26              24              16
// 4       3               6               3               20              17              11
