#include <stdio.h>
#include <stdbool.h>

#define MAX 50

void printFrames(int frames[], int frameCount) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

bool search(int key, int frames[], int frameCount) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == key)
            return true;
    }
    return false;
}

int findLRU(int time[], int frameCount) {
    int min = time[0], pos = 0;
    for (int i = 1; i < frameCount; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void fifo(int pages[], int n, int frameCount) {
    int frames[MAX], front = 0, faults = 0;
    for (int i = 0; i < frameCount; i++) frames[i] = -1;

    printf("FIFO Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        if (!search(pages[i], frames, frameCount)) {
            frames[front] = pages[i];
            front = (front + 1) % frameCount;
            faults++;
            printf("PF No. %d: ", faults);
            printFrames(frames, frameCount);
        }
    }

    printf("FIFO Page Faults: %d\n", faults);
}

void lru(int pages[], int n, int frameCount) {
    int frames[MAX], time[MAX], faults = 0, counter = 0;
    for (int i = 0; i < frameCount; i++) frames[i] = -1;

    printf("\nLRU Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        bool hit = search(pages[i], frames, frameCount);

        if (!hit) {
            int pos = -1;

            // Find empty frame first
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame, use LRU
            if (pos == -1) {
                pos = findLRU(time, frameCount);
            }

            frames[pos] = pages[i];
            faults++;
            printf("PF No. %d: ", faults);
            printFrames(frames, frameCount);
        }

        // Update access time
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == pages[i]) {
                time[j] = ++counter;
            }
        }
    }

    printf("LRU Page Faults: %d\n", faults);
}


int predict(int pages[], int frames[], int n, int index, int frameCount) {
    int result = -1, farthest = index;

    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    result = i;
                }
                break;
            }
        }

        if (j == n) return i;
    }

    return (result == -1) ? 0 : result;
}

void optimal(int pages[], int n, int frameCount) {
    int frames[MAX], faults = 0;
    for (int i = 0; i < frameCount; i++) frames[i] = -1;

    printf("\nOptimal Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        if (!search(pages[i], frames, frameCount)) {
            int pos = -1;

            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) {
                pos = predict(pages, frames, n, i + 1, frameCount);
            }

            frames[pos] = pages[i];
            faults++;
            printf("PF No. %d: ", faults);
            printFrames(frames, frameCount);
        }
    }

    printf("Optimal Page Faults: %d\n", faults);
}

int main() {
    int pages[MAX], n, frameCount;

    printf("Enter the number of Frames: ");
    scanf("%d", &frameCount);

    printf("Enter the length of reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    fifo(pages, n, frameCount);
    lru(pages, n, frameCount);
    optimal(pages, n, frameCount);

    return 0;
}
