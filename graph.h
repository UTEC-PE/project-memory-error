#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <algorithm>
#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <limits.h>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>

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
				map<N,int> heuristica;

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

				void calculoHeuristica(node* ni,node* final){
					heuristica.clear();
					for(auto ni:nodes){
						int calculo = sqrt(pow(ni->getXdata()-final->getXdata(),2)+pow(ni->getYdata()-final->getYdata(),2));
						heuristica.insert(pair<N,int>(ni->getNdata(),calculo));
					}
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
            int cont = 0;
            for(auto ni: nodes) {
                cont ++;
                if(ni->getNdata()== value) {
                    while (ni->edges.size() > 0) {
                        ei = ni->edges.begin();
                        removeEdge((*ei)->getFirstPointer()->getNdata(), (*ei)->getSecondPointer()->getNdata());
                    }
                    nodes.erase(nodes.begin()+(cont-1));
                    break;
                }
            }
        }

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

				E getEdgeWeight(N node1,N node2){
					for(ni = nodes.begin(); ni != nodes.end(); ni++){
						if((*ni)->getNdata() == node1){
							for(ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
								if((*ei)->nodes[1]->getNdata()==node2){
									return (*ei)->getEdata();
									break;
								}
							}
						}
				}
				return 0;
			}

				node* findParent(node* ni){
					node* current = ni;
					while(current -> parent != current){
						current = current -> parent;
					}
					ni->parent= current;
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

				void getGrado(N value){

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

				bool conexo(){
					bool conexo = false;
					for(auto ni: nodes){
						DFS(ni->getNdata(), conexo);
						if(conexo==false){return false;}
					}
					return true;
				}

				vector<pair<N,N>> BFS(N startN){
						queue<N> myqueue;
						vector<N> visited;
						vector<pair<N,N>> bfs;

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
											bfs.push_back(make_pair((*ni)->getNdata(), (*ei)->nodes[1]->getNdata()));
											//cout << (*ni)->getNdata() << (*ei)->nodes[1]->getNdata() << " | ";
											lvlh=true;
										}
									}
									lvl+=lvlh;
									lvlh=false;
									myqueue.pop();
								}
							}
						}
						for (auto i = 0; i<bfs.size(); ++i){
							 cout << bfs[i].first << " "
										<< bfs[i].second << endl;
					 	}
						return bfs;
					}

				vector<pair<N,N>> DFS(N startN, bool &fc){
					stack<N> mystack;
					vector<N> visited;
					vector<pair<N,N>> dfs;

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
										dfs.push_back(make_pair((*ni)->getNdata(), (*ei)->nodes[1]->getNdata()));
										//cout << (*ni)->getNdata() << (*ei)->nodes[1]->getNdata() << " | ";
										break;
									}
								}
								if(t!=true){mystack.pop();}
							}
						}
					}

					//si dfs ha visitado todos los nodos
					fc = visited.size() == nodes.size();

					for (auto i = 0; i<dfs.size(); ++i){
						 cout << dfs[i].first << " "
									<< dfs[i].second << endl;
				 	}

					return dfs;
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
						cout << "Only works for directed graphs"<<endl;
					}

				}

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
                cout << endl;
				for (typename vector<N>::iterator i = colorred.begin(); i != colorred.end(); ++i) cout << *i << ' ';
				cout << endl;
				for (typename vector<N>::iterator i = colorblue.begin(); i != colorblue.end(); ++i) cout << *i << ' ';
				cout << endl;

				return true;
    }

		self getTranspose(){
				 	self transpose(dir);
				 	for(ni=nodes.begin();ni!=nodes.end();++ni){
				 		transpose.insertNode((*ni)->getNdata(),(*ni)->getXdata(),(*ni)->getYdata());
				 	}
				 	for(ni=nodes.begin();ni!=nodes.end();++ni){
				 		for(ei=(*ni)->edges.begin(); ei!=(*ni)->edges.end(); ++ei){
				 			transpose.insertEdge((*ei)->getEdata(), (*ei)->getSecondPointer()->getNdata(),(*ei)->getFirstPointer()->getNdata());
				 		}
				 	}
				 	return transpose;
				}

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
										GrafoPrim.insertNode(BeginEdge->getFirstPointer()->getNdata(),BeginEdge->getFirstPointer()->getXdata(),BeginEdge->getFirstPointer()->getYdata());
                    GrafoPrim.insertNode(BeginEdge->getSecondPointer()->getNdata(),BeginEdge->getSecondPointer()->getXdata(),BeginEdge->getSecondPointer()->getYdata());
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

				map<N,E> dijkstra(N vertice){
					map<N,E> dijkstraTable;
					set<N> visitados;
					node* root = findNode(vertice);
					N nodomenor;
					for(auto ni:nodes){
						if(ni!=root){dijkstraTable.insert(pair<N,int>(ni->getNdata(),INT_MAX));}
						else{dijkstraTable.insert(pair<N,int>(ni->getNdata(),0));}
					}
					int menor = INT_MAX;
					while(visitados.size()!=nodes.size()){
						visitados.insert(root->getNdata());
						for(auto ei:root->edges){
						    int rootvalueInTable = dijkstraTable[root->getNdata()];
						    int movevalueInTable = dijkstraTable[ei->getSecondPointer()->getNdata()];
							if(ei->getEdata()+rootvalueInTable < movevalueInTable){
								dijkstraTable[ei->getSecondPointer()->getNdata()] = ei->getEdata()+rootvalueInTable;
							}
						}
						for(auto nodos:dijkstraTable){
                if(nodos.second < menor && find(visitados.begin(),visitados.end(),nodos.first)==visitados.end()){
                    menor = nodos.second;
                    nodomenor = nodos.first;
                }
						}
						menor = INT_MAX;
						root = findNode(nodomenor);
					}
					return dijkstraTable;
				}

				Graph<Traits> A_estrella(N origen,N llegada){
					//heuristica = 10*(abs(Xactual-Xdestino) + abs(Yactual-Ydestino)
					Graph<Traits> GrafoAStar(1);
					vector<N> visitados;
					map<N,E> AStarTable;
					node* temp = findNode(origen);
					node* final = findNode(llegada);
					calculoHeuristica(temp,final);
					int menor;
					N nodomenor;
					for(auto ni:nodes){
						if(ni!=temp){AStarTable.insert(pair<N,int>(ni->getNdata(),INT_MAX));}
						else{AStarTable.insert(pair<N,int>(ni->getNdata(),0));}
					}
					while(temp != final){
						visitados.push_back(temp->getNdata());
						menor = INT_MAX;
						for(auto ei:temp->edges){
								int rootvalueInTable = AStarTable[temp->getNdata()];
								int movevalueInTable = AStarTable[ei->getSecondPointer()->getNdata()];
							if(ei->getEdata()+rootvalueInTable+heuristica[ei->getSecondPointer()->getNdata()] < movevalueInTable){
								AStarTable[ei->getSecondPointer()->getNdata()] = ei->getEdata()+rootvalueInTable+heuristica[ei->getSecondPointer()->getNdata()];
							}
							if(ei->getEdata()+rootvalueInTable+heuristica[ei->getSecondPointer()->getNdata()] < menor && find(visitados.begin(),visitados.end(),ei->getSecondPointer()->getNdata())==visitados.end()){
								menor = ei->getEdata()+rootvalueInTable+heuristica[ei->getSecondPointer()->getNdata()];
								nodomenor = ei->getSecondPointer()->getNdata();
							}
						}
						node* nuevonodomenor = findNode(nodomenor);
						GrafoAStar.insertNode(temp->getNdata(),temp->getXdata(),temp->getYdata());
						GrafoAStar.insertNode(nuevonodomenor->getNdata(),nuevonodomenor->getXdata(),nuevonodomenor->getYdata());
						GrafoAStar.insertEdge(getEdgeWeight(temp->getNdata(),nuevonodomenor->getNdata()),temp->getNdata(),nuevonodomenor->getNdata());
						temp = nuevonodomenor;
					}
					visitados.push_back(temp->getNdata());
					return GrafoAStar;
				}

