
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
	graph G(0,"graph_construct.txt");
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

//a la hora de usar kruskal que no chanque al grafo
