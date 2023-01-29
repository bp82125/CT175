#include <stdio.h>

#define MAX_SIZE 500

typedef struct ElementType{
	int u,p;	
}ElementType;

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

#define MAX_VERTICES 100

typedef struct {
	int n;
	int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

void init_graph(Graph *pG, int n){
	pG->n=n;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			pG->A[i][j]=0;
		}
	}
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v]++;
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0;
}

void print_adjacent(Graph *pG, int u){
	printf("adjacent[%d] = ", u);
	for(int v = 1; v<=pG->n;++v){
		if(adjacent(pG, u, v)){
			printf("%d ", v);
		}
	}
	printf("\n");
}

void bfs(Graph *pG, int a, int mark[], int parent[]){
	Queue Q;
	make_null_queue(&Q);
	
	ElementType pair;
	pair.u = a;
	pair.p = -1;
	
	enqueue(&Q, pair);
	
	while(!empty(&Q)){
		ElementType pair = front(&Q);
		int u = pair.u;
		int p = pair.p;
		
		dequeue(&Q);
		
		if(mark[u]==1){
			continue;
		}
		
		mark[u]=1;
		parent[u] = p;
		
		for(int i=1;i<=pG->n;++i){
			if(adjacent(pG, u, i)){
				pair.u = i;
				pair.p = u;
				enqueue(&Q, pair);
			}
		}
	}
}

int main(void){
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	int mark[n], parent[n];
	for(int i=1;i<=n;++i){
		mark[i] = 0;
		parent[i]=0;
	}
	
	for(int i=1;i<=n;++i){
		if(mark[i]==0){
			bfs(&G, i, mark, parent);	
		}	
	}
	
	for(int i = 1; i<=n;++i){
		printf("%d %d\n", i, parent[i]);
	}
	
	return 0;
}
