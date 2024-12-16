#include <stdio.h>
#include <stdlib.h>

int find(int no_of_frames, int *frames, int tofind) {
    int index = -1;
    for (int i = 0; i < no_of_frames; i++) {
        if (frames[i] == tofind) {
            index = i;
            break;
        }
    }
    return index;
}

void main() {
    int no_of_frames, no_of_pages;

    printf("Enter the number of frames: ");
    scanf("%d", &no_of_frames);

    printf("Enter the size of the reference string: ");
    scanf("%d", &no_of_pages);

    printf("Enter the Reference String: ");
    int *refStr = (int *)calloc(no_of_pages, sizeof(int));
    for (int i = 0; i < no_of_pages; i++) {
        scanf("%d", &refStr[i]);
    }

    int *frames = (int *)calloc(no_of_frames, sizeof(int));
    for (int i = 0; i < no_of_frames; i++) {
        frames[i] = -1;
    }

    int index = 0;
    int no_of_page_faults = 0;
    int no_of_page_hits = 0;
    int indx;
    int count = 0;

    for (int i = 0; i < no_of_pages; i++) {
        if (count < no_of_frames) {
            indx = find(no_of_frames, frames, refStr[i]);
            if (indx != -1) {
                no_of_page_hits++;
                printf("Page Hit: Found Page %d in frame %d\n", refStr[i], indx + 1);
            } else {
                frames[count] = refStr[i];
                printf("Page Miss: Storing Page %d in frame %d\n", refStr[i], count + 1);
                count++;
                no_of_page_faults++;
            }
        } else {
            indx = find(no_of_frames, frames, refStr[i]);
            if (indx != -1) {
                no_of_page_hits++;
                printf("Page Hit: Found Page %d in frame %d\n", refStr[i], indx + 1);
            } else {
                printf("Page Miss: Replacing Frame %d with page %d\n", index + 1, refStr[i]);
                no_of_page_faults++;
                frames[index] = refStr[i];
                index = (index + 1) % no_of_frames;
            }
        }
    }

    printf("\nThe total number of page faults are: %d\n", no_of_page_faults);
}

/*
Sample Input:
Enter the number of frames: 3
Enter the size of the reference string: 12
Enter the Reference String: 1 2 3 4 1 2 5 1 2 3 4 5
*/
