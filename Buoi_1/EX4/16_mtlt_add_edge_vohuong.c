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

void add_edge(Graph *pG, int e,int u, int v){
	pG->A[u][e]++;
	pG->A[v][e]++;
}

int main() {
	Graph G;
	int n, m;
	
	scanf("%d%d", &n, &m);
	init_graph(&G, n, m);
	
	for (int e = 1; e <= m; e++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(&G, e, u, v);
	}
	
	printf("Ma tran lien thuoc:\n");
	
	for(int i=1;i<=G.n;++i){
		for(int j=1;j<=G.m;++j){
			printf("%d ", G.A[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
