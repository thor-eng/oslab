#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int at;
    int bt;
    int pr;
    int rt;
    int ct;
    int st;
    bool started;
};

// Sort by arrival time
void sort(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void simulatePreemptivePriority(struct Process p[], int n) {
    int currentTime = 0;
    int completed = 0;
    bool isCompleted[n];
    int totalTAT = 0, totalWT = 0, totalRT = 0;

    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
        isCompleted[i] = false;
        p[i].started = false;
    }

    printf("\nTime \tRunning Process\n");

    while (completed < n) {
        int idx = -1;
        int minPr = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !isCompleted[i] && p[i].pr < minPr) {
                minPr = p[i].pr;
                idx = i;
            }
        }

        if (idx != -1) {
            printf("%d \tP%d\n", currentTime, p[idx].pid);

            if (!p[idx].started) {
                p[idx].started = true;
                p[idx].st = currentTime;
            }

            p[idx].rt--;
            currentTime++;

            if (p[idx].rt == 0) {
                p[idx].ct = currentTime;
                isCompleted[idx] = true;
                completed++;

                int tat = p[idx].ct - p[idx].at;
                int wt = tat - p[idx].bt;
                int rt = p[idx].st - p[idx].at;

                totalTAT += tat;
                totalWT += wt;
                totalRT += rt;
            }
        } else {
            printf("%d \tIDLE\n", currentTime);
            currentTime++;
        }
    }

    float avgTAT = (float)totalTAT / n;
    float avgWT = (float)totalWT / n;
    float avgRT = (float)totalRT / n;

    printf("\nAverage Turnaround Time: %.2f\n", avgTAT);
    printf("Average Waiting Time   : %.2f\n", avgWT);
    printf("Average Response Time  : %.2f\n", avgRT);
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
        printf("Enter the priority for Process %d (lower number = higher priority): ", p[i].pid);
        scanf("%d", &p[i].pr);
    }

    sort(p, n);
    simulatePreemptivePriority(p, n);

    return 0;
}


// Time    Running Process
// 0       P1
// 1       P2
// 2       P2
// 3       P2
// 4       P1
// 5       P1
// 6       P1
// 7       P3
// 8       P3
// 9       P3
// 10      P3

// Average Turnaround Time: 6.33
// Average Waiting Time   : 2.33
// Average Response Time  : 1.67





