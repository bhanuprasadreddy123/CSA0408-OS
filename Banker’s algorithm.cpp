#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

void calculateNeed(int need[MAX_P][MAX_R], int max[MAX_P][MAX_R], int alloc[MAX_P][MAX_R], int P, int R) {
for (int i = 0; i < P; i++)
for (int j = 0; j < R; j++)
need[i][j] = max[i][j] - alloc[i][j];
}

bool isSafe(int processes[], int avail[], int max[][MAX_R], int alloc[][MAX_R], int P, int R) {
int need[MAX_P][MAX_R];
calculateNeed(need, max, alloc, P, R);

bool finish[MAX_P] = {0};
int safeSeq[MAX_P];
int work[MAX_R];
for (int i = 0; i < R; i++)
work[i] = avail[i];

int count = 0;
while (count < P) {
bool found = false;
for (int p = 0; p < P; p++) {
if (!finish[p]) {
int j;
for (j = 0; j < R; j++)
if (need[p][j] > work[j])
break;
if (j == R) {
for (int k = 0; k < R; k++)
work[k] += alloc[p][k];
safeSeq[count++] = p;
finish[p] = true;
found = true;
}
}
}
if (!found) {
printf("System is not in safe state");
return false;
}
}

printf("System is in safe state.\nSafe sequence is: ");
for (int i = 0; i < P; i++)
printf("%d ", safeSeq[i]);
printf("\n");
return true;
}

int main() {
int P, R;
printf("Enter number of processes: ");
scanf("%d", &P);
printf("Enter number of resources: ");
scanf("%d", &R);

int processes[MAX_P];
printf("Enter process IDs: ");
for (int i = 0; i < P; i++)
scanf("%d", &processes[i]);

int available[MAX_R];
printf("Enter available instances of resources: ");
for (int i = 0; i < R; i++)
scanf("%d", &available[i]);

int max[MAX_P][MAX_R];
printf("Enter maximum resources that can be allocated to each process:\n");
for (int i = 0; i < P; i++) {
printf("For process %d: ", processes[i]);
for (int j = 0; j < R; j++)
scanf("%d", &max[i][j]);
}

int allocation[MAX_P][MAX_R];
printf("Enter resources allocated to each process:\n");
for (int i = 0; i < P; i++) {
printf("For process %d: ", processes[i]);
for (int j = 0; j < R; j++)
scanf("%d", &allocation[i][j]);
}

isSafe(processes, available, max, allocation, P, R);

return 0;
}
