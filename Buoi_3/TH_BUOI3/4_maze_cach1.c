#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 500


typedef struct Maze{
	int A[MAX_VERTICES][MAX_VERTICES];
	int n,m;
}Maze;

void read_maze(Maze *pM){
	scanf("%d%d", &pM->n, &pM->m);
	
	for(int i=0;i<pM->n;++i){
		for(int j=0;j<pM->m;++j){
			int temp;
			scanf("%d", &temp);
			pM->A[i][j] = temp;
		}
	}
}

int pi[MAX_VERTICES];
int mark[MAX_VERTICES];
int p[MAX_VERTICES];

void MooreDijkstra(Maze *pM, int u){

	
	for(int i = 1; i<=pM->m*pM->n;++i){
		pi[i] = INT_MAX;
		mark[i] = 0;
		p[i] = 0;
	}
	
	pi[u] = 0;
	p[u] = -1;
	
	int di[] = {-1, 1, 0, 0};
	int dj[] = {0, 0, -1, 1};
	
	for(int i=1;i<pM->m*pM->n;++i){
		int min_index, min_pi = INT_MAX;
		
		for(int j=1;j<=pM->m*pM->n;++j){
			if(pi[j] < min_pi && !mark[j]){
				min_pi = pi[j];
				min_index = j;
			}
		}
		
		mark[min_index] = 1;
		
		int min_index_i = (min_index - 1)/pM->m;
		int min_index_j = (min_index - 1)%pM->m;
		
		for(int k = 0; k<4;k++){
			int ii = min_index_i + di[k];
			int jj = min_index_j + dj[k];
			
			if(ii >= 0 && ii < pM->n && jj >= 0 && jj < pM->m){
				int v = ii*pM->m + jj + 1;
				if(!mark[v] && pi[min_index] + pM->A[ii][jj] < pi[v]){
					pi[v] = pi[min_index] + pM->A[ii][jj];
					p[v] = min_index;
				}
			}
			
		}
		
	}
}

void print_path(Maze *pM, int start, int end){
	
	printf("Path from %d to %d, weight = %d\n", start, end, pi[end]);
	
	int child[pM->n*pM->m + 1];
	
	child[end] = 0;
	while(end!=start){
		child[p[end]] = end;
		end = p[end];
	}
	
	while(child[end]!=0){
		printf("%d -> ", end);
		end = child[end];
	}
	printf("%d", end);
}

int main(void){
	freopen("dt.txt", "r", stdin);
	
	Maze M;
	
	read_maze(&M);
		
	MooreDijkstra(&M, 1);
	
	print_path(&M, 1, M.n*M.m);
	
	return 0;
}
