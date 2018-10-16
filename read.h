#ifndef READ_H
#define READ_H

#include "graph.h"
#include <fstream>
/**
 * Clase de ayuda para leer el grafo desde un archivo,
 * no es necesario que la utilicen, podrían implementar su lector
 * desde su grafo o algún otro lado
 **/
template <typename G>
class Read {
	typedef typename G::N N;
	typedef typename G::E E;
	graph<G> nuevografo;
	public:
		Read(string file) {
			ifstream infile(file);
			int numNodos,nodo1,nodo2,direccion,peso;
			char nombre;
			double x,y;
			infile >> numNodos;
			for(int i = 0;i < numNodos ; i++){
					infile >> nombre >> x >> y;
					nuevografo.insertNode(nombre);
			}
			for(int j = 0; j < numNodos; j++){
					infile >> peso >> nodo1 >> nodo2 >> direccion;
					nuevografo.insertEdge(0,nodo1,nodo2,direccion);
			}
				    // TODO
    }

		graph& getGraph() {
			return nuevografo;
			// TODO
    }
};


/*
 * Número de Nodos
 *
 * Letra - X - Y
 *
 * Nodo 1 - Nodo 2 - Direccion
 */


#endif
