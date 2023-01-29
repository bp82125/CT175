#include <stdio.h>
#include "queue.c"

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
	pG->A[v][u]++;
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0 && pG->A[v][u] > 0;
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

void bfs(Graph *pG, int n, int mark[]){
	Queue Q;
	make_null_queue(&Q);
	
	enqueue(&Q, n);
	
	while(!empty(&Q)){
		int u = front(&Q);
		dequeue(&Q);
		
		if(mark[u]==1){
			continue;
		}
		
		printf("%d\n", u);
		mark[u] = 1;
		
		for(int i = 1; i <= pG->n;++i){
			if(adjacent(pG, u, i)){
				enqueue(&Q, i);
			}
		}
	}
}

int main(void){
	freopen("dt_s.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	int mark[n];
	for(int i=1;i<=n;++i){
		mark[i]=0;
	}
	
	int s;
	scanf("%d", &s);
	
	bfs(&G, s, mark);
	
	return 0;
	
}
