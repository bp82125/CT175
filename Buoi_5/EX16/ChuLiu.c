#include <stdio.h>
#include <limits.h>

#define MAXN 100
#define MAXM 500
#define INF INT_MAX

typedef struct Edge{
	int u, v;
	int w;
	int link; // cung truoc trong do thi G(t-1)
}Edge;

typedef struct Graph{
	int n, m;
	Edge edges[MAXM];
}Graph;

typedef struct Tree{ //do thi xap xi
	int n;
	int parent[MAXN];
	int weight[MAXN];
	int link[MAXN];
}Tree;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

void init_tree(Tree *pT, int n){
	pT->n = n;
	for(int i = 1; i <= pT->n; ++i){
		pT->parent[i] = i;
		pT->weight[i] = INF;
		pT->link[i] = -1;
	}
}

void add_edge(Graph *pG, int u, int v, int w, int link){
	int m = pG->m;
	
	pG->edges[m].u = u;
	pG->edges[m].v = v;
	pG->edges[m].w = w;
	pG->edges[m].link = link;
	
	pG->m++;
}

void buildH(Graph *pG, int root, Tree *pH){
	init_tree(pH, pG->n);
	
	for(int e = 0; e < pG->m; ++e){
		int u = pG->edges[e].u;
		int v = pG->edges[e].v;
		int w = pG->edges[e].w;
		int link = pG->edges[e].link;
		
		if(w < pH->weight[v]){
			pH->parent[v] = u;
			pH->weight[v] = w;
			pH->link[v] = link;
		}
	}
	
	pH->parent[root] = -1;
	pH->parent[root] = 0;
}

int id[MAXN];

int find_cycle(Tree *pH, int root){
	int color[MAXN];
	
	for(int i = 1; i <=pH->n;++i){
		id[i] = -1;
		color[i] = -1;
	}
	
	int no = 0;
	for(int i = 1; i <= pH->n; ++i){
		int u = i;
		while(u != root && id[u] == -1 && color[u]!=i){
			color[u] = i;
			u = pH->parent[u];
		}
		
		if(color[u] == i){
			no++;
			int v = pH->parent[u];
			while(v != u){
				id[v] = no;
				v = pH->parent[v];
			}
			id[u] = no;
		}
	}
	return no;
}

void contract(Graph *pG, Tree *pH, int no, Graph *pG1){
	init_graph(pG1, no);
	for(int e = 0; e < pG->m;++e){
		int u = pG->edges[e].u;
		int v = pG->edges[e].v;
		int w = pG->edges[e].w;
		if(id[u] != id[v]){
			add_edge(pG1, id[u], id[v], w - pH->weight[v],e);
		}
	}
}

void expand(Tree *pH, Graph *pG1, Tree * pH1){
	for(int i = 1; i <= pH->n; ++i){
		if(pH->parent[i] != -1){
			Edge pe = pG1->edges[pH->link[i]];
			pH1->parent[pe.v] = pe.u;
			pH1->weight[pe.v] += pH->weight[i];
			pH1->link[pe.v] = pe.link;
		}
	}
}

#define MAXIT 10

void ChuLiu(Graph *pG0, int s, Tree *pT){
	Graph G[MAXIT];
	Tree H[MAXIT];
	
	int t = 0;
	int root = s;
	G[0] = *pG0;
	
	while(1){
		buildH(&G[t], root, &H[t]);
		int no = find_cycle(&H[t], root);
		if(no == 0){
			break;
		}
		
		for(int i = 1; i <= H[t].n;++i){
			if(id[i] == -1){
				id[i] = ++no;
			}
		}
		
		contract(&G[t],&H[t], no, &G[t+1]);
		root = id[root];
		t++;
	}
	
	for(int k = t; k > 0; --k){
		expand(&H[k], &G[k-1], &H[k-1]);
	}
	
	*pT = H[0];
}

int main(void){
	Graph G;
	int n, m;
	
	freopen("dt.txt", "r", stdin);
	
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for(int e = 0; e < m; ++e){
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w, -1);
	}
	
	Tree T;
	
	ChuLiu(&G, 1, &T);
	
	for(int i = 1; i <= T.n; ++i){
		if(T.parent[i] != -1 && T.weight[i]!=INF){
			printf("(%d, %d) %d\n", T.parent[i], i, T.weight[i]);
		}
	}
	return 0;
}
