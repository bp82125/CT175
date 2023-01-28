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
	if(u==v){
		pG->A[u][u]++;
	}else{
		pG->A[u][v]++;
		pG->A[v][u]++;
	}
	pG->m++;
}

void neighbours(Graph *pG, int u){
	printf("neighbours(%d) = ",u);
	for(int i=1;i<=pG->n;++i){
		for(int j=1;j<=pG->A[u][i];++j){
			printf("%d ", i);	
		}
	}
	printf("\n");
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
	
	for(int i=1;i<=G.n;++i){
		neighbours(&G,i);
	}
		
	return 0;
}


