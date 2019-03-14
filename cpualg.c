#include<stdio.h>
void FCFS();
void SJF();
void priority_np();
void roundrobin();
int burstTime[10]={0}, process[10];
int wt[10]={0}, tat[10]={0};
int clock, n;
void main()
{
    int i;
    printf("Enter the no. of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter Burst Time of P%d: ", i);
        scanf("%d", &burstTime[i]);
        process[i] = i;
    }
    clock = 0;
    FCFS();
    clock = 0;
    SJF();
    clock = 0;
    roundrobin();
    clock = 0;
    priority_np();

}
void FCFS()
{
    int i, avg_tat = 0, avg_wt = 0;
    printf("\nFCFS\n");
    for (i = 0; i < n; i++)
    {
        clock = clock + burstTime[i];
        tat[i] = tat[i] + clock;
        printf("P%d\t", i);
    }
    printf("\nProcess\tWaiting\tTurnAround\n");
    for (i = 0; i < n; i++)
    {
        wt[i] = tat[i] - burstTime[i];
        avg_wt = avg_wt + wt[i];
        avg_tat = avg_tat + tat[i];
        printf("\nP%d\t%d\t%d", process[i], wt[i], tat[i]);
    }
    printf("\nAvg. Waiting Time: %d\nAvg. TurnAround Time: %d\n", avg_wt/n, avg_tat/n);
}

void SJF()
{
    int i, j, small, smallIndex = 0, temp, avg_wt = 0, avg_tat = 0;
    int burstCopy[10];
    printf("\nSJF\n");
    for (i = 0; i < n; i++)
    {
        burstCopy[i] = burstTime[i];
        tat[i] = 0;
    }
    //Sort the burst in ascending order
    for (i = 0; i < (n-1); i++)
    {
        small = burstCopy[i];
        smallIndex = i;
        for (j = i; j < n; j++)
        {
            if (small > burstCopy[j])
            {
                small = burstCopy[j];
                smallIndex = j;
            }
        }
        temp = burstCopy[i];
        burstCopy[i] = small;
        burstCopy[smallIndex] = temp;
        //sort process numbers also
        temp = process[i];
        process[i] = process[smallIndex];
        process[smallIndex] = temp;
        for (i = 0; i < n; i++)
        {
            clock = clock + burstCopy[i];
            tat[i] = tat[i] + clock;
            printf("P%d\t", process[i]);
        }
        printf("\nProcess\tWaiting\tTurnAround\n");
        for (i = 0; i < n; i++)
        {
            wt[i] = tat[i] - burstCopy[i];
            avg_wt = avg_wt + wt[i];
            avg_tat = avg_tat + tat[i];
            printf("\nP%d\t%d\t%d", process[i], wt[i], tat[i]);
        }
    }
    printf("\nAvg. Waiting Time: %d\nAvg. TurnAround Time: %d\n", avg_wt/n, avg_tat/n);
}
void priority_np()
{
    int i, j, small, smallIndex, temp, avg_wt = 0, avg_tat = 0;
    int burstCopy[10], priority[10];
    printf("\nPRIORITY\n");
    for (i = 0; i < n; i++)
    {
        printf("\nEnter priority of P%d: ",i);
        scanf("%d", &priority[i]);
        burstCopy[i] = burstTime[i];
        process[i] = i; //reset the process numbers
        tat[i] = 0;
    }
    //Sort the burst in ascending order of priority
    for (i = 0; i < (n-1); i++)
    {
        small = priority[i];
        smallIndex = i;
        for (j = (i+1); j < n; j++)
        {
            if (small > priority[j])
            {
                small = priority[j];
                smallIndex = j;
            }
        }
        temp = priority[i];
        priority[i] = priority[smallIndex] ;
        priority[smallIndex] = temp;
        //sort process numbers & burst time also
        temp = process[i];
        process[i] = process[smallIndex];
        process[smallIndex] = temp;
        temp = burstCopy[i];
        burstCopy[i] = burstCopy[smallIndex];
        burstCopy[smallIndex] = temp;
    }
    for (i = 0; i < n; i++)
    {
        clock = clock + burstCopy[i];
        tat[i] = tat[i] + clock;
        printf("P%d\t", process[i]);
    }
    printf("\nProcess\tWaiting\tTurnAround\n");
    for (i = 0; i < n; i++)
    {
        wt[i] = tat[i] - burstCopy[i];
        avg_wt = avg_wt + wt[i];
        avg_tat = avg_tat + tat[i];
        printf("\nP%d\t%d\t%d", process[i], wt[i], tat[i]);
    }
    printf("\nAvg. Waiting Time: %d\nAvg. TurnAround Time: %d\n", avg_wt/n, avg_tat/n);
}

void roundrobin()
{
    int i, burstCopy[10], avg_tat = 0, avg_wt = 0;
    int count = 0, quantum = 0;
    int flag[10] = {0};
    for (i = 0; i < n; i++)
    {
        burstCopy[i] = burstTime[i];
        process[i] = i;
        tat[i] = 0;
    }
    printf("Enter quantum: ");
    scanf("%d", &quantum);
    for (i = 0; i < n; i=(i+1)%n)
    {
        if (flag[i]==0)
        {
            if (burstCopy[i] <= quantum)
            {
                clock = clock + burstCopy[i];
                printf("P%d\t", i);
                burstCopy[i] = 0;
                flag[i] = 1;
                count++;
            }
            else
            {
                clock = clock + quantum;
                printf("P%d\t", i);
                burstCopy[i] = burstCopy[i] - quantum;
            }
                tat[i] = tat[i] + clock;
        }
        if (count == n)
        {
            break;
        }
    }
    printf("\nProcess\tWaiting\tTurnAround\n");
    for (i = 0; i < n; i++)
    {
        wt[i] = tat[i] - burstTime[i];
        avg_wt = avg_wt + wt[i];
        avg_tat = avg_tat + tat[i];
        printf("\nP%d\t%d\t%d", process[i], wt[i], tat[i]);
    }
    printf("\nAvg. Waiting Time: %d\nAvg. TurnAround Time: %d\n", avg_wt/n, avg_tat/n);
}
