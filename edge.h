#ifndef EDGE_H
#define EDGE_H

#include "node.h"

template <typename G>
class Edge {
    public:
        typedef typename G::E E;
        typedef typename G::node node;

        node* nodes[2]; //Los dos nodos que conecta mirarlo asi: Node* start, Node* end

    private:
        E data; //Peso numerico
        bool dir; //Si es direccionado o no
};

#endif