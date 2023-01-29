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

#define min(a,b) (a<b) ? a : b

int num[MAX_VERTICES]; //num dung de luu thu tu duyet dfs
int min_num[MAX_VERTICES]; // min_num luu gia tri num nho nhat tai u ma nho nhat trong cay dfs con cua dinh u
int k; // bien dung de danh dau thu tu duyet dinh
Stack S;
int on_stack[MAX_VERTICES]; //danh dau dinh co co nam trong stack hay khong
int has_scc;

void SCC(Graph *pG, int u){
	num[u] = min_num[u] = k++;
	push(&S, u);
	on_stack[u] = 1;
	
	for(int i = 1; i<=pG->n;++i){
		if(adjacent(pG, u, i)){
			if(num[i]<0){ //neu i chua duyet thi goi de quy duyet i
				SCC(pG, i);
				min_num[u] = min(min_num[i], min_num[u]); 
			}else if(on_stack[i]){
				min_num[u] = min(min_num[u], num[i]);
			}
		}
	}
	
	if(min_num[u]==num[u]){ // neu u la dinh khop thi ra het khoi stack cho toi khi gap u
		int temp; 			// khi do cac dinh lay ra se thuoc 1 bplt manh xuat phat tu u
		int count = 0;
		do{
			count++;
			temp = top(&S);
			pop(&S);
			on_stack[temp] = 0;
		}while(temp!=u);
		
		if(count == pG->n){
			has_scc = 1;
		}
		
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
	
	for(int i=1;i<=n;++i){
		num[i] = -1;
		min_num[i] = n+1;
		on_stack[i] = 0;
	}
	
	k = 1;
	has_scc = 0;
	make_null_stack(&S);
	
	for(int i=1;i<=n;++i){
		if(num[i]==-1){
			SCC(&G, i);
		}
	}
	
	if(has_scc){
		printf("STRONG CONNECTED");
	}else{
		printf("DISCONNECTED");
	}
	return 0;
}



