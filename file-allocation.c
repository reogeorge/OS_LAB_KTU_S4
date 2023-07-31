#include <stdio.h>
#include <stdlib.h>

typedef struct block {
    int block_no;
    struct block* next;
} block;

typedef struct {
    int start_block;
    int length;
    block* list; // list of blocks allocated to this process
} file;

void sequentialAllocation(int n) {
    int blocks[100];
    for (int i = 0; i < n; i++) {
        blocks[i] = 0;
    }
    int flag = 0;
    do {
        int b;
        printf("\nInput file starting block: ");
        scanf("%d", &b);
        int len;
        printf("Input file length: ");
        scanf("%d", &len);
        if ((b + len - 1) > (n - 1)) {
            printf("\nFile cannot be allocated to disk!");
        } else {
            int flag = 0;
            for (int i = b; i < (b + len); i++) {
                if (blocks[i] == 1) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                printf("\nBlocks allocated to this file: ");
                for (int i = b; i < (b + len); i++) {
                    printf("%d ", i);
                    blocks[i] = 1;
                }
            } else {
                printf("\nFile cannot be allocated to disk!");
            }
        }
        printf("\n0 - Continue, 1 - Exit: ");
        scanf("%d", &flag);
    } while (flag != 1);
}

void linkedAllocation(int n) {
    int blocks[100];
    for (int i = 0; i < n; i++) {
        blocks[i] = 0;
    }
    int flag = 0;
    do {
        file* ptr = (file*)malloc(sizeof(file));
        printf("\nInput file starting block: ");
        scanf("%d", &(ptr->start_block));
        printf("Input file length: ");
        scanf("%d", &(ptr->length));
        if (blocks[ptr->start_block] == 1) {
            printf("\nStarting block already allocated! - Allocation not possible");
        } else {
            block* b = (block*)malloc(sizeof(block));
            b->block_no = ptr->start_block;
            b->next = NULL;
            ptr->list = b;
            blocks[ptr->start_block] = 1;
            int count = 1;
            int i;
            for (i = 0; (i < n) && (count < ptr->length); i++) {
                if (blocks[i] == 0) {
                    block* new_block = (block*)malloc(sizeof(block));
                    new_block->block_no = i;
                    new_block->next = NULL;
                    block* p = ptr->list;
                    while (p->next != NULL) {
                        p = p->next;
                    }
                    p->next = new_block;
                    count++;
                    blocks[i] = 1;
                }
            }
            if (i == n && count < ptr->length) {
                printf("\nAllocation not possible - Insufficient storage!");
            } else {
                printf("\nFile allocated to disk");
                printf("\nLinked list of blocks allocated to this file: ");
                block* p = ptr->list;
                while (p->next != NULL) {
                    printf("%d->", p->block_no);
                    p = p->next;
                }
                printf("%d ", p->block_no);
            }
        }
        printf("\n0 - Continue, 1 - Exit: ");
        scanf("%d", &flag);
    } while (flag != 1);
}

void indexedAllocation(int n) {
    int* blocks = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        blocks[i] = 0;
    }
    int flag = 0;
    do {
        int index;
        printf("\nInput file index block number: ");
        scanf("%d", &index);
        if (blocks[index] == 1) {
            printf("\nIndex block already allocated! - No allocation possible");
        } else {
            int length;
            printf("Input file length: ");
            scanf("%d", &length);
            int count = 0;
            blocks[index] = 1;
            int index_block[100];
            for (int i = 0; (i < n) && (count < length); i++) {
                if (blocks[i] == 0) {
                    blocks[i] = 1;
                    index_block[count] = i;
                    count++;
                }
            }
            if (count < length) {
                printf("\nInsufficient storage - No allocation");
                for (int i = 0; i < count; i++) {
                    blocks[index_block[i]] = 0;
                }
                blocks[index] = 0;
            } else {
                printf("\nFile allocated to disk with index block %d\n", index);
                for (int i = 0; i < count; i++) {
                    printf("%d->%d\n", index, index_block[i]);
                }
            }
        }
        printf("\n0 - Continue, 1 - Exit: ");
        scanf("%d", &flag);
    } while (flag != 1);
}

int main() {
    int n;
    printf("\nInput the number of blocks: ");
    scanf("%d", &n);
    int option;
    do {
        printf("\n\nChoose the file allocation type: ");
        printf("\n1. Sequential Allocation");
        printf("\n2. Linked Allocation");
        printf("\n3. Indexed Allocation");
        printf("\n0. Exit");
        printf("\n\nOption: ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                sequentialAllocation(n);
                break;
            case 2:
                linkedAllocation(n);
                break;
            case 3:
                indexedAllocation(n);
                break;
            case 0:
                printf("\nExiting program...\n");
                break;
            default:
                printf("\nInvalid option! Please try again.\n");
                break;
        }
    } while (option != 0);
    return 0;
}
