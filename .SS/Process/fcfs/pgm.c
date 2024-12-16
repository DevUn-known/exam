#include <stdio.h>

#define MAX 20

struct process {
    int pid, at, bt, wt, ct, tat;
} ps[MAX];

int main() {
    int n, totTat = 0, totWt = 0;
    printf("Enter the number of processes to schedule: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        ps[i].pid = i;
        printf("Enter arrival time and burst time respectively of process %d: ", i);
        scanf("%d %d", &ps[i].at, &ps[i].bt);
    }
    
    for (int i = n-1; i > 0; i--)
        for (int j = 0; j < i; j++)
            if (ps[j].at > ps[j+1].at) {
                struct process temp = ps[j];
                ps[j] = ps[j+1];
                ps[j+1] = temp;
            }
    
    ps[0].ct = ps[0].at + ps[0].bt;
    ps[0].wt = 0;
    ps[0].tat = ps[0].bt;
    totTat += ps[0].tat;
    totWt += ps[0].wt;
    
    for (int i = 1; i < n; i++) {
        if (ps[i-1].ct > ps[i].at)
            ps[i].ct = ps[i-1].ct + ps[i].bt;
        else
            ps[i].ct = ps[i].at + ps[i].bt;
        
        ps[i].tat = ps[i].ct - ps[i].at;
        ps[i].wt = ps[i].tat - ps[i].bt;
        totTat += ps[i].tat;
        totWt += ps[i].wt;
    }
    
    printf("\n\nTable:\n\n");
    printf("Process | AT | BT | CT | TAT | WT\n");
    printf("--------|----|----|----|-----|----\n");
    for (int i = 0; i < n; i++) {
        struct process p = ps[i];
        printf("  P%d    | %s%d | %s%d | %s%d | %s%d  | %d\n", p.pid,
               p.at<10?"0":"", p.at, p.bt<10?"0":"", p.bt, p.ct<10?"0":"", p.ct,
               p.tat<10?"0":"", p.tat, p.wt);
    }
    printf("\n\nAvg TAT = %f\nAvg WT = %f\n", (float) totTat / n, (float) totWt / n);
    
    printf("\nGhantt chart:\n\n");
    printf(" %s", ps[0].at != 0? " x |" : ""); 
    for (int i = 0; i < n; i++) {
        printf("  p%d  |", ps[i].pid);
    }
    printf("\n");
    
    printf(" %s", ps[0].at != 0? "___|" : "");
    for (int i = 0; i < n; i++) printf("______|");
    printf("\n");
    
    printf(" %s", ps[0].at != 0? "00 |" : "");
    for (int i = 0; i < n; i++) {
        int st; 
        if (i == 0) st = ps[i].at;
        else st = ps[i-1].ct > ps[i].at ? ps[i-1].ct : ps[i].at;
        printf("%s%d  %s%d|", st<10? "0" : "", st, ps[i].ct<10? "0" : "", ps[i].ct);
    }
    printf("\n");
}
