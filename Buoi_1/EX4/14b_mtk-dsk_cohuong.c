#include <stdio.h>

#define MAX_VERTICES 100
#define MAX_LENGTH 100

typedef struct List{
	int size;
	int data[MAX_LENGTH];
}List;

void make_null(List *pL){
	pL->size = 0;
}

void push_back(List *pL, int x){
	pL->data[pL->size] = x;
	pL->size++;
}

int element_at(List L, int i){
	return L.data[i-1];
}

void print_list(List L){
	for(int i=1;i<=L.size;++i){
		printf("%d ", element_at(L,i));
	}
	printf("0\n");
}

typedef struct Graph{
	int n,m;
	List adj[MAX_VERTICES];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	
	for(int i=1;i<=n;++i){
		make_null(&pG->adj[i]);
	}
}

void add_edge(Graph *pG, int x, int y){
	push_back(&pG->adj[x], y);
	pG->m++;
}

int main() {	
	Graph G;
	int n;
	scanf("%d", &n);
	init_graph(&G, n);
	
	int mtk[n][n];
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			int temp;
			scanf("%d", &temp);
			mtk[i][j]=temp;
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(mtk[i][j]>0){
				for(int k=1;k<=mtk[i][j];k++){
					add_edge(&G, i, j);
				}
			}
		}
	}
	
	for(int i=1;i<=G.n;++i){
		print_list(G.adj[i]);
	}
	
	return 0;
}

