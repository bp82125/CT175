#include <stdio.h>

#define MAX_M 500

typedef struct Edge{
	int u,v;
}Edge;

typedef struct Graph{
	int n,m;
	Edge edges[MAX_M];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

void add_edge(Graph *pG, int u, int v){
	if(u < 1 || u > pG->n) return;
	if(v < 1 || v > pG->n) return;
	
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	
	pG->m++;
}

int degree(Graph *pG, int u){
	int deg_u = 0;
	
	for(int i=0;i<pG->m;++i){
		if(pG->edges[i].u == u){
			deg_u++;
		}
		if(pG->edges[i].v == u){
			deg_u++;
		}
	}
	
	return deg_u;
}

int main(){
	Graph G;
	int n, m, u, v;
	
	scanf("%d%d", &n, &m);
	init_graph(&G,n);
	
	for(int i=0;i<m;++i){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for(int i=1;i<=n;++i){
		printf("deg(%d) = %d\n", i, degree(&G, i));
	}
	
	return 0;
}
