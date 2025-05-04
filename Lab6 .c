#include <stdio.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

void worstFit(int blockSize[], int blocks, int processSize[], int processes);
void bestFit(int blockSize[], int blocks, int processSize[], int processes);
void firstFit(int blockSize[], int blocks, int processSize[], int processes);

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int blocks, processes, i;

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);
    printf("Enter sizes of %d blocks:\n", blocks);
    for (i = 0; i < blocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &processes);
    printf("Enter sizes of %d processes:\n", processes);
    for (i = 0; i < processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    printf("\n--- First Fit Allocation ---\n");
    firstFit(blockSize, blocks, processSize, processes);

    printf("\n--- Best Fit Allocation ---\n");
    bestFit(blockSize, blocks, processSize, processes);

    printf("\n--- Worst Fit Allocation ---\n");
    worstFit(blockSize, blocks, processSize, processes);

    return 0;
}

void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    int i, j;
    int tempBlocks[MAX_BLOCKS];

    // Copy original block sizes to temp
    for (i = 0; i < blocks; i++)
        tempBlocks[i] = blockSize[i];

    for (i = 0; i < processes; i++) {
        allocation[i] = -1;
        for (j = 0; j < blocks; j++) {
            if (tempBlocks[j] >= processSize[i]) {
                allocation[i] = j;
                tempBlocks[j] -= processSize[i];
                break;
            }
        }
    }

    for (i = 0; i < processes; i++) {
        printf("Process %d (Size %d) --> ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    int i, j, bestIdx;
    int tempBlocks[MAX_BLOCKS];

    for (i = 0; i < blocks; i++)
        tempBlocks[i] = blockSize[i];

    for (i = 0; i < processes; i++) {
        allocation[i] = -1;
        bestIdx = -1;
        for (j = 0; j < blocks; j++) {
            if (tempBlocks[j] >= processSize[i]) {
                if (bestIdx == -1 || tempBlocks[j] < tempBlocks[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            tempBlocks[bestIdx] -= processSize[i];
        }
    }

    for (i = 0; i < processes; i++) {
        printf("Process %d (Size %d) --> ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    int i, j, worstIdx;
    int tempBlocks[MAX_BLOCKS];

    for (i = 0; i < blocks; i++)
        tempBlocks[i] = blockSize[i];

    for (i = 0; i < processes; i++) {
        allocation[i] = -1;
        worstIdx = -1;
        for (j = 0; j < blocks; j++) {
            if (tempBlocks[j] >= processSize[i]) {
                if (worstIdx == -1 || tempBlocks[j] > tempBlocks[worstIdx])
                    worstIdx = j;
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            tempBlocks[worstIdx] -= processSize[i];
        }
    }

    for (i = 0; i < processes; i++) {
        printf("Process %d (Size %d) --> ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
