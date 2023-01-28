#include <stdio.h>

#define MAX_VERTICES 20
#define MAX_LENGTH 20

typedef struct Graph{
	int A[MAX_VERTICES][MAX_VERTICES];
	int n;
}Graph;

//khoi tao do thi
void init_Graph(Graph *G, int n){
	G->n = n;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			G->A[i][j] = 0;
		}
	}
}

//in ma tran dinh
void print_Graph(Graph G){
	for(int i=1;i<=G.n;++i){
		for(int j=1;j<=G.n;++j){
			printf("%d ", G.A[i][j]);
		}
		printf("\n");
	}
}

//them cung
void add_Edge(Graph *G, int x, int y){
	G->A[x][y] = 1;
	G->A[y][x] = 1;
	
}

//kt co phai dinh ke
int isAdjacent(Graph *G, int x, int y){
	return G->A[x][y] == 1;
}

//bac cua dinh
int degree(Graph G, int x){
	int deg = 0;
	for(int i=1;i<=G.n;++i){
		if(G.A[x][i] == 1){
			deg++;	
		}
	}
	return deg;
}

//khai bao cau truc ds dac
typedef struct List{
	int data[MAX_LENGTH];
	int size;
}List;

//tao rong
void make_null_list(List *L){
	L->size=0;
}

//chen cuoi
void push_back(List *L, int x){
	L->data[L->size] = x;
	L->size++;
}

//lay 1 ptu trong ds tai vtri i
int element_at(List L, int i){
	return L.data[i-1];
}

//lay lang gieng cua 1 dinh
List neighbors(Graph G, int x){
	List L;
	make_null_list(&L);
	for(int i=1;i<=G.n;++i){
		if(G.A[x][i] == 1){	
			push_back(&L, i);
		}
	}
	return L;
}

// in ds
void print_list(List N){
	for(int i=1;i<=N.size;++i){
		printf("%d, ", element_at(N, i));
	}
	printf("]\n");
}

int marked[MAX_VERTICES];// mang danh dau cac dinh da duyet

void DFS_Recursion(Graph G, int u){
	if(marked[u]){
		return;
	}
	printf("Duyet: %d\n", u);
	marked[u]=1;
	List L = neighbors(G,u);
	for(int i=1;i<=L.size;++i){
		int v = element_at(L,i);
		DFS_Recursion(G,v);
	}
}

int main(int argc, char *argv[]){
	Graph G;
	freopen("DFS_Recursion.txt", "r", stdin);
	int n, m; //so luong dinh va cung
	scanf("%d %d", &n, &m);
	init_Graph(&G, n);
	int u, v; //bien temp de luu 2 dinh cua cung
	
	for(int k=1;k<=m;++k){
		scanf("%d%d", &u, &v);
		add_Edge(&G,u,v);
	}
	
	for(int i=1;i<=G.n;++i){
		marked[i]=0;
	}
	
	DFS_Recursion(G,1);
	
	return 0;
}
