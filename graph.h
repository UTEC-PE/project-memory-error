#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include<iostream>

#include "node.h"
#include "edge.h"

using namespace std;

class Traits {
	public:
		typedef char N; //Node es de tipo char
		typedef int E; //Edge es de tipo int
};

template <typename Tr>
class Graph {
    public:
        typedef Graph<Tr> self; //Para defi
        typedef Node<self> node; //Para definir todos los nodos mas rapido
        typedef Edge<self> edge; //Para definir todos los edges mas rapido
        typedef vector<node*> NodeSeq; //Alias
        typedef list<edge*> EdgeSeq;
        typedef typename Tr::N N; //Alias
        typedef typename Tr::E E; //Alias
        typedef typename NodeSeq::iterator NodeIte;
        typedef typename EdgeSeq::iterator EdgeIte;

    private:
        NodeSeq nodes;
        NodeIte ni;
        EdgeIte ei;


    public:
        Graph():nodes(0){}

        void insertNode(N value){

          for(int i=0; nodes.size() < i; i++){ //este nodes es de NodeSeq
              if(value==(nodes[i])->getNdata()){
                  throw "Ya existe un nodo con el mismo nombre";
              }
          }

					node* NewNodo = new node(value);
					nodes.push_back(NewNodo);
				}

        void insertEdge(E peso, int node1, int node2, bool dir){ //posicion que quieres conectar
            //chequear si value esta en el vector maybe later

            edge* NewEdge1 = new edge(peso, nodes[node1], nodes[node2], dir); //este nodes es de edge
            nodes[node1] -> edges.push_back(NewEdge1);

            if(dir==false){
                edge* NewEdge2 = new edge(peso, nodes[node1], nodes[node2], dir);
                nodes[node2] -> edges.push_back(NewEdge2);
            }
        }

				void removeNode()

				void print(){
					for(ni = nodes.begin(); ni != nodes.end(); ni++){
						cout << (*ni)->getNdata() << ' ';
						for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
							cout << (*ei)->getEdata() << ' ';
						}
						cout << endl;
					}
				}

       //list<edge*> kruskal();

};

typedef Graph<Traits> graph;

#endif
