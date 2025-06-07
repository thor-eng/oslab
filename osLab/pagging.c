#include <stdio.h>

#define FRAME_SIZE 4
#define NUM_PAGES 5
#define NUM_FRAMES 8

int main() {
    int pageTable[NUM_PAGES];
    int i, logicalAddress, pageNumber, offset, physicalAddress;

    // Simulate a page table with random frame numbers
    printf("Page Table:\n");
    for (i = 0; i < NUM_PAGES; i++) {
        pageTable[i] = i + 2;  // Example mapping
        printf("Page %d -> Frame %d\n", i, pageTable[i]);
    }

    // Get logical address
    printf("\nEnter logical address (page number and offset): ");
    scanf("%d%d", &pageNumber, &offset);

    if (pageNumber >= NUM_PAGES || offset >= FRAME_SIZE) {
        printf("Invalid logical address.\n");
        return 1;
    }

    physicalAddress = pageTable[pageNumber] * FRAME_SIZE + offset;
    printf("Physical Address: %d\n", physicalAddress);

    return 0;
}



#include <stdio.h>

#define NUM_SEGMENTS 3

int main() {
    int segmentTable[NUM_SEGMENTS][2];  // base and limit
    int i, segmentNumber, offset, logicalAddress, physicalAddress;

    // Initialize segment table
    printf("Enter base and limit for each segment:\n");
    for (i = 0; i < NUM_SEGMENTS; i++) {
        printf("Segment %d - Base: ", i);
        scanf("%d", &segmentTable[i][0]);
        printf("Segment %d - Limit: ", i);
        scanf("%d", &segmentTable[i][1]);
    }

    // Get logical address
    printf("\nEnter logical address (segment number and offset): ");
    scanf("%d%d", &segmentNumber, &offset);

    if (segmentNumber >= NUM_SEGMENTS || offset >= segmentTable[segmentNumber][1]) {
        printf("Invalid logical address.\n");
        return 1;
    }

    physicalAddress = segmentTable[segmentNumber][0] + offset;
    printf("Physical Address: %d\n", physicalAddress);

    return 0;
}
