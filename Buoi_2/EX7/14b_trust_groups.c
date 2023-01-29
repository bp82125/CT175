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

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v]++;
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

int min(int a, int b){
	return (a<b) ? a : b;
}

int num[MAX_VERTICES], lowlink[MAX_VERTICES];
int k;
Stack S;
int on_stack[MAX_VERTICES];
int cnt_group;

void SCC(Graph *pG, int u){
	num[u] = lowlink[u] = k++;
	
	push(&S, u);
	on_stack[u] = 1;
	
	for(int i=1;i<=pG->n;++i){
		if(adjacent(pG,u,i)){
			if(num[i]==-1){
				SCC(pG, i);
				lowlink[u] = min(lowlink[u], lowlink[i]);
			}else if(on_stack[i]){
				lowlink[u] = min(lowlink[u], num[i]);
			}
		}
	}
	
	if(num[u]==lowlink[u]){
		int temp;
		do{
			temp = top(&S);
			pop(&S);
			on_stack[temp] = 0;
		}while(temp!=u);
		
		cnt_group++;
	}
}

int main(void){
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	k = 1;
	cnt_group = 0;
	make_null_stack(&S);
	
	for(int i=1;i<=n;++i){
		num[i] = -1;
		lowlink[i] = n+1;
		on_stack[i] = 0;
	}
	
	for(int i=1;i<=n;++i){
		if(num[i]==-1){
			SCC(&G, i);
		}
	}
	
	printf("%d", cnt_group);
	return 0;
}


