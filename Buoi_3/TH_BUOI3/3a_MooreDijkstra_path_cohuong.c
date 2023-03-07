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

#define oo INT_MAX

int pi[MAX_N];
int p[MAX_N];
int mark[MAX_N];

int getWeight(Graph *pG, int u, int v){
	for(int i=0;i<pG->m;++i){
		if(pG->edges[i].u == u && pG->edges[i].v == v){
			return pG->edges[i].weight;
		}
	}
	return 0;
}

void MooreDijkstra(Graph *pG, int s){
	for(int i=1;i<=pG->n;++i){
		pi[i] = oo;
		p[i] = 0;
		mark[i] = 0;
	}
	
	pi[s] = 0;
	p[s] = -1;
	
	for(int i=1;i<=pG->n-1;++i){
		int u, min_pi = oo;
		for(int j=1;j<=pG->n;++j){
			if(pi[j] < min_pi && !mark[j]){
				u = j;
				min_pi = pi[j];
			}
		}
		
		mark[u] = 1;
		
		for(int v=1;v<=pG->n;++v){
			if(adjacent(pG, u, v) && !mark[v]){
				if(pi[u] + getWeight(pG, u, v) < pi[v]){
					pi[v] = pi[u] + getWeight(pG, u, v);
					p[v] = u;
				}
			}
		}
	}
}

void print_path(Graph *pG, int start, int end){
	int child[pG->n];
	
	child[end] = 0;
	while(end!=start){
		child[p[end]] = end;
		end = p[end];
	}
	
	while(child[end]!=0){
		printf("%d -> ", end);
		end = child[end];
	}
	printf("%d", end);
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
	
	int start, end;
	scanf("%d%d", &start, &end);
	
	MooreDijkstra(&G, start);
	
	print_path(&G, start, end);
	
	return 0;
}
