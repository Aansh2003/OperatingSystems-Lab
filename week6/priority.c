// Priority Scheduling algorithm

#include<stdio.h>
#include <stdlib.h>

//Struct definitions

typedef struct{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
} Job;

typedef struct{
    Job *arr;
    int rear;
} queue;

// HeapSort functions

void swap(Job* a, Job* b)
{
    Job temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Job *arr, int N, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N && arr[left].priority < arr[largest].priority) 
        largest = left;

    if (right < N && arr[right].priority < arr[largest].priority)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, N, largest);
    }
}

void heapSort(Job *arr, int N)
{
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);

    for (int i = N - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}


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

    heapSort(q->arr,q->rear);
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

//Driver code

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
        printf("Enter priority: ");
        scanf("%d",&arr[i].priority);
        arr[i].id = i+1;
    }

    queue job_queue = q_create();

    int job_complete = 0;
    int time = 0;

    int jobs[1000];
    int count = 0;
    
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
            jobs[count] = q_top(&job_queue)->id;
            job_complete += q_decrement(&job_queue);
            count++;
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