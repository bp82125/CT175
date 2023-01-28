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
	for(int i=0;i<pG->m;++i){
		if(pG->edges[i].u == u && pG->edges[i].v == v){ //truong hop da ton tai cung trong do thi
			return;
		}
	}
	
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	
	pG->m++;
}

int main(){
	Graph G;
	
	init_graph(&G, 5);
	add_edge(&G, 1, 1);
	add_edge(&G, 1, 3);
	add_edge(&G, 4, 2);
	add_edge(&G, 2, 4);
	add_edge(&G, 3, 1);
	add_edge(&G, 5, 4);
	add_edge(&G, 2, 4);
	add_edge(&G, 3, 1);
	
	printf("n = %d, m = %d\n", G.n, G.m);
	
	for(int i=0;i<G.m;++i){
		printf("%d %d\n", G.edges[i].u, G.edges[i].v);
	}
	return 0;
}

