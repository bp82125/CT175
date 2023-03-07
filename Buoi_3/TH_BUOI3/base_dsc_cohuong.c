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
		if(pG->edges[i].u == u && pG->edges[i].v == v){
			return pG->edges[i].weight > 0;
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
	
	for(int i = 0; i<G.m;++i){
		printf("%d %d %d\n", G.edges[i].u, G.edges[i].v, G.edges[i].weight);
	}
	
	printf("adjacent %d and %d: %d\n", 1, 2, adjacent(&G, 1 , 2));
	printf("adjacent %d and %d: %d\n", 1, 3, adjacent(&G, 1 , 4));
	
	return 0;
}
