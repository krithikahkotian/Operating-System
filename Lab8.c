#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_BLOCKS 100

typedef struct {
    int startBlock;
    int length;
    bool allocated;
} File;

int main() {  
    int disk[MAX_BLOCKS] = {0};
    File files[10];
    int n, i, j, k;
    printf("Enter number of files: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        int start, length;
        printf("\nEnter start block and length for file %d: ", i + 1);
        scanf("%d %d", &start, &length);
        bool canAllocate = true;
        if (start + length > MAX_BLOCKS) {
            printf("File %d: Out of disk bounds. Cannot allocate.\n", i + 1);
            files[i].allocated = false;
            continue;
        }
        for (j = start; j < start + length; j++) {
            if (disk[j] == 1) {
                canAllocate = false;
                break;
            }
        }
        if (canAllocate) {
            for (j = start; j < start + length; j++) {
                disk[j] = 1;
            }
            files[i].startBlock = start;
            files[i].length = length;
            files[i].allocated = true;
            printf("File %d allocated from block %d to %d.\n", i + 1, start, start + length - 1);
        } else {
            printf("File %d: Blocks already allocated. Cannot allocate.\n", i + 1);
            files[i].allocated = false;
        }
    }
    printf("\nFile Allocation Table:\n");
    printf("File\tStart\tLength\tStatus\n");
    for (i = 0; i < n; i++) {
        printf("%d\t", i + 1);
        if (files[i].allocated) {
            printf("%d\t%d\tAllocated\n", files[i].startBlock, files[i].length);
        } else {
            printf("-\t-\tNot Allocated\n");
        }
    }
    return 0;
}
