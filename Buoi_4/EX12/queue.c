#include <stdio.h>

#define ElementType int

#define MAX_Q 100

typedef struct Queue{
	int front, rear;
	ElementType data[MAX_Q];
}Queue;

void make_null_queue(Queue *pQ){
	pQ->rear = -1;
	pQ->front = 0;
}

void enqueue(Queue *pQ, ElementType x){
	pQ->rear++;
	pQ->data[pQ->rear] = x;
}

void dequeue(Queue *pQ){
	pQ->front++;
}

ElementType front(Queue *pQ){
	return pQ->data[pQ->front];
}

int empty(Queue *pQ){
	return pQ->front > pQ->rear;
}
