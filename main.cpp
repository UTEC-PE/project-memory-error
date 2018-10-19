
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {

	graph G(true);

	G.insertNode('A');
	G.insertNode('B');
	G.insertNode('C');
	G.insertNode('D');

	G.insertEdge(6, 0, 1);
	G.insertEdge(7, 1, 2);
	G.insertEdge(8, 1, 3);
	G.insertEdge(9, 2, 3);
	G.insertEdge(10, 3, 0);

	G.print();

	cout << endl;

	cout << G.stronglyConnected('A');

	cout << endl;

	G.print();

    return 0;
}

//a la hora de usar kruskal que no chanque al grafo
