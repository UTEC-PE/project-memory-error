
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {

	graph G;

	G.insertNode('A');
	G.insertNode('B');
	G.insertNode('C');
	G.insertNode('D');

	G.insertEdge(1, 0, 1, false);
	G.insertEdge(2, 1, 2, false);
	G.insertEdge(3, 1, 3, false);
	G.insertEdge(4, 2, 3, false);

	G.print();

    return 0;
}

//a la hora de usar kruskal que no chanque al grafo
