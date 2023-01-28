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

int adjacent(Graph *pG, int u, int v) {
	for(int i=0;i<pG->m;++i){
		if(pG->edges[i].u == u && pG->edges[i].v == v){
			return 1;
		}
	}
	return 0;
}

int main(){
	Graph G;
	
	init_graph(&G, 4);
	add_edge(&G, 1, 3);
	add_edge(&G, 4, 2);
	add_edge(&G, 2, 4);
	add_edge(&G, 2, 1);
	add_edge(&G, 3, 2);
	
	printf("n = %d, m = %d\n", G.n, G.m);
	
	for(int i=1;i<=G.n;++i){
		for(int j=1;j<=G.n;++j){
			if(adjacent(&G, i, j)){
				printf("%d ke voi %d.\n", i, j);
			}else{
				printf("%d KHONG ke voi %d.\n", i, j);
			}	
		}
	}
	return 0;
}
