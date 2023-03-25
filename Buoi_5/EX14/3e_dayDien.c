#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

typedef struct Edge{
	int u, v;
	int length, cost;
}Edge;

typedef struct Graph{
	int n, m;
	Edge edges[MAX_N];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

void add_edges(Graph *pG, int u, int v, int s, int c){
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	pG->edges[pG->m].length = s;
	pG->edges[pG->m].cost = c;
	
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

int comparator(const void *a, const void *b){
	return (*((Edge*)a)).length * (*((Edge*)a)).cost - (*((Edge*)b)).length * (*((Edge*)b)).cost;
}

int parent[MAX_N];

int findRoot(int u){
	if(parent[u]==u){
		return u;
	}
	return findRoot(parent[u]);
}

int Kruskal(Graph *pG, Graph *pT){
	qsort(pG->edges, pG->m, sizeof(Edge), comparator);
	
	init_graph(pT, pG->n);
	for(int u = 1; u<=pG->n;++u){
		parent[u] = u;
	}
	
	int sum_w = 0;
	
	for(int e = 0; e<pG->m;++e){
		int u = pG->edges[e].u;
		int v = pG->edges[e].v;
		int s = pG->edges[e].length;
		int d = pG->edges[e].cost;
		
		int root_u = findRoot(u);
		int root_v = findRoot(v);
		
		if(root_u != root_v){
			add_edges(pT, u, v, s, d);
			parent[root_v] = root_u;
			sum_w += s*d;
		}
	}
	return sum_w;
}

int main(void){
	freopen("dt.txt", "r", stdin);
	
	Graph G;
	
	int n,m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for(int i = 0;i<m;++i){
		int u, v, s, d;
		scanf("%d%d%d%d", &u, &v, &s, &d);
		add_edges(&G, u,v,s, d);
	}
	
	Graph T;
	
	int sum = Kruskal(&G, &T);
	
	printf("%d\n", sum);
	
	return 0;
}
