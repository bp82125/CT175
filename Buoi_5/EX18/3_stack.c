#include <stdio.h>
#include <limits.h>
#include "stack.c"

#define MAXN 100
#define NO_EDGE 0
#define oo INT_MAX
#define min(a,b) (a<b)?a:b 

typedef struct Graph{
	int C[MAXN][MAXN];
	int F[MAXN][MAXN];
	int n,m;
}Graph;

typedef struct Label{
	int dir;
	int parent;
	int sigma;
}Label;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= n; ++j){
			pG->C[i][j] = 0;
		}
	}
}

void add_edge(Graph *pG, int u, int v, int c){
	pG->C[u][v] = c;
	pG->m++;
}

Label labels[MAXN];

void init_flow(Graph *pG){
	int n = pG->n;
	
	for(int i = 1; i <= n;++i){
		for(int j = 1; j <= n; ++j){
			pG->F[i][j] = 0;
		}
	}
}



int FordFulkerson(Graph *pG, int s, int t){
	init_flow(pG);
	int max_flow = 0;
	
	Stack S;
	do{
		for(int i = 1; i <= pG->n; ++i){
			labels[i].dir = 0;
		}
		
		labels[s].dir = +1;
		labels[s].parent = s;
		labels[s].sigma = oo;
		
		make_null_stack(&S);
		push(&S, s);
		
		int found = 0;
		while(!empty(&S)){
			int u = top(&S);
			pop(&S);
			// cung thuan
			for(int v = 1; v <= pG->n; ++v){
				if(pG->C[u][v] != NO_EDGE 
					&& labels[v].dir == 0 
					&& pG->F[u][v] < pG->C[u][v]){
						labels[v].dir = +1;
						labels[v].parent = u;
						labels[v].sigma = min(labels[u].sigma, pG->C[u][v] - pG->F[u][v]); // luong co the tang con lai va sigma
						push(&S, v);
				}
			}
			
			// cung nghich
			for(int p = 1; p <= pG->n; ++p){
				if(pG->C[p][u] != NO_EDGE 
					 && labels[p].dir == 0 
					 && pG->F[p][u] > 0){
						labels[p].dir = -1;
						labels[p].parent = u;
						labels[p].sigma = min(labels[u].sigma, pG->F[p][u]); // luong co the tang con lai va sigma
						push(&S, p);
				}
			}
			
			if(labels[t].dir != 0){
				found = 1;
				break;
			}
		}
		
		if(found){
			int sigma = labels[t].sigma;
			
			int u = t;
			
			while(u != s){
				int p = labels[u].parent;
				if(labels[u].dir > 0){
					pG->F[p][u] += sigma;
				}else{
					pG->F[p][u] -= sigma;
				}
				u = p;
			}
			
			max_flow += sigma;
		}else{
			break;
		}
	}while(1);
	
	return max_flow;
}

int main(void){
	Graph G;
	int n, m;
	freopen("dt.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	
	init_graph(&G, n);
	for(int e = 0; e < m; ++e){
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		add_edge(&G, u, v, c);
	}

	int max_flow = FordFulkerson(&G, 1, n);
	
	printf("Max flow: %d\n", max_flow);
	
	return 0;
	
}


