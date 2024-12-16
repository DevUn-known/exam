#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, totalSeekTime = 0;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];

    printf("Enter the current head position: ");
    scanf("%d", &head);

    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int index = 0;
    for (; index < n && requests[index] < head; index++);

    for (int i = index; i < n; i++) {
        totalSeekTime += abs(head - requests[i]);
        head = requests[i];
        printf("%d ", head);
    }

    if (index > 0) {
        totalSeekTime += abs(head - 0);
        head = 0;

        for (int i = 0; i < index; i++) {
            totalSeekTime += abs(head - requests[i]);
            head = requests[i];
            printf("%d ", head);
        }
    }

    printf("\nTotal seek time using C-SCAN: %d\n", totalSeekTime);
}

/*
Sample Input:
Enter the number of disk requests: 5
Enter the current head position: 50
Enter the disk requests: 98 183 37 122 14
*/
