
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
	graph G("graph_construct.txt");
	G.print();
	G.prim();
	G.kruskal();

	return 0;
}

//a la hora de usar kruskal que no chanque al grafo
