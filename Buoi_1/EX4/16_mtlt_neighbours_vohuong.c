#include <stdio.h>

#define MAX_N 500
#define MAX_M 500
#define MAX_ELEMENTS 100

typedef int ElementType;

typedef struct {
	ElementType data[MAX_ELEMENTS];
	int size;
} List;

void make_null(List* L) {
	L->size = 0;
}

void push_back(List* L, ElementType x) {
	L->data[L->size] = x;
	L->size++;
}

ElementType element_at(List* L, int i) {
	return L->data[i-1];
}

int count_list(List* L) {
	return L->size;
}

int member(List *pL, int x){
	for(int i=1;i<=pL->size;++i){
		if(element_at(pL,i)==x){
			return 1;
		}
	}
	return 0;
}

void print_list(List L){
	for(int i=1;i<=L.size;++i){
		printf("%d ", element_at(&L,i));
	}
	printf("\n");
}

typedef struct Graph{
	int n, m;
	int A[MAX_N][MAX_M];
}Graph;

void init_graph(Graph *pG, int n, int m){
	pG->n = n;
	pG->m = m;
	
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			pG->A[i][j]=0;
		}
	}
}

void add_edge(Graph *pG, int e,int u, int v){
	pG->A[u][e]++;
	pG->A[v][e]++;
}

int adjacent(Graph *pG, int x, int y){
	for(int e=1;e<=pG->m;++e){
		if(x==y && pG->A[x][e]==2){
			return 1;
		}else if(pG->A[x][e]==1 && pG->A[y][e]==1 && x!=y){
			return 1;
		}
	}
	return 0;
}

List neighbours(Graph *pG, int x){
	List L;
	make_null(&L);
	
	for(int e=1;e<=pG->m;++e){
		for(int i=1;i<=pG->n;++i){
			if(adjacent(pG, x, i) && !member(&L, i)){
				push_back(&L, i);
			}
		}
	}
	return L;
}

int main() {
	Graph G;
	int n, m;
	
	scanf("%d%d", &n, &m);
	init_graph(&G, n, m);
	
	for (int e = 1; e <= m; e++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(&G, e, u, v);
	}
	
	for(int i=1;i<=G.n;++i){
		printf("neighbours(%d): ", i);
		List L = neighbours(&G, i);
		print_list(L);
	}
	
	return 0;
}
