// First come first serve Scheduling algorithm

#include<stdio.h>

typedef struct{
    int id;
    int arrival_time;
    int burst_time;
} Job;

void sort(Job arr[],int size)
{
    for(int i=0;i<size-1;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(arr[j].arrival_time>arr[j+1].arrival_time)
            {
                Job temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main()
{
    int job_count;
    printf("Enter the number of jobs: ");
    scanf("%d",&job_count);
    Job arr[job_count];
    for(int i=0;i<job_count;i++)
    {
        printf("Job %d\n",i+1);
        printf("Enter arrival time: ");
        scanf("%d",&arr[i].arrival_time);
        printf("Enter burst time: ");
        scanf("%d",&arr[i].burst_time);
        arr[i].id = i+1;
    }

    sort(arr,job_count);

    int time = 0;

    printf("\nSchedule: \n");

    for(int i=0;i<job_count;i++)
    {
        if(arr[i].arrival_time > time)
        {
            printf("Idle(%d-%d)\n",time,arr[i].arrival_time);
            time += arr[i].arrival_time;
        }
        printf("Job %d (%d-%d)\n",arr[i].id,time,time+arr[i].burst_time);
        time += arr[i].burst_time;
    }
}