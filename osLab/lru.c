#include <stdio.h>

int main() {
    int pages[50], frame[10], n, f, i, j, k = 0, faults = 0;
    
    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    printf("Enter the page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    
    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i = 0; i < f; i++)
        frame[i] = -1;

    printf("\nPage Frames\n");
    for(i = 0; i < n; i++) {
        int found = 0;
        for(j = 0; j < f; j++) {
            if(frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            frame[k] = pages[i];
            k = (k + 1) % f;
            faults++;
        }

        for(j = 0; j < f; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", faults);
    return 0;
}




#include <stdio.h>

int findLRU(int time[], int f) {
    int i, min = time[0], pos = 0;
    for(i = 1; i < f; i++) {
        if(time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int pages[50], frame[10], time[10], n, f, i, j, pos, faults = 0, counter = 0;
    
    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    printf("Enter the page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i = 0; i < f; i++)
        frame[i] = -1;

    printf("\nPage Frames\n");
    for(i = 0; i < n; i++) {
        int found = 0;
        for(j = 0; j < f; j++) {
            if(frame[j] == pages[i]) {
                found = 1;
                time[j] = ++counter;
                break;
            }
        }

        if(!found) {
            pos = findLRU(time, f);
            frame[pos] = pages[i];
            time[pos] = ++counter;
            faults++;
        }

        for(j = 0; j < f; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", faults);
    return 0;
}




#include <stdio.h>

int predict(int pages[], int frame[], int n, int index, int f) {
    int res = -1, farthest = index;
    for(int i = 0; i < f; i++) {
        int j;
        for(j = index; j < n; j++) {
            if(frame[i] == pages[j]) {
                if(j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if(j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

int main() {
    int pages[50], frame[10], n, f, i, j, faults = 0;
    
    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    printf("Enter the page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i = 0; i < f; i++)
        frame[i] = -1;

    printf("\nPage Frames\n");
    for(i = 0; i < n; i++) {
        int found = 0;
        for(j = 0; j < f; j++) {
            if(frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            int empty = -1;
            for(j = 0; j < f; j++) {
                if(frame[j] == -1) {
                    empty = j;
                    break;
                }
            }

            if(empty != -1)
                frame[empty] = pages[i];
            else {
                int pos = predict(pages, frame, n, i + 1, f);
                frame[pos] = pages[i];
            }
            faults++;
        }

        for(j = 0; j < f; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", faults);
    return 0;
}
