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

typedef struct Vertex{
	int i, j, data;
}Vertex;

void find_min(Maze *pM, Vertex *min_pi){
	min_pi->data = INT_MAX;
	for(int i=0;i<pM->n;i++){
		for(int j=0;j<pM->m;j++){
			if(pi[i][j] < min_pi->data && !mark[i][j]){
				min_pi->data = pi[i][j];
				min_pi->i = i;
				min_pi->j = j;
			}
		}
	}
}

void MooreDijkstra(Maze *pM, Vertex u){
	int max_vertices = pM->m * pM->n;
	
	for(int i=0;i<pM->n;i++){
		for(int j=0;j<pM->m;j++){
			pi[i][j] = INT_MAX;
			mark[i][j] = 0;
			p[i][j] = 0;
		}
	}
	
	pi[u.i][u.j] = 0;
	p[u.i][u.j] = -1;
	
	int di[] = {-1 , 1, 0, 0};
	int dj[] = {0, 0, -1, 1};
	
	for(int i=1;i<=max_vertices;++i){
		Vertex min_pi;
		
		find_min(pM, &min_pi);
		
		mark[min_pi.i][min_pi.j] = 1;
		
		for(int k=0;k<4;++k){
			Vertex v;
			v.i = min_pi.i + di[k];
			v.j = min_pi.j + dj[k];
			
			if(v.i >= 0 && v.i < pM->n && v.j >= 0 && v.j < pM->m){
				if(!mark[v.i][v.j] && pi[min_pi.i][min_pi.j] + pM->A[v.i][v.j] < pi[v.i][v.j]){
					pi[v.i][v.j] = pi[min_pi.i][min_pi.j] + pM->A[v.i][v.j];
					p[v.i][v.j] = min_pi.i * pM->m + min_pi.j + 1;
				}
			}
		}
	}
}

void print_path(Maze *pM, Vertex start, Vertex end){
	
	int max_vertices = pM->n*pM->m;
	
	printf("Path from (%d,%d) to (%d,%d), weight = %d\n", start.i, start.j, end.i, end.j, pi[end.i][end.j]);
	
	int temp = end.i*pM->m + end.j + 1;
	
	int child[max_vertices + 1][max_vertices + 1];
	
	child[end.i][end.j] = 0;
	while((temp-1)/pM->m != start.i || (temp-1)%pM->m != start.j){
		int parent = p[(temp-1)/pM->m][(temp-1)%pM->m];
		child[(parent-1)/pM->m][(parent-1)%pM->m] = temp;
		temp = parent;
	}
	
	while(child[(temp-1)/pM->m][(temp-1)%pM->m]!=0){
		printf("%d -> ", temp);
		temp = child[(temp-1)/pM->m][(temp-1)%pM->m];
	}
	printf("%d", temp);		
}

int main(void){
	freopen("dt.txt", "r", stdin);
	
	Maze M;
	
	read_maze(&M);
	
	Vertex start = {0, 0, 0};
	Vertex end = {M.n-1, M.m-1, 0};
	MooreDijkstra(&M, start);
	
	print_path(&M,start, end);
	
	return 0;
}
