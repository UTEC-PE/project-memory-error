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
        bool dir;


    public:
        Graph(bool dir):nodes(0), dir(dir){}



        void insertNode(N value){

          for(ni=nodes.begin(); ni != nodes.end(); ni++){ //este nodes es de NodeSeq
              if(value==(*ni)->getNdata()){
                  throw "Ya existe un nodo con el mismo nombre";
              }
          }

					node* NewNodo = new node(value);
					nodes.push_back(NewNodo);
				}

        void insertEdge(E peso, int node1, int node2){ //posicion que quieres conectar
            //Cambiar de posicion a char

            edge* NewEdge1 = new edge(peso, nodes[node1], nodes[node2]);
            nodes[node1] -> edges.push_back(NewEdge1);

            if(dir==false){
                edge* NewEdge2 = new edge(peso, nodes[node2], nodes[node1]);
                nodes[node2] -> edges.push_back(NewEdge2);
            }

        }

        void removeEdge(N node1, N node2){ //node1->node2 if dir=true

            for(ni = nodes.begin(); ni != nodes.end(); ni++){
                if((*ni)->getNdata() == node1){
                    for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
                        if(((*ei)->nodes[1])->getNdata() == node2){
                            (*ni) -> edges.remove(*ei);
                            break;
                        }
                    }
                }

                if(dir==false){
                    if((*ni)->getNdata() == node2){
                        for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
                            if(((*ei)->nodes[0])->getNdata() == node1){
                                (*ni) -> edges.remove(*ei);
                                break;
                            }
                        }
                    }
                }
            }

        }

        void removeNode(N value){

	        for(ni = nodes.begin(); ni != nodes.end(); ni++){
            if((*ni)->getNdata()==value){
                (*ni)->edges.clear(); //borra toda la lista adjacente
                nodes.erase(ni); //borra nodo del vector nodes
								break;
            }
            for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
                if((*ei)->nodes[1]->getNdata()==value){
                    (*ni)->edges.remove(*ei);
										break;
                }
            }
	        }
        }

				bool findNode(N node){
					for(ni = nodes.begin(); ni != nodes.end(); ni++){
						if((*ni)->getNdata() == node){
							return true;
							break;
						}
					}
					return false;
				}

				bool findEdge(N node1, N node2){
					for(ni = nodes.begin(); ni != nodes.end(); ni++){
						if((*ni)->getNdata() == node1){
							for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
								if((*ei)->nodes[1]->getNdata()==node2){
									return true;
									break;
								}
							}
						}
					}
					return false;
				}

        bool Densidad(float cota){

            float sizeNodes = nodes.size();
            float sizeEdges = 0;
            float dens = 0;

            for(ni = nodes.begin(); ni != nodes.end(); ni++){
                for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
                    sizeEdges += 1;
                }
            }

            dens = sizeEdges/(sizeNodes*(sizeNodes-1));

            if(dens>cota){
                return true;
            }
            else{
                return false;
            }
        }


       //list<edge*> kruskal();

        void print(){
            for (ni=nodes.begin();ni!=nodes.end();++ni){
                cout << (*ni)->getNdata() << endl;
                for(ei=(*ni)->edges.begin();ei!=(*ni)->edges.end();++ei){
                    cout <<"peso : ";
                    cout << (*ei)->getEdata();
                    cout << ", nodo : ";
                    if((*ni)->getNdata()!= (*ei)->nodes[1]->getNdata()){
                        cout<<(*ei)->nodes[1]->getNdata();
                    }
                    else{
                        cout<<"-----" <<(*ei)->nodes[0]->getNdata();
                    }
                    cout <<" | ";
                }
                cout <<endl;
            }
        }

};

typedef Graph<Traits> graph;

#endif
