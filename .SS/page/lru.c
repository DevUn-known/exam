#include <stdio.h>
#include <stdlib.h>

int find(int no_of_frames, int *frames, int tofound)
{
    int index = -1;
    for (int i = 0; i < no_of_frames; i++)
    {
        if (frames[i] == tofound)
        {
            index = i;
        }
    }
    return index;
}

int traverse(int no_of_pages, int *pageString, int i, int tofound)
{
    int index = -1;
    for (int j = i - 1; j >= 0; j--)
    {
        if (pageString[j] == tofound)
        {
            return j;
        }
    }
    return index;
}

int find_LRU(int *pageString, int i, int no_of_pages, int no_of_frames, int *frames)
{
    int *flag;
    flag = (int *)calloc(no_of_frames, sizeof(int));
    for (int j = 0; j < no_of_frames; j++)
    {
        flag[j] = 0;
    }
    int index = -1;
    int idx = -1;
    int min = no_of_pages;

    for (int j = 0; j < no_of_frames; j++)
    {
        idx = traverse(no_of_pages, pageString, i, frames[j]);
        if (idx != -1)
        {
            if (idx < min)
            {
                min = idx;
                index = j;
            }
            flag[j] = 1;
        }
    }
    free(flag);
    return index;
}

void main()
{
    int no_of_frames, no_of_pages, i, index = 0, no_of_page_faults = 0, no_of_page_hits = 0, idx, count = 0;

    printf("Enter the no of frames: ");
    scanf("%d", &no_of_frames);

    printf("Enter the size of Reference String: ");
    scanf("%d", &no_of_pages);

    printf("Enter the Reference String: ");
    int *refStr;
    refStr = (int *)calloc(no_of_pages, sizeof(int));
    for (i = 0; i < no_of_pages; i++)
    {
        scanf("%d", &refStr[i]);
    }

    int *frames;
    frames = (int *)calloc(no_of_frames, sizeof(int));
    for (i = 0; i < no_of_frames; i++)
    {
        frames[i] = -1;
    }

    for (i = 0; i < no_of_pages; i++)
    {
        if (count < no_of_frames)
        {
            idx = find(no_of_frames, frames, refStr[i]);
            if (idx != -1)
            {
                printf("Found page %d at frame %d\n", refStr[i], idx + 1);
            }
            else
            {
                frames[count] = refStr[i];
                printf("Page Miss : Storing Page %d in Frame %d\n", refStr[i], count + 1);
                count++;
                no_of_page_faults++;
            }
        }
        else
        {
            idx = find(no_of_frames, frames, refStr[i]);
            if (idx != -1)
            {
                printf("Found page %d at frame %d\n", refStr[i], idx + 1);
            }
            else
            {
                index = find_LRU(refStr, i, no_of_pages, no_of_frames, frames);
                printf("Page Miss : Storing Page %d in Frame %d\n", refStr[i], index + 1);
                no_of_page_faults++;
                frames[index] = refStr[i];
            }
        }
    }

    printf("The total number of page faults are : %d\n", no_of_page_faults);

    free(refStr);
    free(frames);
}

/*
Sample Input:
Enter the no of frames: 3
Enter the size of Reference String: 12
Enter the Reference String: 7 0 1 2 0 3 0 4 2 3 0 3
*/
