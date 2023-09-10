// Round robbing scheduling algorithm

#include<stdio.h>
#include <stdlib.h>

//Struct definitions

typedef struct{
    int id;
    int arrival_time;
    int burst_time;
} Job;

typedef struct{
    Job *arr;
    int rear;
} queue;


// Queue functions

queue q_create()
{
    queue new;
    Job* queue_job = (Job*)malloc(100*sizeof(Job));
    new.rear = 0;
    new.arr = queue_job;
    return new;
}

void q_insert(queue *q,Job new_job)
{
    q->arr[q->rear] = new_job;
    q->rear++;
}

int q_empty(queue *q)
{
    if(q->rear==0)
        return 1;
    return 0;
}

void q_pop(queue *q)
{
    if(q_empty(q)==1)
        return;
    Job *new = (Job*)malloc(100*sizeof(Job));
    for(int i=1;i<=q->rear;i++)
    {
        new[i-1] = q->arr[i];
    }
    q->arr = new;
    q->rear--;
}

Job* q_top(queue *q)
{
    if(!q_empty(q))
        return q->arr;
}

int q_decrement(queue *q)
{
    if(q_empty(q))
        return 0;
    q_top(q)->burst_time--;
    if(q_top(q)->burst_time==0)
    {
        q_pop(q);
        return 1;
    }
    return 0;
}

int q_switch(queue *q)
{
    Job* top = q_top(q);
    q_pop(q);
    q_insert(q,*top);
}

int main()
{
    int job_count;
    int quantum;
    printf("Enter quantum value: ");
    scanf("%d",&quantum);
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

    queue job_queue = q_create();

    int job_complete = 0;
    int time = 0;

    int jobs[1000];
    int count = 0;
    
    int count_quanta;

    while(job_complete!=job_count)
    {
        for(int i=0;i<job_count;i++)
        {
            if(arr[i].arrival_time == time)
            {
                q_insert(&job_queue,arr[i]);
            }
        }

        if(q_empty(&job_queue))
        {
            jobs[count] = 0;
            count++;
        }
        else
        {
            if(count_quanta>=quantum)
            {
                q_switch(&job_queue);
                count_quanta = 0;
            }
            jobs[count] = q_top(&job_queue)->id;
            int complete = 0;
            complete += q_decrement(&job_queue);
            if(complete == 1)
                count_quanta = 0;
            job_complete += complete;
            count++;
            count_quanta++;
        }
        time++;
    }

    int start = 0;
    int running_time = 1;

    printf("Scheduled order:\n");
    for(int i=0;i<count-1;i++)
    {
        if(jobs[i] != jobs[i+1])
        {
            if(jobs[i]==0)
                printf("Idle: %d-%d\n",start,start+running_time);
            else
                printf("Job %d: %d-%d\n",jobs[i],start,start+running_time);
            start += running_time;
            running_time = 0;
        }
        running_time += 1;
    }
    printf("Job %d: %d-%d\n",jobs[count-1],start,start+running_time);
}