#include <iostream>
#include <vector>

#define MAX_N 100

typedef struct Graph{
	int n;
	std::vector<int> adj[MAX_N];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	
	for(std::vector<int> v : pG->adj){
		v.clear();
	}
}

void add_edge(Graph *pG, int x, int y){
	pG->adj[x].push_back(y);
	pG->adj[y].push_back(x);
}

int adjacent(Graph *pG, int x, int y){
	for(int i : pG->adj[x]) {
		if(i == y){
			return 1;
		}
	}
	return 0;
}

int main() {
	Graph G;
	int n, m;
	
	std::cin >> n >> m;
	init_graph(&G, n);
	
	for (int e = 0; e < m; e++) {
		int u, v;
		std::cin >> u >> v;
		add_edge(&G, u, v);
	}
	
	for(int i = 1; i <= G.n; ++i){
		for(int j = 1; j <= G.n; ++j){
			if(adjacent(&G, i, j)){
				std::cout << i << " ke voi " << j << "\n";
			}else{
				std::cout << i << " KHONG ke voi " << j << "\n";
			}
		}			
	}
	
	return 0;
}
	
