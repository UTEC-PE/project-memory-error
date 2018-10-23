#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <limits.h>
#include <map>
#include <queue>
#include <stack>

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
        NodeSeq nodes;
        NodeIte ni;
        EdgeIte ei;
        bool dir;


    public:
        Graph(){}

        Graph(bool dir, string file):nodes(0), dir(dir){
					ifstream infile(file);
					int numNodos,nodo1,nodo2,direccion,peso;
					char nombre;
					double x,y;
					infile >> numNodos;
					for(int i = 0;i < numNodos ; i++){
							infile >> nombre >> x >> y;
							insertNode(nombre,x,y);
					}
					while(infile >> peso >> nodo1 >> nodo2){
						if(nodo1 < nodes.size() && nodo2 < nodes.size() || nodo1 == nodo2)
								insertEdge(peso,nodo1,nodo2);
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
                sizeEdges += (*ni)->edges.size();
            }

            dens = sizeEdges/(sizeNodes*(sizeNodes-1));

            if(dens>cota){
                return true;
            }
            else{
                return false;
            }
        }

				void findGrado(N value){

					if(dir==false){

						for(ni=nodes.begin(); ni!=nodes.end(); ni++){
							if((*ni)->getNdata() == value){
								cout << "Grado total para no direccionado: " << (*ni)->edges.size() << endl;
							}
						}

					}
					else{
						int gsalida = 0;
						int gentrada = 0;
						int gtotal = 0;

						for(ni=nodes.begin(); ni!=nodes.end(); ni++){
							if((*ni)->getNdata() == value){
								gsalida = (*ni)->edges.size();
								gtotal += (*ni)->edges.size();
							}
							else{
								for(ei=(*ni)->edges.begin(); ei!=(*ni)->edges.end(); ei++){
									if((*ei)->nodes[1]->getNdata()==value){
										gtotal += 1;
										gentrada +=1;
									}
								}
							}
						}

						cout << "Grado total para direccionado: " << gtotal << endl;
						cout << "Grado de salida para direccionado: " << gsalida << endl;
						cout << "Grado de entrada para direccionado: " << gentrada << endl;

						if(gsalida==0){
							cout << value << " es un nodo hundido" << endl;
						}
						if(gentrada==0){
							cout << value << " es un nodo fuente" << endl;
						}

					}

				}

				void BFS(N startN){
					queue<N> myqueue;
					vector<N> visited;

					myqueue.push(startN);
					visited.push_back(startN);

					int lvl=1;
					bool lvlh=false;

					while(!myqueue.empty()){

						N current = myqueue.front();
						for(ni=nodes.begin();ni!=nodes.end();++ni){
							if(((*ni)->getNdata())==current){
								for(ei=(*ni)->edges.begin(); ei!=(*ni)->edges.end(); ++ei){
									if((find(visited.begin(), visited.end(),(*ei)->nodes[1]->getNdata()) != visited.end()) == false){ //If edge not in visited
										myqueue.push((*ei)->nodes[1]->getNdata());
										visited.push_back((*ei)->nodes[1]->getNdata());
										cout << (*ni)->getNdata() << (*ei)->nodes[1]->getNdata() << " | ";
										lvlh=true;
									}
								}
								lvl+=lvlh;
								lvlh=false;
								myqueue.pop();
							}
						}

					}
				}

				bool bipartite(N startN){ //only works for strongly connected

					queue<N> myqueue;
					vector<N> visited;

					myqueue.push(startN);
					visited.push_back(startN);

					int lvl=1;
					bool lvlh=false;

					while(!myqueue.empty()){

						N current = myqueue.front();
						for(ni=nodes.begin();ni!=nodes.end();++ni){
							if(((*ni)->getNdata())==current){
								for(ei=(*ni)->edges.begin(); ei!=(*ni)->edges.end(); ++ei){
									if((find(visited.begin(), visited.end(),(*ei)->nodes[1]->getNdata()) != visited.end()) == false){ //If edge not in visited
										myqueue.push((*ei)->nodes[1]->getNdata());
										visited.push_back((*ei)->nodes[1]->getNdata());
										cout << (*ni)->getNdata() << (*ei)->nodes[1]->getNdata() << " | ";
										lvlh=true;
									}
								}
								lvl+=lvlh;
								lvlh=false;
								myqueue.pop();
							}
						}

					}
				}

				void DFS(N startN, bool &fc){
					stack<N> mystack;
					vector<N> visited;

					mystack.push(startN);
					visited.push_back(startN);

					while(!mystack.empty()){
						N current = mystack.top();
						for(ni=nodes.begin();ni!=nodes.end();++ni){
							if(((*ni)->getNdata())==current){
								for(ei=(*ni)->edges.begin(); ei!=(*ni)->edges.end(); ++ei){
									if((find(visited.begin(), visited.end(),(*ei)->nodes[1]->getNdata()) != visited.end()) == false){ //if *ei not in visited
										mystack.push((*ei)->nodes[1]->getNdata());
										visited.push_back((*ei)->nodes[1]->getNdata());
										cout << (*ni)->getNdata() << (*ei)->nodes[1]->getNdata() << " | ";
										break;
									}
									else{
										mystack.pop();
									}
								}
							}
						}

					}

					//si dfs ha visitado todos los nodos
					if(visited.size() == nodes.size()){fc = true;}
					else{fc=false;}
				}

				bool stronglyConnected(N startN){

					if(dir){
						bool fc;

						DFS(startN, fc);
						if(fc==false){return false;}
						else{

							getTranspose().DFS(startN, fc);
							if(fc==false){return false;}
							else{return true;}

						}

					}
					else{
						throw "Only works for directed graphs";
					}

				}

				self getTranspose(){
					self transpose(dir);
					for(ni=nodes.begin();ni!=nodes.end();++ni){
						transpose.insertNode((*ni)->getNdata());
					}
					for(ni=nodes.begin();ni!=nodes.end();++ni){
						for(ei=(*ni)->edges.begin(); ei!=(*ni)->edges.end(); ++ei){
							transpose.insertEdge(
							(*ei)->getEdata(),
							distance(nodes.begin(), find(nodes.begin(), nodes.end(), (*ei)->nodes[1])),
							distance(nodes.begin(), find(nodes.begin(), nodes.end(), *ni))
							);
						}
					}
					return transpose;
				}

				void setAllNotVisited(){
					for(auto item: nodes){
						item->setNotVisited();
					}
				}

				void prim(){
					setAllNotVisited();
					multimap<E,edge*> EdgeMap;
					int visitedNodes = 0;
					auto ni = nodes[0];
					cout << "PRIM: ";
					while(visitedNodes < nodes.size()){
						visitedNodes ++;
						for(auto ei:ni->edges){
							if(!ei->getSecondPointer()->isVisited()){
									EdgeMap.insert(pair<E,edge*>(ei->getEdata(),ei));
							}
						}
                        (*EdgeMap.begin()).second->getFirstPointer()->setVisited();
						if(!(*EdgeMap.begin()).second->getSecondPointer()->isVisited()){
                            ni = (*EdgeMap.begin()).second->getSecondPointer();
                            cout <<"{"<<(*EdgeMap.begin()).second->getFirstPointer()->getNdata() <<","<<(*EdgeMap.begin()).second->getSecondPointer()->getNdata()<<","<<(*EdgeMap.begin()).first<<"} ";
							(*EdgeMap.begin()).second->getSecondPointer()->setVisited();
						}
						EdgeMap.erase(EdgeMap.begin());
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


};

typedef Graph<Traits> graph;

#endif
