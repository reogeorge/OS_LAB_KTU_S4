#include <stdio.h>

int available[10], allocation[10][10], req[10][10], finish[10], flag = 0;

void main() {
    int n, m;
    printf("Enter the no. of processes: ");
    scanf("%d", &n);
    printf("Enter the no. of resource types: ");
    scanf("%d", &m);

    printf("\nEnter available resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    printf("\nEnter allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nRequest matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &req[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        flag = 0;
        for (int j = 0; j < m; j++) {
            if (allocation[i][j] != 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            finish[i] = 1;
        } else {
            finish[i] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (finish[j] == 0) {
                flag = 0;
                for (int k = 0; k < m; k++) {
                    if (req[j][k] > available[k]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    for (int l = 0; l < m; l++) {
                        available[l] += allocation[j][l];
                    }
                    finish[j] = 1;
                }
            }
        }
    }

    flag = 0;
    for (int i = 0; i < n; i++) {
        if (finish[i] == 0) {
            flag = 1;
            printf("\nDeadlock detected!\n");
            break;
        }
    }

    if (flag == 0) {
        printf("\nNo deadlock\n");
    }
}