vector<pair<N,N>> greedyBFS(N origen, N llegada){
			node* nOrigen = findNode(origen);
			node* nLlegada = findNode(llegada);
			calculoHeuristica(nOrigen, nLlegada);

			vector<pair<N,N>> greedyBFS_path;

			map<int, N> should_visit;
			set<N> steped_on;
			set<N> visited;
			steped_on.insert(origen);

			N current = origen;
			bool origenNotLlegada=false;

			while(current != llegada ){
				origenNotLlegada=true;
				for(ni=nodes.begin(); ni!=nodes.end(); ++ni){
					if((*ni)->getNdata()==current){
						cout << "current: " << current << endl;
						for(ei=(*ni)->edges.begin(); ei!=(*ni)->edges.end(); ++ei){
							if(visited.find((*ei)->nodes[1]->getNdata()) == visited.end() && steped_on.find((*ei)->nodes[1]->getNdata()) == steped_on.end()){ //if the edge is not in the map and has not been steped_on
								should_visit.insert( pair<int,N>(heuristica.find((*ei)->nodes[1]->getNdata())->second , (*ei)->nodes[1]->getNdata()) );
								visited.insert((*ei)->nodes[1]->getNdata());
							}
						}
						cout << "map before: " << endl;
						for (auto it=should_visit.begin(); it!=should_visit.end(); ++it)
						std::cout << it->first << " => " << it->second << '\n';

						greedyBFS_path.push_back(make_pair(current, should_visit.begin()->second));
						current = should_visit.begin()->second;
						if(current==llegada){break;}
						steped_on.insert(current);
						should_visit.erase(should_visit.begin());

						cout << "map after: " << endl;
						for (auto it=should_visit.begin(); it!=should_visit.end(); ++it)
						std::cout << it->first << " => " << it->second << '\n';
					}
				}
			}

			cout << "Heuristica: " << endl;
			for (auto it=heuristica.begin(); it!=heuristica.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

			cout << "Path: " << endl;
			for (auto i = 0; i<greedyBFS_path.size(); ++i){
				 cout << greedyBFS_path[i].first << " "
							<< greedyBFS_path[i].second << endl;
			}
			cout << endl;

			cout << "should_visit: " << endl;
			while (!should_visit.empty())
			{
				std::cout << should_visit.begin()->first << " => " << should_visit.begin()->second << '\n';
				should_visit.erase(should_visit.begin());
			}
			cout << endl;

			cout << "steped_on: " << endl;
			for (auto it=steped_on.begin(); it!=steped_on.end(); ++it)
				std::cout << ' ' << *it;
			cout << endl;

			cout << "current: " << current << endl;


			if(!origenNotLlegada){ // si el origen es igual a la llegada, el camino minimo seria el mismo
				greedyBFS_path.push_back(make_pair(origen, origen));
			}

			return greedyBFS_path;
		}


				map<N, int> Bellman_Ford(N startN){
							map<N, int> dist;
							queue<N> should_visit;
							int inf=99;

							should_visit.push(startN);
							for(ni=nodes.begin(); ni!=nodes.end(); ni++){
								dist.insert(make_pair((*ni)->getNdata(), inf));
							}
							dist.find(startN)->second = 0;

							for(int i=1; i<nodes.size(); i++){

								bool path_changed=false;

								for(ni=nodes.begin(); ni!=nodes.end(); ni++){
									if((*ni)->getNdata()!=startN){should_visit.push((*ni)->getNdata());};
								}

								while(!should_visit.empty()){
									for(ni=nodes.begin(); ni!=nodes.end(); ++ni){ //works only if starN is the first Node and the map is in the same order as the nodes v
										if((*ni)->getNdata() == should_visit.front()){
											for(ei=(*ni)->edges.begin(); ei!=(*ni)->edges.end(); ++ei){
												if(dist.find((*ni)->getNdata())->second != inf && (*ei)->nodes[1]->getNdata()!=startN){ //salta startN
													if(dist.find((*ni)->getNdata())->second + (*ei)->getEdata() < dist.find((*ei)->nodes[1]->getNdata())->second && dist.find((*ei)->nodes[1]->getNdata())->second > 0){
														dist.find((*ei)->nodes[1]->getNdata())->second = dist.find((*ni)->getNdata())->second + (*ei)->getEdata();
														path_changed=true;
													}
												}
											}
											should_visit.pop();
										}
									}
								}

								if(path_changed==false){break;}
							}

							return dist;
						}


pair<vector<vector<int>>,vector<vector<N>>> Floyd_warshall(){
		int inf=99;
		int size=nodes.size();
		vector<vector<int>> dist;
		vector<vector<N>> steps;
		map<N, int> node_pos;
		map<int, N> pos_node;
		pair<vector<vector<int>>,vector<vector<N>>> Floyd_Warshall;
		int count=0;

		for(ni=nodes.begin(); ni!=nodes.end(); ni++){ //crea mapa
			node_pos.insert(pair<N, int>((*ni)->getNdata(), count));
			pos_node.insert(pair<int, N>(count, (*ni)->getNdata()));
			count+=1;
		}

		vector<N> node_vec; //inicializa steps
		for(auto node: nodes){
			node_vec.push_back(node->getNdata());
		}
		for(int i=0; i<size; i++){
			steps.push_back(node_vec);
		}

		vector<int> inf_vec; //inicializa dist
		for(int i=0; i<size; i++)
		{
			inf_vec.push_back(inf);
		}
		for(int i=0; i<size; i++)
		{
			dist.push_back(inf_vec);
		}
		for(int i=0; i<size; i++){
			dist[i][i]=0;
		}

		for(ni=nodes.begin(); ni!=nodes.end(); ni++){ //pesos
			for(ei=(*ni)->edges.begin(); ei!=(*ni)->edges.end(); ++ei){
				dist[node_pos.find((*ni)->getNdata())->second][node_pos.find((*ei)->nodes[1]->getNdata())->second]=(*ei)->getEdata();
			}
		}

		for(int k=0; k<size; k++){
			for(int i=0; i<size; i++){
				for(int j=0; j<size; j++){
					if(dist[i][j] > dist[i][k]+ dist[k][j]){
						dist[i][j] = dist[i][k]+dist[k][j];
						steps[i][j] = pos_node.find(k)->second;
					}
				}
			}
		}
<<<<<<< HEAD

		void Floyd_Warshall(){
			int inf=99;
			int size=nodes.size();
			int dist[size][size];
			N steps[size][size];
			map<N, int> node_pos;
			map<int, N> pos_node;
			int count=0;

			for(ni=nodes.begin(); ni!=nodes.end(); ni++){ //crea mapa
				node_pos.insert(pair<N, int>((*ni)->getNdata(), count));
				pos_node.insert(pair<int, N>(count, (*ni)->getNdata()));
				count+=1;
			}

			count=0; //inicializa steps
			for(auto node: nodes){
				for(int i=0; i<size; i++){
					steps[i][count]=node->getNdata();
				}
				count+=1;
			}

			for(int i=0; i<size; i++){ //inicializa con infinito
				for(int j=0; j<size; j++){
					dist[i][j]=inf;
				}
			}

			for(int i=0; i<size; i++){ //diagonal con 0
				dist[i][i]=0;
			}

			for(ni=nodes.begin(); ni!=nodes.end(); ni++){ //pesos
				for(ei=(*ni)->edges.begin(); ei!=(*ni)->edges.end(); ++ei){
					dist[node_pos.find((*ni)->getNdata())->second][node_pos.find((*ei)->nodes[1]->getNdata())->second]=(*ei)->getEdata();
				}
			}

			for(int k=0; k<size; k++){
				for(int i=0; i<size; i++){
					for(int j=0; j<size; j++){
						if(dist[i][j] > dist[i][k]+ dist[k][j]){
							dist[i][j] = dist[i][k]+dist[k][j];
							steps[i][j] = pos_node.find(k)->second;
						}
					}
				}
			}

			cout << "distancia:";
			cout << endl;
			for(int i=0; i<size; i++){
				for(int j=0; j<size; j++){
					cout << dist[i][j] << " ";
				}
				cout << endl;
			}

			cout << endl;

			cout << "steps:";
			cout << endl;
			for(int i=0; i<size; i++){
				for(int j=0; j<size; j++){
					cout << steps[i][j] << " ";
				}
				cout << endl;
			}
		}

    void print(){
        for(auto ni: nodes){
            cout << ni->getNdata() << "| ";
            for(auto item: ni->edges){
                cout << item->getSecondPointer()->getNdata() <<":"<<item->getEdata()<<' ';
=======
		return Floyd_Warshall = make_pair(dist, steps);
	}

        void print(){
            for(auto ni: nodes){
                cout << ni->getNdata() << "| ";
                for(auto item: ni->edges){
                    cout << item->getSecondPointer()->getNdata() <<":"<<item->getEdata()<<' ';
                }
                    cout << endl;
>>>>>>> chip
            }
        }


};

typedef Graph<Traits> graph;

#endif
