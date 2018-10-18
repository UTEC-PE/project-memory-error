#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <limits.h>
#include <map>

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
        typedef Graph<Tr> self; //Para definir tipo de grafo
        typedef Node<self> node; //Para definir todos los nodos mas rapido
        typedef Edge<self> edge; //Para definir todos los edges mas rapido
        typedef vector<node*> NodeSeq; //Alias
        typedef list<edge*> EdgeSeq;
        typedef typename Tr::N N; //Alias
        typedef typename Tr::E E; //Alias
        typedef typename NodeSeq::iterator NodeIte;
        typedef typename EdgeSeq::iterator EdgeIte;

    private:
				int cantidadNodos;
				int cantidadAristas;
        NodeSeq nodes;
        NodeIte ni;
        EdgeIte ei;


    public:
        Graph(string file):nodes(0),cantidadNodos(0),cantidadAristas(0){
					ifstream infile(file);
					int numNodos,nodo1,nodo2,direccion,peso;
					char nombre;
					double x,y;
					infile >> numNodos;
					for(int i = 0;i < numNodos ; i++){
							infile >> nombre >> x >> y;
							insertNode(nombre,x,y);
					}
					while(infile >> peso >> nodo1 >> nodo2 >> direccion){
						if(nodo1 < numNodos || nodo2 < numNodos)
								insertEdge(peso,nodo1,nodo2,direccion);
					}
					// TODO
				}

        void insertNode(N value, double x,double y){
          for(int i=0; i < nodes.size(); i++){ //este nodes es de NodeSeq
              if(value == nodes[i]->getNdata()){
									return;
              }
          }
          node* NewNodo = new node(value,x,y);
          nodes.push_back(NewNodo);
					cantidadNodos++;
        }

        void insertEdge(int peso, int node1, int node2, bool dir){
/*					for(auto ed: nodes[node1]->edges){
						if(ed->getSecondPointer() == nodes[node2] || ed -> getFirstPointer() == nodes[node1]){
							return;
						}
					}
*/					//posicion que quieres conectar
	          edge* NewEdge1 = new edge(peso, nodes[node1], nodes[node2], dir); //este nodes es de edge
	          nodes[node1] -> edges.push_back(NewEdge1);
						cantidadAristas++;
	          if(dir== false){
	             edge* NewEdge2 = new edge(peso, nodes[node2], nodes[node1], dir);
	             nodes[node2] -> edges.push_back(NewEdge2);
						}
        }

        void removeNode(){}

				void setAllNotVisited(){
					for(auto item: nodes){
						item->setNotVisited();
					}
				}

				void prim(){
					setAllNotVisited();
					multimap<E,edge*> EdgeMap;
					int visitedNodes = 1;
					auto ni = nodes[0];
					cout << "PRIM: ";
					while(visitedNodes <= cantidadNodos){
								for(auto ei:ni->edges){
										if(!ei->getSecondPointer()->isVisited()){
														EdgeMap.insert(pair<E,edge*>(ei->getEdata(),ei));
													(*EdgeMap.begin()).second->getFirstPointer()->setVisited();
											}
										}
										ni = (*EdgeMap.begin()).second->getSecondPointer();
										if(!(*EdgeMap.begin()).second->getSecondPointer()->isVisited()){
											cout <<"{"<<(*EdgeMap.begin()).second->getFirstPointer()->getNdata() <<","<<(*EdgeMap.begin()).second->getSecondPointer()->getNdata()<<","<<(*EdgeMap.begin()).first<<"} ";
											(*EdgeMap.begin()).second->getSecondPointer()->setVisited();
										}
										EdgeMap.erase(EdgeMap.begin());
										visitedNodes ++;
								}
		        }

				void kruskal(){
					setAllNotVisited();
					multimap<E,edge*> EdgeMap;
					for(auto ni:nodes){
							for(auto ei:ni->edges){
									if(!ei->getSecondPointer()->isVisited()){
											EdgeMap.insert(pair<E,edge*>(ei->getEdata(),ei));
											(*EdgeMap.begin()).second->getFirstPointer()->setVisited();
										}
								}
						}
				cout << endl << "KRUSKAL: ";
				while(EdgeMap.size() > 0){
						if(!(*EdgeMap.begin()).second->getSecondPointer()->isVisited()){
							cout <<"{"<<(*EdgeMap.begin()).second->getFirstPointer()->getNdata() <<","<<(*EdgeMap.begin()).second->getSecondPointer()->getNdata()<<","<<(*EdgeMap.begin()).first<<"} ";
							(*EdgeMap.begin()).second->getSecondPointer()->setVisited();
						}
						EdgeMap.erase(EdgeMap.begin());
					}
					cout << endl;
        }

        void print(){
            for(auto ni: nodes){
                cout << ni->getNdata() << "| ";
                for(auto item: ni->edges){
                    cout << item->getSecondPointer()->getNdata() <<":"<<item->getEdata()<<' ';
                }
                    cout << endl;
            }
        }
       //list<edge*> kruskal();

};

typedef Graph<Traits> graph;

#endif
