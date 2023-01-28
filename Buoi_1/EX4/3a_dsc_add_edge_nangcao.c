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
	if(u < 1 || u > pG->n) return; //truong hop u va v khong hop le
	if(v < 1 || v > pG->n) return;
	
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	
	pG->m++;
}

int main(){
	Graph G;
	
	init_graph(&G, 5);
	add_edge(&G, 1, 1);
	add_edge(&G, 1, 3);
	add_edge(&G, 6, 2);
	add_edge(&G, 2, 4);
	add_edge(&G, 3, 3);
	add_edge(&G, 5, 4);
	add_edge(&G, 3, -3);
	add_edge(&G, 3, 3);
	
	printf("n = %d, m = %d\n", G.n, G.m);
	
	for(int i=0;i<G.m;++i){
		printf("%d %d\n", G.edges[i].u, G.edges[i].v);
	}
	return 0;
}




