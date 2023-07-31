#include <stdio.h>
#include <stdlib.h>

// Structure to represent a memory partition
struct partition {
    int id;
    int size;
    int allocated; // 0 for unallocated, 1 for allocated
};

// Structure to represent a process
struct process {
    int id;
    int size;
};

// Function to allocate memory using the Best Fit algorithm
void best_fit(struct partition *partitions, int num_partitions, struct process *processes, int num_processes) {
    int i, j, best_partition;
    for (i = 0; i < num_processes; i++) {
        best_partition = -1;
        for (j = 0; j < num_partitions; j++) {
            if (partitions[j].allocated == 0 && partitions[j].size >= processes[i].size) {
                if (best_partition == -1 || partitions[j].size < partitions[best_partition].size) {
                    best_partition = j;
                }
            }
        }
        if (best_partition != -1) {
            partitions[best_partition].allocated = 1;
            partitions[best_partition].id = processes[i].id;
        }
    }
}

// Function to allocate memory using the Worst Fit algorithm
void worst_fit(struct partition *partitions, int num_partitions, struct process *processes, int num_processes) {
    int i, j, worst_partition;
    for (i = 0; i < num_processes; i++) {
        worst_partition = -1;
        for (j = 0; j < num_partitions; j++) {
            if (partitions[j].allocated == 0 && partitions[j].size >= processes[i].size) {
                if (worst_partition == -1 || partitions[j].size > partitions[worst_partition].size) {
                    worst_partition = j;
                }
            }
        }
        if (worst_partition != -1) {
            partitions[worst_partition].allocated = 1;
            partitions[worst_partition].id = processes[i].id;
        }
    }
}

// Function to allocate memory using the First Fit algorithm
void first_fit(struct partition *partitions, int num_partitions, struct process *processes, int num_processes) {
    int i, j;
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_partitions; j++) {
            if (partitions[j].allocated == 0 && partitions[j].size >= processes[i].size) {
                partitions[j].allocated = 1;
                partitions[j].id = processes[i].id;
                break;
            }
        }
    }
}

int main() {
    int num_partitions, num_processes, choice;
    while (1) {
        printf("\nChoose the memory allocation algorithm:\n");
        printf(" 1. Best Fit\n");
        printf(" 2. Worst Fit\n");
        printf(" 3. First Fit\n");
        printf(" 4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4)
            return 0;

        printf("\nEnter the number of partitions: ");
        scanf("%d", &num_partitions);
        struct partition *partitions = (struct partition *)malloc(num_partitions * sizeof(struct partition));

        printf("\nEnter the size of each partition:\n");
        int i;
        for (i = 0; i < num_partitions; i++) {
            printf("Partition %d: ", i + 1);
            scanf("%d", &partitions[i].size);
            partitions[i].id = -1;
            partitions[i].allocated = 0;
        }

        printf("\nEnter the number of processes: ");
        scanf("%d", &num_processes);
        struct process *processes = (struct process *)malloc(num_processes * sizeof(struct process));

        printf("Enter the size of each process:\n");
        for (i = 0; i < num_processes; i++) {
            printf("Process %d: ", i + 1);
            scanf("%d", &processes[i].size);
            processes[i].id = i + 1;
        }

        switch (choice) {
            case 1:
                best_fit(partitions, num_partitions, processes, num_processes);
                break;
            case 2:
                worst_fit(partitions, num_partitions, processes, num_processes);
                break;
            case 3:
                first_fit(partitions, num_partitions, processes, num_processes);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice!\n");
                exit(1);
        }

        printf("\nAllocation state:\n");
        for (i = 0; i < num_partitions; i++) {
            printf("Partition %d: ", i + 1);
            if (partitions[i].allocated == 1) {
                printf("Process %d\n", partitions[i].id);
            } else {
                printf("Unallocated\n");
            }
        }
        printf("\n");

        free(partitions);
        free(processes);
    }
}
