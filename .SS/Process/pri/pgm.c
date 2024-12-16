#include <stdio.h>

#define MAX 20

struct process {
    int pid, st, at, bt, priority, wt, ct, tat, completed;
} ps[MAX];

int main() {
    int n, totTat = 0, totWt = 0, rt = 0;
    printf("Enter the number of processes to schedule: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++){
        ps[i].pid = i+1;
        printf("Enter arrival time, burst time and priority respectively of process %d: ", i+1);
        scanf("%d %d %d", &ps[i].at, &ps[i].bt, &ps[i].priority);
        ps[i].st = 0, ps[i].wt = 0, ps[i].ct = 0, ps[i].tat = 0, ps[i].completed = 0;
    }
    
    for (int i = n-1; i > 0; i--)
        for (int j = 0; j < i; j++)
            if (ps[j].at > ps[j+1].at){
                struct process temp = ps[j];
                ps[j] = ps[j+1];
                ps[j+1] = temp;
            }

    int index = 0;
    while (1){
        for (;ps[index].completed == 1; index++);
        if (index == n) break;
        if (ps[index].at > rt) rt = ps[index].at;
        int hp = index;
        for (int i = index + 1; i < n && ps[i].at <= rt; i++)
            if (!ps[i].completed)
                if (ps[i].priority > ps[hp].priority) hp = i;
        ps[hp].st = rt;
        rt += ps[hp].bt;
        ps[hp].ct = rt;
        ps[hp].tat = rt - ps[hp].at;
        ps[hp].wt = ps[hp].tat - ps[hp].bt;
        ps[hp].completed = 1;
        totTat += ps[hp].tat, totWt += ps[hp].wt;
    }

    for (int i = n-1; i > 0; i--)
        for (int j = 0; j < i; j++)
            if (ps[j].st > ps[j+1].st){
                struct process temp = ps[j];
                ps[j] = ps[j+1];
                ps[j+1] = temp;
            }
    
    printf("\n\nTable:\n\n");
    printf("Process | AT | BT | CT | TAT | WT | Priority\n");
    printf("--------|----|----|----|-----|----|----------\n");
    for (int i = 0; i < n; i++){
        struct process p = ps[i];
        printf("  P%d    | %s%d | %s%d | %s%d | %s%d  | %s%d |    %d\n", p.pid,
               p.at<10?"0":"", p.at, p.bt<10?"0":"", p.bt, p.ct<10?"0":"", p.ct,
               p.tat<10?"0":"", p.tat, p.wt<10?"0":"", p.wt, p.priority);
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
    for (int i = 0; i < n; i++){
        int st;
        if (i == 0) st = ps[i].at;
        else st = ps[i-1].ct > ps[i].at? ps[i-1].ct : ps[i].at;
        printf("%s%d  %s%d|", st<10? "0" : "", st, ps[i].ct<10? "0" : "", ps[i].ct);
    }
    printf("\n");
}
