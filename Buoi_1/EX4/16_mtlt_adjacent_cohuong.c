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
	if(u==v){
		pG->A[u][e]=2;
	}
	else{
		pG->A[u][e]=1;
		pG->A[v][e]=-1;	
	}
}

int adjacent(Graph *pG, int x, int y){
	for(int e=1;e<=pG->m;++e){
		if(x==y && pG->A[x][e]==2){
			return 1;
		}else if(pG->A[x][e]==1 && pG->A[y][e]==-1 && x!=y){
			return 1;
		}
	}
	return 0;
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
