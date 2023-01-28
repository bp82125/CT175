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

int degree(Graph *pG, int u){
	int deg_u=0;
	
	for(int i=1;i<=pG->n;++i){
		deg_u+=pG->A[u][i];
	}
	return deg_u + pG->A[u][u]; //do do thi vo huong nen khuyen cong 2 lan
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
		printf("degree(%d) = %d\n", i, degree(&G,i));
	}
		
	return 0;
}


