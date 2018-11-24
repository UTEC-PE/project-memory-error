
#include <iostream>
#include <vector>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
	graph G(0);

  G.insertNode('A', 25, 90);
  G.insertNode('B', 10, 70);
  G.insertNode('C', 17, 53);
  G.insertNode('D', 34, 65);
  G.insertNode('E', 32, 44);
  G.insertNode('F', 56, 85);
  G.insertNode('G', 46, 73);
  G.insertNode('H', 66, 73);
  G.insertNode('I', 56, 6);
  G.insertNode('J', 47, 37);

  G.insertEdge(3, 'A', 'F');
  G.insertEdge(6, 'A', 'B');
  G.insertEdge(2, 'B', 'D');
  G.insertEdge(3, 'B', 'C');
  G.insertEdge(1, 'C', 'D');
  G.insertEdge(5, 'C', 'E');
  G.insertEdge(8, 'D', 'E');
  G.insertEdge(5, 'E', 'I');
  G.insertEdge(5, 'E', 'J');
  G.insertEdge(3, 'I', 'J');
  G.insertEdge(3, 'G', 'I');
  G.insertEdge(1, 'G', 'F');
  G.insertEdge(7, 'F', 'H');
  G.insertEdge(2, 'I', 'H');

	G.print();
	cout << endl;
	G.greedyBFS('A', 'E');
	return 0;
}

//que no sume A
