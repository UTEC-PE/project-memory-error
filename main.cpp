
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
	graph G(1);
	G.insertNode('A', 0, 0);
  G.insertNode('B', 0, 0);
  G.insertNode('C', 0, 0);
  G.insertNode('D', 0, 0);
  G.insertNode('E', 0, 0);

  // G.insertEdge(6, 'A', 'C');
	// G.insertEdge(3, 'A', 'D');
  // G.insertEdge(3, 'B', 'A');
  // G.insertEdge(2, 'C', 'D');
  // G.insertEdge(1, 'D', 'C');
  // G.insertEdge(1, 'D', 'B');
  // G.insertEdge(4, 'E', 'B');
	// G.insertEdge(2, 'E', 'D');

	G.insertEdge(4, 'A', 'B');
	G.insertEdge(8, 'A', 'C');
	G.insertEdge(4, 'B', 'A');
	G.insertEdge(1, 'B', 'C');
	G.insertEdge(2, 'B', 'D');
	G.insertEdge(8, 'C', 'A');
	G.insertEdge(4, 'C', 'D');
	G.insertEdge(2, 'C', 'E');
	G.insertEdge(2, 'D', 'B');
	G.insertEdge(4, 'D', 'C');
	G.insertEdge(7, 'D', 'E');
	G.insertEdge(2, 'E', 'C');
	G.insertEdge(7, 'E', 'D');

	G.print();
	cout << endl;
	G.Floyd_Warshall();
	return 0;
}

//a la hora de usar kruskal que no chanque al grafo
