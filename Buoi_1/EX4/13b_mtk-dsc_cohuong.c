#include <stdio.h>

#define MAX_M 500
typedef struct {
	int u, v;
} Edge;
typedef struct {
	int n, m;     
	Edge edges[MAX_M];
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}


void add_edge(Graph *pG, int u, int v){
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	
	pG->m++;
}

int main(){
	Graph G;
	int n;
	scanf("%d", &n);
	init_graph(&G, n);
	
	int mtk[n][n];
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			int temp;
			scanf("%d", &temp);
			mtk[i][j]=temp;
		}
	}

	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			for(int k=1;k<=mtk[i][j];++k){
				add_edge(&G, i, j);
			}
		}
	}
	
	for(int i=0;i<G.m;++i){
		printf("%d %d\n", G.edges[i].u, G.edges[i].v);
	}
	return 0;
}


