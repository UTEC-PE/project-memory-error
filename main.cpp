
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
	graph G(0,"graph_construct3.txt");
	G.print();
	cout << endl;
	bool f;
	G.DFS('G',f);
	cout << endl;
	G.BFS('G');
	cout << endl;
	cout << G.Densidad(0.6) << endl;
	cout << G.bipartite() << endl;
	G.prim('A');
	G.kruskal();
	return 0;
}

//a la hora de usar kruskal que no chanque al grafo
