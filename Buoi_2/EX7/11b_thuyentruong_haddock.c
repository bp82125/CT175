#include <stdio.h>

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

#define WHITE 0 //dinh ch duoc duyet
#define GRAY 1 //dinh dang cho duyet cac dinh ke cua no
#define BLACK 2 //dinh da duoc duyet

int colour[MAX_VERTICES];
int is_drunk;

void dfs(Graph *pG, int u){
	if(colour[u] == BLACK){
		return; //dinh da duyet roi thi khong duyet nua
	}
	
	colour[u] = GRAY;
		
	for(int i=1;i<=pG->n;++i){
		if(adjacent(pG, u, i)){
			if(colour[i] == WHITE){
				dfs(pG, i); //neu chua duyet thi duyet
			}else if(colour[i] == GRAY){
				is_drunk = 1; //neu dinh con dang trong trang thai cho duyet -> chu trinh
			}
		}
	}
	
	colour[u] = BLACK; //danh dau da duyet
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
		colour[i]=WHITE;
	}
		
	is_drunk = 0;
	
	for(int i=1;i<=n;++i){
		if(colour[i]==WHITE){
			dfs(&G, i);
		}
	}
	
	if(is_drunk){
		printf("NO");
	}else{
		printf("YES");
	}
	
	return 0;
}
