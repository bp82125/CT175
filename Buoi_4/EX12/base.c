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
	
	for(int i = 1; i <= n ;++i){
		for(int j = 1; j<=n;++j){
			if(adjacent(&G, i, j)){
				printf("%d %d\n", i, j);
			}
		}
	}
	
	for(int u = 1; u<=n;++u){
		printf("in-deg[%d] = %d\n", u, deg_in(&G, u));
	}
	
	return 0;
}

