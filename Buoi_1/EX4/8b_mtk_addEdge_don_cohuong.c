#include <stdio.h>

#define MAX_N 100

typedef struct Graph{
	int n,m;
	int A[MAX_N][MAX_N];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			pG->A[i][j]=0;
		}
	}
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v]=1;
	pG->m++;
}

int main() {
	Graph G;
	int n, m;

	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (int e = 0; e < m; e++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	printf("Ma tran ke:\n");
	
	for (int u = 1; u <= G.n; u++) {
		for (int v = 1; v <= G.n; v++)
			printf("%d ", G.A[u][v]);
		printf("\n");	
	}	
	return 0;
}


