#include "queue.h"
#include <stdio.h>
void makeNullQueue(Queue *q)
{
    q->rear = -1;
    q->front = -1;
}
int isEmpty(Queue q)
{
    return q.rear == -1;
}
int fullQueue(Queue q)
{
    return (q.rear - q.front + 1) == Max;
}
void enQueue(Queue *q, elementtype value)
{
    if(!fullQueue(*q))
    {
        if(isEmpty(*q))
        {
            q->front = 0;
        }
        q->rear++;
        q->data[q->rear] = value;
    }
    else
    {
        printf("Queue is full!\n");
    }
}
void deQueue(Queue *q, elementtype *value)
{
    if(!isEmpty(*q))
    {
        *value = q->data[q->front];
        q->front++;
        if(q->front > q->rear)
        {
            makeNullQueue(q);
        }
    }
    else
    {
        printf("Queue is empty!\n");
    }
}
