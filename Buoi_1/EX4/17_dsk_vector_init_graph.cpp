#include <iostream>
#include <vector>

#define MAX_N 100

typedef struct Graph{
	int n;
	std::vector<int> adj[MAX_N];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	
	for(std::vector<int> i : pG->adj){
		i.clear();
	}
}

int main() {
	Graph G;
	init_graph(&G, 5);
	std::cout << "Do thi co " << G.n << " dinh va 0 cung. "; 
	return 0;
}
