#include <iostream>
#include <limits.h>
#include <queue>

using namespace std;

#define MAXN 100
#define NO_EDGE false
#define oo INT_MAX
#define min(a,b) (a<b)?a:b 

typedef struct Graph{
	int C[MAXN][MAXN];
	int F[MAXN][MAXN];
	int n,m;
}Graph;

typedef struct Label{
	int dir;
	int parent;
	int sigma;
}Label;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	
	for(auto& rows : pG->C){
		for(auto& elements : rows){
			elements = 0;
		}
	}
}

void add_edge(Graph *pG, int u, int v, int c){
	pG->C[u][v] = c;
	pG->m++;
}

void init_flow(Graph *pG){
	for(auto& rows : pG->F){
		for(auto& elements : rows){
			elements = 0;
		}
	}
}

Label labels[MAXN];

struct Comparator{
	bool operator()(int const &p1, int const &p2){
		return labels[p1].sigma < labels[p2].sigma;
	}	
};

int FordFulkerson(Graph *pG, int s, int t){
	init_flow(pG);
	int max_flow = 0;
	
	priority_queue<int, vector<int>, Comparator> Q;
	do{
		for(auto &e : labels){
			e.dir = 0;
		}
		
		labels[s].dir = +1;
		labels[s].parent = s;
		labels[s].sigma = oo;
		
		Q = priority_queue<int, vector<int>, Comparator>();
		Q.push(s);
		
		bool found = false;
		while(!Q.empty()){
			int u = Q.top(); Q.pop();
			// cung thuan
			for(int v = 1; v <= pG->n; ++v){
				if(pG->C[u][v] != NO_EDGE 
					&& labels[v].dir == 0 
					&& pG->F[u][v] < pG->C[u][v]){
						labels[v].dir = +1;
						labels[v].parent = u;
						labels[v].sigma = min(labels[u].sigma, pG->C[u][v] - pG->F[u][v]); // luong co the tang con lai va sigma
						Q.push(v);
				}
			}
			
			// cung nghich
			for(int p = 1; p <= pG->n; ++p){
				if(pG->C[p][u] != NO_EDGE 
					 && labels[p].dir == 0 
					 && pG->F[p][u] > 0){
						labels[p].dir = -1;
						labels[p].parent = u;
						labels[p].sigma = min(labels[u].sigma, pG->F[p][u]); // luong co the tang con lai va sigma
						Q.push(p);
				}
			}
			
			if(labels[t].dir != 0){
				found = true;
				break;
			}
		}
		
		if(found){
			int sigma = labels[t].sigma;
			
			int u = t;
			
			while(u != s){
				int p = labels[u].parent;
				if(labels[u].dir > 0){
					pG->F[p][u] += sigma;
				}else{
					pG->F[p][u] -= sigma;
				}
				u = p;
			}
			
			max_flow += sigma;
		}else{
			break;
		}
	}while(true);
	
	return max_flow;
}

int main(void){
	Graph G;
	int n, m;
	freopen("dt.txt", "r", stdin);
	cin >> n >> m;
	
	init_graph(&G, n);
	for(int e = 0; e < m; ++e){
		int u, v, c;
		cin >> u >> v >> c;
		add_edge(&G, u, v, c);
	}

	int max_flow = FordFulkerson(&G, 1, n);
	
	cout << "Max flow: " << max_flow << endl;
	
	return 0;
	
}


