#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, head, totalSeekTime = 0;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];

    printf("Enter the current head position: ");
    scanf("%d", &head);

    printf("Enter the disk requests: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    for (i = 0; i < n; i++) {
        totalSeekTime += abs(head - requests[i]);
        head = requests[i];
    }

    printf("Total seek time using FCFS: %d\n", totalSeekTime);
}

/*
Sample Input:
Enter the number of disk requests: 5
Enter the current head position: 50
Enter the disk requests: 98 183 37 122 14
*/
