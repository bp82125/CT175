#include <stdio.h>

#define MAX_VERTICES 100
#define MAX_LENGTH 100

typedef struct List{
	int size;
	int data[MAX_LENGTH];
}List;

void make_null(List *pL){
	pL->size = 0;
}

void push_back(List *pL, int x){
	pL->data[pL->size] = x;
	pL->size++;
}

int element_at(List *pL, int i){
	return pL->data[i-1];
}

int size(List *pL){
	return pL->size;
}

typedef struct Graph{
	int n,m;
	List adj[MAX_VERTICES];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	
	for(int i=1;i<=n;++i){
		make_null(&pG->adj[i]);
	}
}

int main() {
	Graph G;
	init_graph(&G, 5);
	printf("Do thi co %d dinh va %d cung.", G.n, G.m);
	return 0;
}

