#include <stdio.h>

#define MAX_N 500
#define MAX_M 500

typedef struct Graph{
	int n, m;
	int A[MAX_N][MAX_M];
}Graph;

void init_graph(Graph *pG, int n, int m){
	pG->n = n;
	pG->m = m;
	
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			pG->A[i][j]=0;
		}
	}
}

int main() {
	Graph G;
	init_graph(&G, 5, 6);
	printf("Do thi co %d dinh va %d cung.", G.n, G.m);
	return 0;
}
