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

int pi[MAX_VERTICES][MAX_VERTICES];
int mark[MAX_VERTICES][MAX_VERTICES];
int p[MAX_VERTICES][MAX_VERTICES];

void find_min(Maze *pM, int *min_pi, int *min_pi_i, int *min_pi_j){
	*min_pi = INT_MAX;
	for(int i=0;i<pM->n;i++){
		for(int j=0;j<pM->m;j++){
			if(pi[i][j] < *min_pi && !mark[i][j]){
				*min_pi = pi[i][j];
				*min_pi_i = i;
				*min_pi_j = j;
			}
		}
	}
}

void MooreDijkstra(Maze *pM, int u_i, int u_j){
	for(int i=0;i<pM->n;i++){
		for(int j=0;j<pM->m;j++){
			pi[i][j] = INT_MAX;
			mark[i][j] = 0;
			p[i][j] = 0;
		}
	}
	
	pi[u_i][u_j] = 0;
	p[u_i][u_j] = -1;
	
	int di[] = {-1 , 1, 0, 0};
	int dj[] = {0, 0, -1, 1};
	
	for(int i=1;i<=pM->n*pM->m-1;++i){
		int min_pi, min_pi_i, min_pi_j;
		
		find_min(pM, &min_pi, &min_pi_i, &min_pi_j);
		
		mark[min_pi_i][min_pi_j] = 1;
		
		for(int k=0;k<4;++k){
			int v_i = min_pi_i + di[k];
			int v_j = min_pi_j + dj[k];
			
			if(v_i >= 0 && v_i < pM->n && v_j >= 0 && v_j < pM->m){
				if(!mark[v_i][v_j] && pi[min_pi_i][min_pi_j] + pM->A[v_i][v_j] < pi[v_i][v_j]){
					pi[v_i][v_j] = pi[min_pi_i][min_pi_j] + pM->A[v_i][v_j];
					p[v_i][v_j] = min_pi_i * pM->m + min_pi_j + 1;
				}
			}
		}
	}
}

void print_path(Maze *pM, int start_i, int start_j, int end_i, int end_j){
	
	printf("Path from (%d,%d) to (%d,%d), weight = %d\n", start_i, start_j, end_i, end_j, pi[end_i][end_j]);
	
	int end = end_i*pM->m + end_j + 1;
	
	int child[pM->n*pM->m + 1][pM->n*pM->m + 1];
	
	child[end_i][end_j] = 0;
	while((end-1)/pM->m != start_i || (end-1)%pM->m != start_j){
		int parent = p[(end-1)/pM->m][(end-1)%pM->m];
		child[(parent-1)/pM->m][(parent-1)%pM->m] = end;
		end = parent;
	}
	
	while(child[(end-1)/pM->m][(end-1)%pM->m]!=0){
		printf("%d -> ", end);
		end = child[(end-1)/pM->m][(end-1)%pM->m];
	}
	printf("%d", end);		
}

int main(void){
	freopen("dt.txt", "r", stdin);
	
	Maze M;
	
	read_maze(&M);
		
	MooreDijkstra(&M, 0, 0);
	
	print_path(&M, 0,0, M.n-1, M.m-1);
	
	return 0;
}
