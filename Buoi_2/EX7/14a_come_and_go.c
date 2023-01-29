#include <stdio.h>
#include "stack.c"

#define MAX_VERTICES 100
typedef struct {
	int n;
	int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

void init_graph(Graph *pG, int n){
	pG->n=n;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			pG->A[i][j]=0;
		}
	}
}

void add_edge(Graph *pG, int u, int v, int side){
	pG->A[u][v]++;
	if(side == 2){
		pG->A[v][u]++;
	}
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0;
}

void print_adjacent(Graph *pG, int u){
	printf("adjacent[%d] = ", u);
	for(int v = 1; v<=pG->n;++v){
		if(adjacent(pG, u, v)){
			printf("%d ", v);
		}
	}
	printf("\n");
}

#define min(a,b) (a<b) ? a : b

int disc[MAX_VERTICES], low[MAX_VERTICES];
Stack S;
int k;
int on_stack[MAX_VERTICES];
int is_sc;

void SCC(Graph *pG, int u){
	disc[u] = low[u] = k++;
	
	push(&S, u);
	on_stack[u] = 1;
	
	for(int v = 1; v<=pG->n;++v){
		if(adjacent(pG, u, v)){
			if(disc[v]<0){
				SCC(pG, v);
				low[u] = min(low[u], low[v]);
			}else if(on_stack[v]){
				low[u] = min(low[u], disc[v]);
			}
		}
	}
	
	if(disc[u]==low[u]){
		int temp;
		int count = 0;
		do{
			count++;
			temp = top(&S);
			pop(&S);
			on_stack[temp] = 0;
		}while(temp!=u);
		
		is_sc = (count == pG->n) ? 1 : is_sc;
	}
}

int main(void){
	freopen("come_n_go.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, e, side;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &side);
		add_edge(&G, u, v, side);
	}
	
	k = 1;
	is_sc = 0;
	make_null_stack(&S);
	
	for(int i = 1;i<=n;++i){
		disc[i] = -1;
		low[i] = n+1;
		on_stack[i] = 0;
	}
	
	for(int i = 1; i<=n;++i){
		if(disc[i]==-1){
			SCC(&G, i);
		}
	}
	
	if(is_sc){
		printf("OKIE");
	}else{
		printf("NO");
	}
	
	return 0;
}


