#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct process {
    int pid, size;
} ps[MAX];

struct block {
    int bid, size;
    struct process p;
} bs[MAX];

int main() {
    int pn, bn;

    printf("Enter the number of blocks: ");
    scanf("%d", &bn);

    for (int i = 0; i < bn; i++) {
        printf("Enter the block size of block %d: ", i + 1);
        scanf("%d", &bs[i].size);
        bs[i].p.pid = -1;
        bs[i].bid = i + 1;
    }

    printf("Enter the number of processes: ");
    scanf("%d", &pn);

    for (int i = 0; i < pn; i++) {
        printf("Enter the size of the process %d: ", i + 1);
        scanf("%d", &ps[i].size);
        ps[i].pid = i + 1;
    }

    for (int i = 0; i < pn; i++) {
        int sizeDiff = -1, worstBIndex = -1;
        
        for (int j = 0; j < bn; j++) {
            if (bs[j].p.pid == -1 && bs[j].size >= ps[i].size
                && (sizeDiff == -1 || bs[j].size - ps[i].size > sizeDiff)) {
                sizeDiff = bs[j].size - ps[i].size;
                worstBIndex = j;
            }
        }
        
        if (worstBIndex >= 0) {
            bs[worstBIndex].p = ps[i]; 
        }
    }

    printf("\nWORST FIT\n");
    for (int i = 0; i < bn; i++) {
        printf("b%d [ %d ] <= ", bs[i].bid, bs[i].size);
        if (bs[i].p.pid != -1)
            printf("p%d [ %d ]\n", bs[i].p.pid, bs[i].p.size);
        else 
            printf("X\n");
    }
    printf("\n");

    return 0;
}
