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
        Node* parent;

        Node(N value,double x, double y):data(value),x(x),y(y),visited(false),parent(this){}

        N getNdata(){
          return data;
        }

        double getXdata(){
          return x;
        }

        double getYdata(){
          return y;
        }

        int EdgeSize(){
          return edges.size();
        }

        edge* GetEdge(int i){
          return edges[i];
        }

        bool isVisited(){
          return visited;
        }

        void setVisited(){
          visited = true;
        }

        void setNotVisited(){
          visited = false;
        }


    private:
        N data; //Tipo de dato N del trait
        double x; //solo para graficar en librerias como blue
        double y; //solo para graficar en librerias como blue
        bool visited;
};

#endif
