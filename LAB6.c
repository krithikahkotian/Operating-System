#include <stdio.h>
#include <stdbool.h>
#define MAX_P 10
#define MAX_R 10
int main() {
    int processes, resources;
    int allocation[MAX_P][MAX_R], max[MAX_P][MAX_R], need[MAX_P][MAX_R];
    int available[MAX_R];
    bool finished[MAX_P] = {false};
    int safeSequence[MAX_P];
    int i, j;
    printf("Enter number of processes -- ");
    scanf("%d", &processes);
    printf("Enter number of resources -- ");
    scanf("%d", &resources);
    for (i = 0; i < processes; i++) {
        printf("Enter details for P%d\n", i);
        printf("Enter allocation -- ");
        for (j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
        printf("Enter Max -- ");
        for (j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    printf("Enter Available Resources -- ");
    for (i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }
    int req_pid, request[MAX_R];
    printf("Enter New Request Details --\n");
    printf("Enter pid -- ");
    scanf("%d", &req_pid);
    printf("Enter Request for Resources -- ");
    for (i = 0; i < resources; i++) {
        scanf("%d", &request[i]);
    }
    bool valid = true;
    for (i = 0; i < resources; i++) {
        if (request[i] > need[req_pid][i] || request[i] > available[i]) {
            valid = false;
            break;
        }
    }
    if (!valid) {
        printf("Request cannot be granted immediately.\n");
        return 1;
    }
    for (i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[req_pid][i] += request[i];
        need[req_pid][i] -= request[i];
    }
    int work[MAX_R];
    for (i = 0; i < resources; i++) work[i] = available[i];
    int count = 0;
    printf("\nOUTPUT\n");
    while (count < processes) {
        bool found = false;
        for (i = 0; i < processes; i++) {
            if (!finished[i]) {
                bool canRun = true;
                for (j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }
                if (canRun) {
                    for (j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finished[i] = true;
                    safeSequence[count++] = i;
                    printf("P%d is visited( %d %d %d )\n", i, work[0], work[1], work[2]);
                    found = true;
                }
            }
        }
        if (!found) break;
    }
    if (count == processes) {
        printf("SYSTEM IS IN SAFE STATE\n");
        printf("The Safe Sequence is -- ");
        for (i = 0; i < processes; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("SYSTEM IS NOT IN SAFE STATE\n");
    }

    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    for (i = 0; i < processes; i++) {
        printf("P%d\t", i);
        for (j = 0; j < resources; j++) printf("%d ", allocation[i][j]);
        printf("\t\t");
        for (j = 0; j < resources; j++) printf("%d ", max[i][j]);
        printf("\t");
        for (j = 0; j < resources; j++) printf("%d ", need[i][j]);
        printf("\n");
    }

    return 0;
}
