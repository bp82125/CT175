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
	pG->A[v][u]++;
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0 && pG->A[u][v] > 0;
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

#define WHITE 0
#define GRAY 1
#define BLACK 2

int color[MAX_VERTICES], parent[MAX_VERTICES];
int has_circle, start, end;

void dfs(Graph *pG, int u, int p){	
	if(color[u]==BLACK){
		return;
	}
		
	color[u] = GRAY;
	parent[u] = p;
		
	for(int i=1;i<=pG->n;++i){
		if(adjacent(pG, u, i)){
			if(i==p){
				continue;
			}
			if(color[i]==WHITE){
				dfs(pG, i, u);	
			}else if(color[i]==GRAY){ //neu cac dinh ke dang trong trang thai duyet -> chu trinh
				start = u;
				end = i;
				has_circle = 1;
			}
		}
	}
	color[u] = BLACK;
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
		color[i] = WHITE;
	}
	
	has_circle = 0;
	
	for(int i=1;i<=n;++i){
		if(color[i]==WHITE){
			dfs(&G, i,-1);
		}
	}
	
	if(has_circle){
		
		int arr[n], index = 0;
		
		arr[index++] = end;
		arr[index++] = start;
		
		int temp = parent[start];
		while(temp!=parent[end]){
			arr[index++] = temp;
			temp = parent[temp];
		}
		
		for(int i=index-1;i>=0;--i){
			printf("%d ", arr[i]);
		}
	}else{
		printf("-1");
	}
	
	return 0;
}
