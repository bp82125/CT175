#include <stdio.h>

#define MAX_VERTICES 20
#define MAX_LENGTH 20
#define MAX_QUEUE 40

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
int isAdjacent(Graph G, int x, int y){
	return G.A[x][y] == 1;
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
		if(isAdjacent(G,x,i)){	
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

//khai bao kieu du lieu hang doi
typedef struct Queue{
	int data[MAX_QUEUE];
	int front; //chi so dau queue
	int rear; //chi so cuoi queue
}Queue;

//tao rong queuez
void make_null_queue(Queue *Q){
	Q->front=0;
	Q->rear=-1;
}

//kiem tra hang doi rong
int empty_queue(Queue Q){
	return Q.front > Q.rear;
}

//lay 1 ptu o dau queue ra
int top(Queue Q){
	return Q.data[Q.front];
}

//xoa ptu o dau queue
void pop(Queue *Q){
	Q->front++;
}

//them vao cuoi hang doi
void push_queue(Queue *Q, int x){
	Q->rear++;
	Q->data[Q->rear]=x;
}

//ham tra ve danh sach cac ptu da duyet theo chieu rong
List breadth_first_search(Graph G, int x){
	Queue Q; //khoi tao queue
	make_null_queue(&Q);
	int marked[MAX_VERTICES]; //khoi tao mang danh dau cac ptu da duyet
	
	for(int i=1;i<=G.n;++i){ //gan gtra khoi tao cho mang danh dau
		marked[i]=0;
	}
	
	push_queue(&Q,x);
	
	List L_bfs; //khoi tao danh sach luu tru cac ptu da duyet = bfs
	make_null_list(&L_bfs);
	
	while(!empty_queue(Q)){
		int u = top(Q); //lay ptu dau hang doi ra
		pop(&Q);
		
		if(marked[u]){ //neu dinh do da duyet roi thi khong lam nua
			continue;
		}
		
		push_back(&L_bfs,u);
		marked[u]=1; //cap nhat dinh u da dc duyet
		
		List L = neighbors(G,u); //khoi tao danh sach cac dinh lan can cua u
		for(int i=1;i<=L.size;++i){
			int v = element_at(L,i); //v lan luot la cac dinh lan can cua u
			if(!marked[v]){
				push_queue(&Q, v); //neu v chua duyet thi them v vao cuoi hang doi
			}
		}
	}
	return L_bfs;
}

int main(int argc, char *argv[]){
	Graph G;
	freopen("BFS.txt", "r", stdin);
	int n, m; //so luong dinh va cung
	scanf("%d %d", &n, &m);
	init_Graph(&G, n);
	int u, v; //bien temp de luu 2 dinh cua cung
	
	for(int k=1;k<=m;++k){
		scanf("%d%d", &u, &v);
		add_Edge(&G,u,v);
	}
	
	int marked_bfs[MAX_VERTICES]; //khoi tao mang luu tru cac ptu da duyet
	for(int i=1;i<=G.n;++i){ 
		marked_bfs[i]=0;
	}
	
	for(int i=1;i<=G.n;++i){ //lan luot luot qua thu tu cac dinh trong do thi
		if(!marked_bfs[i]){ //neu dinh i chua duyet
			List L = breadth_first_search(G,i); //thi se tao ds duyet tu dinh i
			for(int j=1;j<=L.size;++j){
				int v = element_at(L,j); 
				printf("%d\n", v); //in ra cac ptu trong ds duyet tu o
				marked_bfs[v]=1; //danh dau cac ptu trong ds la da duyet
			}
		}
	}
	
	return 0;
}
