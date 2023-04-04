#include <stdio.h>
#include <limits.h>

#define MAXN 100
#define NO_EDGE 0
#define oo INT_MAX
#define min(a,b) (a<b)?a:b 

typedef struct Graph{
	int C[MAXN][MAXN];
	int F[MAXN][MAXN];
	int n,m;
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= n; ++j){
			pG->C[i][j] = 0;
		}
	}
}

int valid_flow(Graph *pG){
	int in_flow[pG->n+1];
	int out_flow[pG->n+1];
	
	for(int u = 1; u <= pG->n; ++u){
		in_flow[u] = out_flow[u] = 0;
	}
	for(int u = 1; u <= pG->n; ++u){
		for(int v = 1; v <= pG->n; ++v){
			if(pG->C[u][v] != NO_EDGE){
				if(pG->F[u][v] < 0 || pG->F[u][v] > pG->C[u][v]){
					return 0;
				}else{
					in_flow[v] += pG->F[u][v];
					out_flow[u] += pG->F[u][v];
				}
			}
		}
	}
	
	if(out_flow[1] != in_flow[pG->n]){
		return 0;
	}
	
	for(int u = 2; u <= pG->n - 1; ++u){
		if(in_flow[u] != out_flow[u]){
			return 0;
		}
	}
	
	return 1;
}

void add_edge(Graph *pG, int u, int v, int c, int f){
	pG->C[u][v] = c;
	pG->F[u][v] = f;
	pG->m++;
}

int main(void){
	Graph G;
	int n, m;
	freopen("dt.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	
	init_graph(&G, n);
	for(int e = 0; e < m; ++e){
		int u, v, c, f;
		scanf("%d%d%d%d", &u, &v, &c, &f);
		add_edge(&G, u, v, c, f);
	}
	
	int check = valid_flow(&G);
	
	if(check){
		printf("YES");
	}else{
		printf("NO");
	}
	
	return 0;
	
}


