#include <stdio.h>
void calculateTimes(int pid[], int burst_time[], int completion_time[], int waiting_time[], int turnaround_time[], int n) {
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        current_time += burst_time[i];
        completion_time[i] = current_time;
        turnaround_time[i] = completion_time[i];
        waiting_time[i] = turnaround_time[i] - burst_time[i];
    }
}

void displayAndCalculateAverages(int pid[], int burst_time[], int completion_time[], int turnaround_time[], int waiting_time[], int queue[], int n) {
    int total_tat = 0, total_wt = 0;
    printf("PID\tQueue\tBurst\tCompletion\tTAT\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", pid[i], queue[i], burst_time[i],
               completion_time[i], turnaround_time[i], waiting_time[i]);
        total_tat += turnaround_time[i];
        total_wt += waiting_time[i];
    }
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
}

int main() {
    int n, count = 0;
    int pid[20], burst_time[20], completion_time[20], waiting_time[20], turnaround_time[20], queue[20];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nEnter burst time for Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        printf("Enter the queue for Process %d (1 or 2):", i + 1);
        scanf("%d", &queue[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (queue[j] > queue[j + 1]) {
                int temp_pid = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp_pid;

                int temp_burst = burst_time[j];
                burst_time[j] = burst_time[j + 1];
                burst_time[j + 1] = temp_burst;

                int temp_queue = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp_queue;
            }
        }
    }

    printf("\nScheduling (FCFS):\n");
    calculateTimes(pid, burst_time, completion_time, waiting_time, turnaround_time, n);
    displayAndCalculateAverages(pid, burst_time, completion_time, turnaround_time, waiting_time, queue, n);

    return 0;
}
