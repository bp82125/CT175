#include <stdio.h>

#define MAX_VERTICES 20
#define MAX_LENGTH 20

typedef struct Graph{
	int A[MAX_VERTICES][MAX_VERTICES];
	int n;
}Graph;

void init_Graph(Graph *G, int n){
	G->n = n;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			G->A[i][j] = 0;
		}
	}
}

void print_Graph(Graph G){
	for(int i=1;i<=G.n;++i){
		for(int j=1;j<=G.n;++j){
			printf("%d ", G.A[i][j]);
		}
		printf("\n");
	}
}

void add_Edge(Graph *G, int x, int y){
	G->A[x][y] = 1;
	G->A[y][x] = 1;
	
}

int isAdjacent(Graph *G, int x, int y){
	return G->A[x][y] == 1;
}

int degree(Graph G, int x){
	int deg = 0;
	for(int i=1;i<=G.n;++i){
		if(G.A[x][i] == 1){
			deg++;	
		}
	}
	return deg;
}

void print_all_degrees(Graph G){
	for(int i=1;i<=G.n;++i){
		printf("degree(%d) = %d\n", i, degree(G,i));	
	}
}

//khai bao cau truc ds dac
typedef struct List{
	int data[MAX_LENGTH];
	int size;
}List;

//tao rong
void make_null(List *L){
	L->size=0;
}

//chen cuoi
void push_back(List *L, int x){
	L->data[L->size] = x;
	L->size++;
}

//lay 1 ptu trong ds tai vtri i
int element_at(List* L, int i){
	return L->data[i-1];
}

//lay lang gieng cua 1 dinh
List neighbors(Graph G, int x){
	List L;
	make_null(&L);
	for(int i=1;i<=G.n;++i){
		if(G.A[x][i] == 1){	
			push_back(&L, i);
		}
	}
	return L;
}

void print_list(List N){
	for(int i=1;i<=N.size;++i){
		printf("%d, ", element_at(&N, i));
	}
	printf("]\n");
}

void print_all_neighbors(Graph G){
	for(int i=1;i<=G.n;++i){
		List list = neighbors(G, i);
		printf("neightbor(%d): [", i);
		print_list(list);	
	}
}

int main(int argc, char *argv[]){
	Graph G;
	freopen("dothi.txt", "r", stdin);
	int n, m; //so luong dinh va cung
	scanf("%d %d", &n, &m);
	init_Graph(&G, n);
	int u, v; //bien temp de luu 2 dinh cua cung
	
	for(int k=1;k<=m;++k){
		scanf("%d%d", &u, &v);
		add_Edge(&G,u,v);
	}
	
	print_all_degrees(G);
	
	print_all_neighbors(G);
	return 0;
}
