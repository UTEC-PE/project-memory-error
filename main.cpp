
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

	//G.BFS('A');

	//G.bipartite();
	// cout << G.conexo();
	/*

	vector<int> myvec;
	myvec.push_back(3);
	myvec.push_back(4);
	myvec.push_back(5);

	if (find(myvec.begin(), myvec.end(), 3)!=myvec.end()) cout << "\nfound\n";
	else cout << "\nnot found\n";
		*/

	return 0;
}

//a la hora de usar kruskal que no chanque al grafo
