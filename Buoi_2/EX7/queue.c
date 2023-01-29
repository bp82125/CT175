#define MAX_SIZE 500

typedef int ElementType;
typedef struct Queue {
	ElementType data[MAX_SIZE];
	int front, rear;
} Queue;

void make_null_queue(Queue *pQ) {
	pQ->front = 0;
	pQ->rear = -1;
}

void enqueue(Queue *pQ, ElementType u) {
	pQ->rear++;
	pQ->data[pQ->rear] = u;
}

ElementType front(Queue *pQ) {
	return pQ->data[pQ->front];
}

void dequeue(Queue *pQ) {
	pQ->front++;
}

int empty(Queue *pQ) {
	return pQ->front > pQ->rear;
}
