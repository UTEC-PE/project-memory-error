
#include <iostream>
#include <vector>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
	graph G(1);

	G.insertNode('A', 0, 0);
  G.insertNode('B', 0, 0);
  G.insertNode('C', 0, 0);
  G.insertNode('D', 0, 0);
  G.insertNode('S', 0, 0);

  G.insertEdge(6, 'S', 'A');
  G.insertEdge(7, 'S', 'C');
  G.insertEdge(5, 'A', 'B');
  G.insertEdge(-4, 'A', 'D');
  G.insertEdge(8, 'A', 'C');
  G.insertEdge(-2, 'B', 'A');
  G.insertEdge(-3, 'C', 'B');
  G.insertEdge(9, 'C', 'D');
  G.insertEdge(8, 'D', 'S');
  G.insertEdge(7, 'D', 'B');

	G.print();
	cout << endl;
	G.Bellman_Ford('S');
	return 0;
}

//que no sume A
