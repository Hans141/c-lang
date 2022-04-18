#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#define Max 100
typedef int elementtype;
typedef struct
{
    elementtype data[100];
    int rear;
    int front;
}Queue;
void makeNullQueue(Queue *q);
int isEmpty(Queue q);
int fullQueue(Queue q);
void enQueue(Queue *q, elementtype value);
void deQueue(Queue *q, elementtype *value);
#endif // QUEUE_H_INCLUDED
