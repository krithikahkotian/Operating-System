#include<stdio.h>
#define MAX 10
int fork[MAX];
void wait(int fork[], int i) {
    if (fork[i] == 1)
        fork[i] = 0;
}
void signal(int fork[], int i) {
    fork[i] = 1;
}
int can_eat(int fork[], int i, int total) {
    int left = i;
    int right = (i + 1) % total;
    return fork[left] && fork[right];
}
void take_forks(int fork[], int i, int total) {
    int left=i;
    int right=(i+1)%total;
    wait(fork, left);
    wait(fork, right);
    printf("P %d is granted to eat\n", i + 1);
}
void put_forks(int fork[], int i, int total) {
    int left = i;
    int right = (i + 1) % total;
    signal(fork, left);
    signal(fork, right);
    printf("P %d has finished eating\n", i + 1);
}
int main() {
    int total, hungryCount, hungry[MAX], choice;
    printf("Enter the total number of philosophers: ");
    scanf("%d", &total);
    for (int i = 0; i < total; i++)
        fork[i] = 1;
    printf("How many are hungry: ");
    scanf("%d", &hungryCount);
    for (int i = 0; i < hungryCount; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, total);
        scanf("%d", &hungry[i]);
        hungry[i]--;
    }
    while (1) {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 3) {
            printf("Exiting...\n");
            break;
        }
        if (choice == 1) {
            printf("Allow one philosopher to eat at any time\n");
            for (int i = 0; i < hungryCount; i++) {
                for (int j = 0; j < hungryCount; j++)
                    printf("P %d is waiting\n", hungry[j] + 1);
                int p = hungry[i];
                if (can_eat(fork, p, total)) {
                    take_forks(fork, p, total);
                    put_forks(fork, p, total);
                } else {
                    printf("P %d cannot eat right now (forks unavailable)\n", p + 1);
                }
            }
        } else if (choice == 2) {
            printf("Allow two philosophers to eat at any time\n");
            int granted[MAX] = {0};
            for (int i = 0; i < hungryCount ; i++) {
                int p = hungry[i];
                if (can_eat(fork, p, total)) {
                    take_forks(fork, p, total);
                    granted[i] = 1;
                }
            }
            for (int i = 0; i < hungryCount; i++) {
                if (granted[i]) {
                    put_forks(fork, hungry[i], total);
                } else {
                    printf("P %d is waiting\n", hungry[i] + 1);
                }
            }
        } else {
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
