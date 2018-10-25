
#include <iostream>
#include <vector>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
	graph G(0,"graph_construct.txt");


	// G.insertNode('A', 0, 0);
	// G.insertNode('B', 0, 0);
	// G.insertNode('C', 0, 0);
	// G.insertNode('D', 0, 0);
	// G.insertNode('E', 0, 0);
	// G.insertNode('F', 0, 0);
	// G.insertNode('G', 0, 0);
	//
	// // G.insertEdge(1, 0, 1);
	// // G.insertEdge(1, 0, 3);
	// // G.insertEdge(1, 1, 2);
	// // G.insertEdge(1, 1, 3);
	// // G.insertEdge(1, 2, 3);
	// // G.insertEdge(1, 3, 4);
	// // G.insertEdge(1, 3, 5);
	// // G.insertEdge(1, 4, 5);
	//
	// G.insertEdge(1, 0, 1);
	// G.insertEdge(2, 0, 4);
	// G.insertEdge(3, 1, 2);
	// G.insertEdge(4, 1, 6);
	// G.insertEdge(4, 2, 4);
	// G.insertEdge(4, 2, 3);
	// G.insertEdge(4, 4, 5);
	// G.insertEdge(4, 4, 6);

	G.print();
	G.BFS('D');
	G.findGrado('A');
	if(G.Densidad(0.5))
		cout << "EL GRAFO ES DENSO"<< endl;
	else
		cout << "EL GRAFO NO ES DENSO" << endl;
	graph prim = G.prim('A');
	prim.print();
	graph kruskal = G.kruskal();
	kruskal.print();
	return 0;
}
