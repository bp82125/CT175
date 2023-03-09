#include <stdio.h>
#include <limits.h>

#define max(x,y) (x > y) ? x : y
#define min(x,y) (x < y) ? x : y

#include "list.c"
#include "queue.c"

#define MAX_VERTICES 100

typedef struct Graph{
	int n, m;
	int A[MAX_VERTICES][MAX_VERTICES];
}Graph;

void init_graph(Graph *pG, int n){
	pG->m++;
	pG->n = n;
	
	for(int i = 0; i < n ;++i){
		for(int j = 0; j<n;++j){
			pG->A[i][j] = 0;
		}
	}
}

void add_edges(Graph *pG, int u, int v){
	pG->A[u][v]++;
	pG->m++;
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0;
}

int deg_in(Graph *pG, int u){
	int deg = 0;
	for(int v = 1; v <= pG->n; ++v){
		deg += pG->A[v][u];
	}
	return deg;
}

int deg_out(Graph *pG, int u){
	int deg = 0;
	for(int v = 1; v <= pG->n; ++v){
		deg += pG->A[u][v];
	}
	return deg;
}


int deg[MAX_VERTICES];

List TopoSort(Graph *pG){
	List L;
	make_null(&L);
	
	Queue Q;
	make_null_queue(&Q);
	
	for(int u = 1; u<=pG->n;++u){
		deg[u] = deg_in(pG, u);
		if(deg[u] == 0) enqueue(&Q, u);
	}
	
	while(!empty(&Q)){
		int u = front(&Q);
		dequeue(&Q);
		push_back(&L, u);
		
		for(int v = 1; v<=pG->n;++v){
			if(adjacent(pG, u, v)){
				deg[v]--;
				if(deg[v] == 0) enqueue(&Q, v);
			}
		}
	}
	return L;
}

int main(void){
	Graph G;
	freopen("dt.txt", "r", stdin);
	
	int n;
	scanf("%d", &n);
	
	n = n + 2;
	
	init_graph(&G, n);
	
	int d[n + 1];
	
	for(int u = 1; u<=n;++u){
		scanf("%d", &d[u]); //nhap thoi gian can thiet cho cong viec u
		int x;
		
		do{
			scanf("%d", &x);
			if(x > 0){ // x la mot cong viec
				add_edges(&G, x, u);
			}
		}while(x > 0);
	}
	
	int alpha = n - 1;
	int beta = n;
	
	for(int u = 1; u<=n - 2;++u){
		int deg_1 = deg_in(&G, u);
		int deg_2 = deg_out(&G, u);
		
		if(deg_1 == 0){
			add_edges(&G, alpha, u);
		}
		
		if(deg_2==0){
			add_edges(&G, u, beta);
		}
	}
	
//	for(int u = 1; u<=n;++u){
//		for(int v = 1; v<=n;++v){
//			printf("%d ", G.A[u][v]);
//			}
//		printf("\n");
//	}
//	
	
//	for(int u = 1; u<=n;++u){
//		for(int v = 1; v<=n;++v){
//			if(G.A[u][v] > 0){
//				printf("%d %d\n", u, v);
//			}
//		}
//	}
	
	List L = TopoSort(&G);
	
//	for(int v = 0; v<L.size;++v){
//		printf("%d ", L.data[v]);
//	}
	
	int t[MAX_VERTICES]; //t la mang luu tru thoi gian thuc hien som nhat cua 1 cong viec u nao do
	t[alpha] = 0;
	d[alpha] = 0;
	
	for(int i = 1; i<L.size;++i){ //bo qua alpha
		int u = L.data[i];
		t[u] = INT_MIN;
		for(int p = 1;p<= G.n;++p){ //p la cong viec truoc cong viec u, hay u la con cua p
			if(adjacent(&G, p, u))
				t[u] = max(t[u], t[p] + d[p]); // tim node cha nao co thoi gian ket thuc tre nhat
		}
	}
	
	int T[n+1]; // T la mang luu tru thoi gian bat dau tru nhat cua mot cong viec u nao do
	T[beta] = t[beta];
	d[beta] = 0;
	
	for(int i = L.size -2; i > 0;--i){ // bo qua beta
		int u = L.data[i];
		T[u] = INT_MAX;
		for(int v = 1; v<=G.n;++v){ // v la con cua u
			if(adjacent(&G, u, v)){
				T[u] = min(T[u], T[v] - d[u]); // tim node con nao co thoi gian bat dau som nhat
			}	
		}
	}
	for(int u = 1; u<=n - 2;++u){ // khong in alpha va beta
		printf("%d %d\n", t[u], T[u]);
	}
	
	
	return 0;
}

