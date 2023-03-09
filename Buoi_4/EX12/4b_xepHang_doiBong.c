#include <stdio.h>
#include "list.c"

#define MAX_VERTICES 100

typedef struct Graph{
	int n, m;
	int A[MAX_VERTICES][MAX_VERTICES];
}Graph;

void init_graph(Graph *pG, int n){
	pG->m++;
	pG->n = n;
	
	for(int i = 0; i < n ;++i){
		for(int j = 0; j<n;++j){
			pG->A[i][j] = 0;
		}
	}
}

void add_edges(Graph *pG, int u, int v){
	pG->A[u][v]++;
	pG->m++;
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0;
}

int deg_in(Graph *pG, int u){
	int deg = 0;
	for(int v = 1; v <= pG->n; ++v){
		deg += pG->A[v][u];
	}
	return deg;
}

int rank[MAX_VERTICES];
int d[MAX_VERTICES];

void ranking(Graph *pG){
	List L1;
	make_null(&L1);
	
	for(int u = 1; u<=pG->n;++u){
		d[u] = deg_in(pG, u);
		if(d[u]==0){
			push_back(&L1, u);
		}
	}
	
	List L2;
	int k = 0;
	
	while(!emptyList(&L1)){
		make_null(&L2);
		
		for(int i = 0; i<L1.size;++i){
			int u = L1.data[i];
			rank[u] = k;
			
			for(int v = 1; v<=pG->n;++v){
				if(adjacent(pG, u, v)){
					d[v]--;
					if(d[v]==0) push_back(&L2, v);
				}
			}
		}
		
		k++;
		copy_list(&L1, &L2);
	}
}


int main(void){
	Graph G;
	freopen("dt.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for(int i = 0; i<m;++i){
		int u, v;
		scanf("%d%d", &u, &v);
		add_edges(&G, u, v);
	}
	
//	for(int i = 1; i <= n ;++i){
//		for(int j = 1; j<=n;++j){
//			if(adjacent(&G, i, j)){
//				printf("%d %d\n", i, j);
//			}
//		}
//	}
	
	ranking(&G);

	for(int u = 1; u<=G.n;++u){
		printf("%d ", rank[u] + 1);
	}
	
	return 0;
}

