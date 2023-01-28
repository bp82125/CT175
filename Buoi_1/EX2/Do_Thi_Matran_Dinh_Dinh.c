#include <stdio.h>

#define MAX_VERTICES 20

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

void get_all_degrees(Graph G){
	for(int i=1;i<=G.n;++i){
		printf("degree(%d) = %d\n", i, degree(G,i));	
	}
}

int main(int argc, char *argv[]){
	Graph G;
	init_Graph(&G, 6);
	add_Edge(&G,2,6);
	add_Edge(&G,5,6);
	add_Edge(&G,3,4);
	add_Edge(&G,1,4);
	add_Edge(&G,1,2);
	add_Edge(&G,1,5);
	print_Graph(G);
	//printf("%d", isAdjacent(&G,1,2));
	get_all_degrees(G);
	return 0;
}
