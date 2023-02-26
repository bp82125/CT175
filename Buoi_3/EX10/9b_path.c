#include <stdio.h>
#include <limits.h>

#define MAX_N 100

typedef struct Edge{
	int u, v;
	int weight;
}Edge;

typedef struct Graph{
	int n, m;
	Edge edges[MAX_N];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

void add_edges(Graph *pG, int u, int v, int w){
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	pG->edges[pG->m].weight = w;
	
	pG->m++;
}

int adjacent(Graph *pG, int u, int v){
	for(int i=0;i<pG->m;++i){
		if(pG->edges[i].u == u && pG->edges[i].v == v){
			return 1;
		}
	}
	return 0;
}

int getWeight(Graph *pG, int u, int v){
	for(int i=0;i<pG->m;++i){
		if(pG->edges[i].u == u && pG->edges[i].v == v){
			return pG->edges[i].weight;
		}
	}
	return INT_MAX;
}

int pi[MAX_N][MAX_N];
int next[MAX_N][MAX_N];

void FloydWarshall(Graph *pG){
	for(int i=1;i<=pG->n;++i){ //khoi tao 2 mang
		for(int j=1;j<=pG->n;++j){
			pi[i][j] = INT_MAX;
			next[i][j] = -1;
		}
	}
	
	for(int i=1;i<=pG->n;++i){
		pi[i][i] = 0;
		next[i][i] = i;
	}
	
	for(int i=1;i<=pG->n;++i){ //khoi tao 2 mang
		for(int j=1;j<=pG->n;++j){
			if(adjacent(pG, i, j)){
				pi[i][j] = getWeight(pG, i, j);
				next[i][j] = j;
			}
		}
	}
	
	for(int k=1;k<=pG->n;++k){
		for(int u=1;u<=pG->n;++u){
			for(int v=1;v<=pG->n;++v){
				if(pi[u][k] + pi[k][v] < pi[u][v] && pi[u][k]!=INT_MAX && pi[k][v]!=INT_MAX){
					pi[u][v] = pi[u][k] + pi[k][v];
					next[u][v] = next[u][k];
				}
			}
		}
	}
	
}

void print_path(Graph *pG,int start, int end){
	
	printf("path(%d -> %d): ", start, end);
	
	if(next[start][end] == -1){
		printf("NO PATH\n");
		return;
	}
	
	while(start!=end){
		printf("%d -> ", start);
		start = next[start][end];
	}
	
	printf("%d\n", end);
}

int main(void){
	freopen("dt.txt", "r", stdin);
	
	Graph G;
	
	int n,m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for(int i = 0;i<m;++i){
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edges(&G, u,v,w);
	}
	
	FloydWarshall(&G);
	
//	for(int i=1;i<=G.n;++i){
//		for(int j=1;j<=G.n;++j){
//			printf("%d -> %d: ", i, j);
//			if(pi[i][j] == INT_MAX){
//				printf("NO PATH\n");
//			}else{
//				printf("%d\n", pi[i][j]);
//			}
//		}
//	}
	
	for(int i=1;i<=G.n;++i){
		for(int j=1;j<=G.n;++j){
			print_path(&G, i, j);
		}
	}

//	for(int i=1;i<=G.n;++i){
//		for(int j=1;j<=G.n;++j){
//			printf("next[%d][%d] = %d\n", i,j,next[i][j]);
//		}
//	}
	

	return 0;
}
