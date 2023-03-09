#include <stdio.h>
#include "queue.c"
#include "list.c"

#define MAX_VERTICES 100

typedef struct Graph{
	int n, m;
	int A[MAX_VERTICES][MAX_VERTICES];
}Graph;

void init_graph(Graph *pG, int n){
	pG->m++;
	pG->n = n;
	
	for(int i = 0; i < n ;++i){
		for(int j = 0; j<n;++j){
			pG->A[i][j] = 0;
		}
	}
}

void add_edges(Graph *pG, int u, int v){
	pG->A[u][v]++;
	pG->m++;
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0;
}

int deg_in(Graph *pG, int u){
	int deg = 0;
	for(int v = 1; v <= pG->n; ++v){
		deg += pG->A[v][u];
	}
	return deg;
}

int d[MAX_VERTICES];

void TopoSort(Graph *pG, List *pL){
	
	for(int u = 1; u<=pG->n;++u){
		d[u] = deg_in(pG, u);
	}
	
	Queue Q;
	make_null_queue(&Q);
	
	for(int u = 1; u<=pG->n;++u){
		if(d[u]==0){
			enqueue(&Q, u);
			
		}
	}
	
	while(!empty(&Q)){
		int u = front(&Q);
		dequeue(&Q);
		push_back(pL, u);
		
		for(int v = 1; v<=pG->n;++v){
			if(adjacent(pG, u, v)){
				d[v]--;
				if(d[v] == 0){
					enqueue(&Q, v);
				}
			}
		}
	}
}

int main(void){
	Graph G;
	freopen("dt.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for(int i = 0; i<m;++i){
		int u, v;
		scanf("%d%d", &u, &v);
		add_edges(&G, u, v);
	}
	
//	for(int i = 1; i <= n ;++i){
//		for(int j = 1; j<=n;++j){
//			if(adjacent(&G, i, j)){
//				printf("%d %d\n", i, j);
//			}
//		}
//	}
	
	List L;
	make_null(&L);
	
	TopoSort(&G, &L);
	
	for(int i = 0; i<L.size;++i){
		printf("%d ", L.data[i]);
	}
	
	return 0;
}

