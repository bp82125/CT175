#include <stdio.h>
#include "list.c"

#define MAX_VERTICES 100

typedef struct {
	int n;
	int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

void init_graph(Graph *pG, int n){
	pG->n=n;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			pG->A[i][j]=0;
		}
	}
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v]++;
	pG->A[v][u]++;
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0;
}

void print_adjacent(Graph *pG, int u){
	printf("adjacent[%d] = ", u);
	for(int v = 1; v<=pG->n;++v){
		if(adjacent(pG, u, v)){
			printf("%d ", v);
		}
	}
	printf("\n");
}

#define NO_COLOR 0 //dinh ch duoc duyet
#define BLUE 1 //dinh dang cho duyet cac dinh ke cua no
#define RED 2 //dinh da duoc duyet

int colour[MAX_VERTICES];
List team_red, team_blue;
int has_conflict;

void colorize(Graph *pG, int u, int c){
	if(colour[u]!=NO_COLOR){
		return;
	}
	
	colour[u] = c;
	if(c == BLUE){
		push_back(&team_blue, u);
	}else{
		push_back(&team_red, u);
	}
	
	for(int i = 1; i<=pG->n;++i){
		if(adjacent(pG, u, i)){
			if(colour[i]==NO_COLOR){
				colorize(pG, i, 3-c); // 3-c la mau doi lap voi mau cua u
			}else if(colour[i]==colour[u]){
				has_conflict = 1;
			}
		}
	}
}

int main(void){
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for(int i=1;i<=n;++i){
		colour[i] = NO_COLOR;
	}
	
	make_null_list(&team_blue);
	make_null_list(&team_red);
	has_conflict = 0;
	
	for(int i = 1;i<=n;++i){
		if(colour[i]==NO_COLOR){
			colorize(&G, i, BLUE);
		}
	}
	
	if(has_conflict){
		printf("NO");
	}else{
		sort(&team_blue);
		sort(&team_red);
		print_list(team_blue);
		print_list(team_red);
	}
	
	return 0;
}
