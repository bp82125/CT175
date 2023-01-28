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

int degree(Graph *pG, int x){
	return pG->adj[x].size();
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
		std::cout << "degree" << "(" << i << ")" << " = " << degree(&G,i) << std::endl;
	}
	return 0;
}
	
