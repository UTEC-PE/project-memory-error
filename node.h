#ifndef NODE_H
#define NODE_H

template <typename G>
class Node {
    public:
        typedef typename G::N N;
        typedef typename G::E E;
        typedef typename G::edge edge;
        typedef typename G::EdgeSeq EdgeSeq;

        EdgeSeq edges; //lista de adyacencia, list de edges

    private:
        N data; //Tipo de fato N del trait
        double x; //solo para graficar en librerias como blue
        double y; //solo para graficar en librerias como blue
};

#endif