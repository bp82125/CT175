#include <stdio.h>

#define MAX_N 100

typedef struct Edge{
	int u, v;
	int weight;
}Edge;

typedef struct Graph{
	int n, m;
	Edge edges[MAX_N];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

void add_edges(Graph *pG, int u, int v, int w){
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	pG->edges[pG->m].weight = w;
	
	pG->m++;
}

int adjacent(Graph *pG, int u, int v){
	for(int i=0;i<pG->m;++i){
		if((pG->edges[i].u == u && pG->edges[i].v == v) ||(pG->edges[i].u == v && pG->edges[i].v == u)){
			return 1;
		}
	}
	return 0;
}

int main(void){
	freopen("dt.txt", "r", stdin);
	
	Graph G;
	
	int n,m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for(int i = 0;i<m;++i){
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edges(&G, u,v,w);
	}

	return 0;
}
