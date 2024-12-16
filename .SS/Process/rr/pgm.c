#include <stdio.h>

#define MAX 100

struct process {
    int pid, at, bt, ct, tat, wt, rt, st, completed;
} p[MAX], chart[MAX];

void main() {
    int n, q, top = 0, totTAT = 0, totWT = 0, clk = 0;

    printf("Enter time quantum: ");
    scanf("%d", &q);
    printf("Enter the number of processes to schedule: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter the at & bt of process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
        p[i].completed = 0;
        p[i].rt = p[i].bt;
    }

    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (p[j].at > p[j + 1].at) {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int index = 0;
    while (1) {
        for (; index < n && p[index].completed; index++);
        if (index == n) break;

        if (p[index].at > clk) clk = p[index].at;

        for (int i = index; i < n && p[i].at <= clk; i++) {
            if (p[i].completed) continue;

            chart[top].st = clk;
            chart[top].pid = p[i].pid;

            if (p[i].rt <= q) {
                clk += p[i].rt;
                p[i].completed = 1;
                p[i].ct = clk;
                p[i].tat = p[i].ct - p[i].at;
                p[i].wt = p[i].tat - p[i].bt;
                totTAT += p[i].tat;
                totWT += p[i].wt;
            } else {
                clk += q;
                p[i].rt -= q;
            }

            chart[top++].ct = clk;
        }
    }

    for (int i = top - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (chart[j].ct > chart[j + 1].ct) {
                struct process temp = chart[j];
                chart[j] = chart[j + 1];
                chart[j + 1] = temp;
            }
        }
    }

    printf("\nPID\t AT\t BT\t CT\t TAT\t WT\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t %d \t %d \t %d \t %d \t %d\n",
            p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nGhantt chart:\n\n");

    if (chart[0].st > 0)
        printf("x\t|%d\t|", chart[0].pid);
    else
        printf("%d\t|", chart[0].pid);

    for (int i = 1; i < top; i++)
        printf("%d\t|", chart[i].pid);

    printf("\n");

    if (chart[0].st > 0)
        printf("0\t%d\t%d\t", chart[0].st, chart[0].ct);
    else
        printf("0\t%d\t", chart[0].ct);

    for (int i = 1; i < top; i++)
        printf("%d\t", chart[i].ct);

    printf("\n\n");

    printf("AVG TAT: %f\nAVG WT: %f\n", (float)totTAT / n, (float)totWT / n);
}
