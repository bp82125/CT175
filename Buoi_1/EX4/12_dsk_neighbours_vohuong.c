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
	printf("\n");
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
	push_back(&pG->adj[y], x);
}

int adjacent(Graph *pG, int x, int y){
	for(int i=1;i<=pG->adj[x].size;++i){
		if(element_at(pG->adj[x],i) == y){
			return 1;
		}
	}
	return 0;
}

int main() {
	Graph G;
	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for(int i=0;i<m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(&G,u,v);
	}
	
	for(int i=1;i<=G.n;++i){
		printf("neighbours(%d): ", i);
		for(int j=1;j<=G.adj[i].size;++j){
			printf("%d ", element_at(G.adj[i], j));
		}
		printf("\n");
	}
	
	return 0;
}

