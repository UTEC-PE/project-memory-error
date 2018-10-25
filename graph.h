#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <algorithm>
#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <limits.h>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include "node.h"
#include "edge.h"

using namespace std;

class Traits {
	public:
		typedef int N; //Node es de tipo char
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
        Graph(bool dir):dir(dir){}
        Graph(bool dir, string file):nodes(0), dir(dir){
					ifstream infile(file);
					int numNodos,peso;
					N nombre,nodo1,nodo2;
					double x,y;
					infile >> numNodos;
					for(int i = 0;i < numNodos ; i++){
							infile >> nombre >> x >> y;
							insertNode(nombre,x,y);
					}
					while(infile >> peso >> nodo1 >> nodo2){
						if(nodo1 != nodo2)
								insertEdge(peso,nodo1,nodo2);
					}
					// TODO
				}
//---------------------INSERT AND REMOVE--------------------------------
				void insertNode(N value, double x,double y){
					for(int i=0; i < nodes.size(); i++){ //este nodes es de NodeSeq
							if(value == nodes[i]->getNdata()){
									return;
							}
					}
					node* NewNodo = new node(value,x,y);
					nodes.push_back(NewNodo);
				}

        void insertEdge(E peso, N node1, N node2){ //posicion que quieres conectar
            //Cambiar de posicion a char
						node* nodoinsert1 = findNode(node1);
						node* nodoinsert2 = findNode(node2);

            edge* NewEdge1 = new edge(peso, nodoinsert1, nodoinsert2);
            nodoinsert1 -> edges.push_back(NewEdge1);

            if(dir==false){
                edge* NewEdge2 = new edge(peso, nodoinsert2, nodoinsert1);
                nodoinsert2 -> edges.push_back(NewEdge2);
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
//-----------------------FINDS---------------------
				node* findNode(N node){
					for(ni = nodes.begin(); ni != nodes.end(); ni++){
						if((*ni)->getNdata() == node){
							return (*ni);
							break;
						}
					}
					return nullptr;
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

				node* findParent(node* ni){
					node* current = ni;
					while(current -> parent != current){
						current = current -> parent;
					}
					return current;
				}

				bool unionParent(node* ni1,node* ni2){
					node* parent1 = findParent(ni1);
					node* parent2 = findParent(ni2);
					if(parent1 != parent2){
						parent2->parent = parent1;
						return true;
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
//--------------------GRADO Y TIPO---------------------------------
				void findGrado(N value){

					if(dir==false){

						for(ni=nodes.begin(); ni!=nodes.end(); ni++){
							if((*ni)->getNdata() == value){
								cout << "Grado total para vertice "<<value<< " no direccionado: " << (*ni)->edges.size() << endl;
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

						cout << "Grado total para vertice "<<value << " direccionado: " << gtotal << endl;
						cout << "Grado de salida para vertice "<<value<<" direccionado: " << gsalida << endl;
						cout << "Grado de entrada para vertice "<<value<<" direccionado: " << gentrada << endl;

						if(gsalida==0){
							cout << value << " es un nodo hundido" << endl;
						}
						if(gentrada==0){
							cout << value << " es un nodo fuente" << endl;
						}

					}

				}
//--------------------------BFS-----------------------------
				void BFS(N startN){
					queue<N> myqueue;
					vector<N> visited;

					myqueue.push(startN);
					visited.push_back(startN);

					int lvl=1;
					bool lvlh=false;

					cout << "BFS: ";
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
					cout << endl;
				}
//--------------------------BIPARTITO-----------------------------
				bool bipartite(){ //only works for strongly connected

				queue<N> myqueue;
				vector<N> colorred;
				vector<N> colorblue;

				N startN = nodes.front()->getNdata();

				myqueue.push(startN);
				colorred.push_back(startN);

				while(!myqueue.empty()){

					N current = myqueue.front();
					for(ni=nodes.begin();ni!=nodes.end();++ni){
						if(((*ni)->getNdata())==current){
							for(ei=(*ni)->edges.begin(); ei!=(*ni)->edges.end(); ++ei){
								if((find(colorred.begin(), colorred.end(), current) != colorred.end()) == true &&
								(find(colorred.begin(), colorred.end(),(*ei)->nodes[1]->getNdata()) != colorred.end()) == false &&
								(find(colorblue.begin(), colorblue.end(),(*ei)->nodes[1]->getNdata()) != colorblue.end()) == false){
									//If current is in red AND the edge is not in red AND the edge not blue
									myqueue.push((*ei)->nodes[1]->getNdata());
									colorblue.push_back((*ei)->nodes[1]->getNdata());
								}
								else if((find(colorblue.begin(), colorblue.end(), current) != colorblue.end()) == true &&
								(find(colorblue.begin(), colorblue.end(),(*ei)->nodes[1]->getNdata()) != colorblue.end()) == false &&
								(find(colorred.begin(), colorred.end(),(*ei)->nodes[1]->getNdata()) != colorred.end()) == false){
									//if current is in blue AND the edge is not in blue AND the edge not red
									myqueue.push((*ei)->nodes[1]->getNdata());
									colorred.push_back((*ei)->nodes[1]->getNdata());
								}
								else if(((find(colorred.begin(), colorred.end(), current) != colorred.end()) == true &&
								(find(colorred.begin(), colorred.end(), (*ei)->nodes[1]->getNdata()) != colorred.end()) == true) ||
								((find(colorblue.begin(), colorblue.end(), current) != colorblue.end()) == true &&
								(find(colorblue.begin(), colorblue.end(), (*ei)->nodes[1]->getNdata()) != colorblue.end()) == true)){
								//If current is in red/blue AND edge is in red/blue
								return false;
								}
							}
							myqueue.pop();
						}
					}
				}

				for (typename vector<N>::iterator i = colorred.begin(); i != colorred.end(); ++i) cout << *i << ' ';
				cout << endl;
				for (typename vector<N>::iterator i = colorblue.begin(); i != colorblue.end(); ++i) cout << *i << ' ';

				return true;
				}
//--------------------------DFS-----------------------------
				void DFS(N startN, bool &fc){
					stack<N> mystack;
					vector<N> visited;

					mystack.push(startN);
					visited.push_back(startN);

					while(!mystack.empty()){
						for(ni=nodes.begin();ni!=nodes.end();++ni){
							bool t=false;
							if(!mystack.empty() && ((*ni)->getNdata())==mystack.top()){ //si el nodo es el primero en el stack
								for(ei=(*ni)->edges.begin(); ei!=(*ni)->edges.end(); ++ei){
									if((find(visited.begin(), visited.end(),(*ei)->nodes[1]->getNdata()) != visited.end()) == false){ //if *ei not in visited
										t=true;
										mystack.push((*ei)->nodes[1]->getNdata());
										visited.push_back((*ei)->nodes[1]->getNdata());
										cout << (*ni)->getNdata() << (*ei)->nodes[1]->getNdata() << " | ";
										break;
									}
								}
								if(t!=true){mystack.pop();}
							}
						}
					}

					//si dfs ha visitado todos los nodos
					fc = visited.size() == nodes.size();
				}
//-------------------------CONEXO------------------------------
				bool conexo(){
					bool conexo = false;
					for(ni=nodes.begin(); ni!=nodes.end(); ni++){
					 	cout << (*ni) << " ";
						DFS('A', conexo);
						if(conexo==false){return false;}
					}

					return true;
				}
//--------------------FUERTEMENTE CONEXO------------------------
				// bool stronglyConnected(N startN){
				//
				// 	if(dir){
				// 		bool fc;
				//
				// 		DFS(startN, fc);
				// 		if(fc==false){return false;}
				// 		else{
				//
				// 			getTranspose().DFS(startN, fc);
				// 			if(fc==false){return false;}
				// 			else{return true;}
				//
				// 		}
				//
				// 	}
				// 	else{
				// 		throw "Only works for directed graphs";
				// 	}
				//
				// }
				//
				// self getTranspose(){
				// 	self transpose(dir, file);
				// 	for(ni=nodes.begin();ni!=nodes.end();++ni){
				// 		transpose.insertNode((*ni)->getNdata());
				// 	}
				// 	for(ni=nodes.begin();ni!=nodes.end();++ni){
				// 		for(ei=(*ni)->edges.begin(); ei!=(*ni)->edges.end(); ++ei){
				// 			transpose.insertEdge(
				// 			(*ei)->getEdata(),
				// 			distance(nodes.begin(), find(nodes.begin(), nodes.end(), (*ei)->nodes[1])),
				// 			distance(nodes.begin(), find(nodes.begin(), nodes.end(), *ni))
				// 			);
				// 		}
				// 	}
				// 	return transpose;
				// }
//---------------------------PRIM-------------------------------
				void setAllNotVisited(){
					for(auto item: nodes){
						item->setNotVisited();
					}
				}

				Graph<Traits> prim(N vertice){
          setAllNotVisited();
					Graph<Traits> GrafoPrim(0);
					if(!dir){
						int visitedNodes = 1;
						multimap<E,edge*> EdgeMap;
						node* ni = findNode(vertice);
						ni->setVisited();
						for(auto ei:ni->edges){
							EdgeMap.insert(pair<E,edge*>(ei->getEdata(),ei));
						}
						cout << "PRIM: ";
						while(visitedNodes != nodes.size()){
							edge* BeginEdge = (*EdgeMap.begin()).second;
							if(!BeginEdge->getSecondPointer()->isVisited()){
                    cout <<"{"<<BeginEdge->getFirstPointer()->getNdata() <<","<<BeginEdge->getSecondPointer()->getNdata()<<","<<BeginEdge->getEdata()<<"} ";
                    BeginEdge->getSecondPointer()->setVisited();
										ni = BeginEdge->getSecondPointer();
										GrafoPrim.insertNode(BeginEdge->getFirstPointer()->getNdata(),0,0);
                    GrafoPrim.insertNode(BeginEdge->getSecondPointer()->getNdata(),0,0);
                    GrafoPrim.insertEdge(BeginEdge->getEdata(),BeginEdge->getFirstPointer()->getNdata(),BeginEdge->getSecondPointer()->getNdata());
								for(auto ei:ni->edges){
                    EdgeMap.insert(pair<E,edge*>(ei->getEdata(),ei));
								}
                visitedNodes++;
                            }else{
                                EdgeMap.erase(EdgeMap.begin());
                            }
						}
						cout<<endl;
						return GrafoPrim;
					}
					else{
						cout << "NO SE PUEDE HACER PRIM, EL GRAFO ES DIRIGIDO"<< endl;
						return GrafoPrim;
					}
				}

				Graph<Traits> kruskal(){
					Graph<Traits> GrafoKruskal(0);
					if(!dir){
						multimap<E,edge*> EdgeMap;
						for(auto ni:nodes){
							for(auto ei:ni->edges){
								EdgeMap.insert(pair<E,edge*>(ei->getEdata(),ei));
							}
						}
						cout << "KRUSKAL: ";
						while(EdgeMap.size()>0){
							if(unionParent((*EdgeMap.begin()).second->getFirstPointer(),(*EdgeMap.begin()).second->getSecondPointer())){
								cout <<"{"<<(*EdgeMap.begin()).second->getFirstPointer()->getNdata() <<","<<(*EdgeMap.begin()).second->getSecondPointer()->getNdata()<<","<<(*EdgeMap.begin()).first<<"} ";
								GrafoKruskal.insertNode((*EdgeMap.begin()).second->getFirstPointer()->getNdata(),(*EdgeMap.begin()).second->getFirstPointer()->getXdata(),(*EdgeMap.begin()).second->getFirstPointer()->getYdata());
								GrafoKruskal.insertNode((*EdgeMap.begin()).second->getSecondPointer()->getNdata(),(*EdgeMap.begin()).second->getFirstPointer()->getXdata(),(*EdgeMap.begin()).second->getFirstPointer()->getYdata());
								GrafoKruskal.insertEdge((*EdgeMap.begin()).second->getEdata(),(*EdgeMap.begin()).second->getFirstPointer()->getNdata(),(*EdgeMap.begin()).second->getSecondPointer()->getNdata());
							}
							EdgeMap.erase(EdgeMap.begin());
						}
						cout << endl;
						return GrafoKruskal;
					}
					else{
						cout << "NO SE PUEDE HACER KRUSKAL, EL GRAFO ES DIRIGIDO"<<endl;
						return GrafoKruskal;
					}
				}



        void print(){
						if (!nodes.size()) {cout<<"No hay nodos\n"; return;}
            for(auto ni: nodes){
                cout << ni->getNdata() << "| ";
                for(auto item: ni->edges){
                    cout << item->nodes[1]->getNdata() <<":"<<item->getEdata()<<' ';
                }
                    cout << endl;
            }
        }


};

typedef Graph<Traits> graph;

#endif
