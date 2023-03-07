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
		if((pG->edges[i].u == u && pG->edges[i].v == v) ||(pG->edges[i].u == v && pG->edges[i].v == u)){
			return 1;
		}
	}
	return 0;
}

int pi[MAX_N];
int p[MAX_N];
int mark[MAX_N];

#define oo INT_MAX

int getWeight(Graph *pG, int u, int v){
	for(int i=0;i<pG->m;++i){
		if((pG->edges[i].u == u && pG->edges[i].v == v) ||(pG->edges[i].u == v && pG->edges[i].v == u)){
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
		
		int min_pi = oo;
		int min_index;
		for(int j=1;j<=pG->n;++j){
			if(pi[j]<min_pi && !mark[j]){
				min_index = j;
				min_pi = pi[j];
			}
		}
	
		mark[min_index] = 1;
		
		for(int v=1;v<=pG->n;++v){
			if(adjacent(pG, min_index, v) && !mark[v]){
				int w = getWeight(pG, min_index, v);
				if(pi[min_index] + w < pi[v]){
					pi[v] = pi[min_index] + w;
					p[v] = min_index;
				}
			}
		}
		
	}
}

void print_path(Graph *pG, int parent, int u, int end){
	if(parent==u){
		printf("%d -> ", u);
		return;
	}
	print_path(pG, parent, p[u], end);
	printf("%d", u);
	if(u!=end){
		printf(" -> ");
	}
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
	
	print_path(&G,start,end,end);
	
	return 0;
}
