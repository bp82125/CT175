#include <stdio.h>
#include <limits.h>

#define INFINITY INT_MAX
#define MAX_VERTICES 100

typedef struct Edge{
	int u, v;
	int weight;
}Edge;

typedef struct Graph{
	int n, m;
	Edge edges[MAX_VERTICES];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

int adjacent(Graph *pG, int u, int v){
	for(int i=0;i<pG->m;++i){
		if((pG->edges[i].u == u && pG->edges[i].v == v) ||(pG->edges[i].u == v && pG->edges[i].v == u)){
			return 1;
		}
	}
	return 0;
}

void add_edges(Graph *pG, int u, int v, int w){	
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	pG->edges[pG->m].weight = w;
	
	pG->m++;
}

int pi[MAX_VERTICES];
int parent[MAX_VERTICES];
int mark[MAX_VERTICES];

int getWeight(Graph *pG, int u, int v){
	for(int i=0;i<pG->m;++i){
		if((pG->edges[i].u == u && pG->edges[i].v == v) ||(pG->edges[i].u == v && pG->edges[i].v == u)){
			return pG->edges[i].weight;
		}
	}
	return 0;
}

void MooreDijkstra(Graph *pG, int s){
	// Khoi tao cac dinh
	for(int i=0;i<=pG->n;++i){
		pi[i] = INFINITY;
		parent[i] = 0;
		mark[i] = 0;
	}
	
	// Khoi tao gia tri cho dinh s
	pi[s] = 0;
	parent[s] = -1;
	
	// Lap n-1 lan
	for(int i=1; i<=pG->n-1;++i){
		// Tim dinh chua duyet co gtri pi nho nhat
		int index, min_pi = INFINITY;
		
		for(int j=1;j<=pG->n;++j){
			if(!mark[j] && pi[j] < min_pi){
				index = j;
				min_pi = pi[index];
			}
		}
		
		// Danh dau diem da duyet
		
		mark[index] = 1;
		
		// Xet cac dinh ke cua dinh da duyet
		
		for(int k=1;k<=pG->n;++k){
			if(adjacent(pG, index, k) && !mark[k] ){
				int w = getWeight(pG, index, k);
				if(pi[index] + w < pi[k]){
					pi[k] = pi[index] + w;
					parent[k] = index;
				}
			}
		}
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
	
	MooreDijkstra(&G, 1);
	
	for(int i=1;i<=n;++i){
		printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, parent[i]);
	}

	
	return 0;
}
