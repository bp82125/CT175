#include <stdio.h>

#define MAX_VERTICES 20
#define MAX_LENGTH 20
#define MAX_STACK 40
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
	printf("\n");
}

//khai bao ngan xep
typedef struct Stack{
	int data[MAX_STACK];
	int size;
}Stack;

//tao rong cho stack
void make_null_stack(Stack *S){
	S->size=0;
}

//them 1 ptu vao stack
void push_stack(Stack *S, int x){
	S->data[S->size]=x;
	S->size++;
}

//lay 1 ptu trong stack
int top(Stack S){
	return S.data[S.size-1];
}

//xoa 1 ptu trong stack
void pop(Stack *S){
	S->size--;
}

int empty(Stack S){
	return S.size==0;
}

List depth_first_search(Graph G, int x, int parent[]){
	Stack S;
	make_null_stack(&S); //khoi tao stack
	push_stack(&S, x); //dua phan tu dau tien vao stack
	parent[x] = 0; //dinh cha cua phan tu dau tien la 0
	
	int marked[MAX_VERTICES]; //mang luu tru cac dinh da duyet
	
	List dfs;
	make_null_list(&dfs); //tao ds luu tru thu tu duyet
	
	for(int i=1;i<=G.n;++i){
		marked[i] = 0; //khoi tao cac dinh chua duoc duyet
	}
	
	while(!empty(S)){
		int u = top(S); //lay dinh cua stack
		pop(&S);
		if(marked[u]){
			continue; //neu da duyet roi thi continue
		}
		
		push_back(&dfs, u); //dua vao ds thu tu duyet
		marked[u] = 1; //danh dau la da duyet
		
		List L = neighbors(G, u); //ds cac dinh lan can cua u
		
		for(int i=1;i<=L.size;++i){
			int v = element_at(L,i); 
			if(!marked[v]){ //neu dinh lan can nao chua duyet
				push_stack(&S, v); //thi them vao stack
				parent[v]=u; //dua cha cua v vao mang parent
			}
		}
	}
	return dfs;
}

void duyet_dfs(Graph G){
	int marked_dfs[MAX_VERTICES];
	int parent[MAX_VERTICES]; //khoi tao mang luu tru dinh cha
	
	for(int i=1;i<=G.n;++i){
		marked_dfs[i] = 0; //khoi tao ds cac dinh da duyet
		parent[i] = -1;
	}
	
	for(int i=1;i<=G.n;++i){
		if(!marked_dfs[i]){
			List dfs = depth_first_search(G,i,parent); //khoi tao ds duyet tu dinh i
			for(int j=1;j<=dfs.size;++j){
				printf("%d\n", element_at(dfs, j));
				marked_dfs[j] = 1; //danh dau cac o da duyet
			}
		}
	}
	
	for(int i=1;i<=G.n;++i){
		printf("%d %d\n", i, parent[i]);
	}
}

int main(int argc, char *argv[]){
	Graph G;
	freopen("DFS.txt", "r", stdin);
	int n, m; //so luong dinh va cung
	scanf("%d %d", &n, &m);
	init_Graph(&G, n);
	int u, v; //bien temp de luu 2 dinh cua cung
	
	for(int k=1;k<=m;++k){
		scanf("%d%d", &u, &v);
		add_Edge(&G,u,v);
	}
	
	duyet_dfs(G);
	
	return 0;
}
