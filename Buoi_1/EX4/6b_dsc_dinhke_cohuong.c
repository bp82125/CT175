#include <stdio.h>

#define MAX_M 500
#define MAX_LENGTH 500

typedef struct Edge{
	int u,v;
}Edge;

typedef struct Graph{
	int n,m;
	Edge edges[MAX_M];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

void add_edge(Graph *pG, int u, int v){
	if(u < 1 || u > pG->n) return;
	if(v < 1 || v > pG->n) return;
	
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	
	pG->m++;
}

typedef struct List{
	int data[MAX_LENGTH];
	int size;
}List;

void make_null_list(List *L){
	L->size=0;
}

void push_back(List *L, int x){
	L->data[L->size] = x;
	L->size++;
}

int member(List L, int x){
	for(int i=0;i<L.size;++i){
		if(L.data[i]==x){
			return 1;
		}
	}
	return 0;
}

void sort(List *L){
	for(int i=0;i<L->size-1;++i){
		for(int j=i;j<L->size;++j){
			if(L->data[i] > L->data[j]){
				int temp = L->data[i];
				L->data[i] = L->data[j];
				L->data[j] = temp;
			}	
		}
		
	}
}

void print_list(List L){
	for(int i=0;i<L.size;++i){
		printf("%d ", L.data[i]);
	}
	printf("\n");
}

List neighbours(Graph G, int x){
	List L;
	make_null_list(&L);
	
	for(int i=0;i<G.m;++i){
		if(G.edges[i].u == x && !member(L,G.edges[i].v)){
			push_back(&L,G.edges[i].v);
		}
	}
	
	sort(&L);
	
	return L;
}
int main(){
	Graph G;
	int n, m, u, v;
	
	scanf("%d%d", &n, &m);
	init_graph(&G,n);
	
	for(int i=0;i<m;++i){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for(int i=1;i<=n;++i){
		printf("neighbours(%d) = ", i);
		List L = neighbours(G,i);
		print_list(L);
	}
	
	return 0;
}
