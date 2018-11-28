
#include <iostream>
#include <thread>
#include <iomanip>
#include "graph.h"

using namespace std;

#define NUM_THREADS 4

void printA_estrella(graph migrafo,char inicio,char final){
	graph datosEstrella = migrafo.A_estrella(inicio,final);
	datosEstrella.print();
	cout <<endl;
}

int main(int argc, char *argv[]) {
	thread threads[NUM_THREADS];
	graph migrafo(1,"graph_construct4.txt");/*
	threads[0] = thread(printA_estrella,migrafo,'A','F');
	threads[1] = thread(printA_estrella,migrafo,'D','F');
	threads[2] = thread(printA_estrella,migrafo,'C','F');
	threads[3] = thread(printA_estrella,migrafo,'A','H');
	for(int i = 0; i < NUM_THREADS;i++){threads[i].join();}
	migrafo.greedyBFS('A','H');
	map<char,int> mymap = migrafo.Bellman_Ford('A');
	cout << "Bellman Ford: ";
	for(auto x:mymap){
		cout << x.first <<":"<<x.second<<" ";
	}
	cout <<endl<< "Dijkstra: ";
	map<char,int> datosDijkstra = migrafo.dijkstra('A');
	for(auto x: datosDijkstra){cout <<x.first<<":"<<x.second<<" ";}
	auto mymatrices = migrafo.Floyd_warshall();
  for (int i = 0; i < 9; i++){
      for (int j = 0; j < 9; j++){
          if (mymatrices.first[i][j] == 99)
              cout << setw(5) << "INF";
          else
              cout << setw(5) << mymatrices.first[i][j];
      }
      cout <<  endl;
  }
  cout << endl;
  for (int i = 0; i < 9; i++){
      for (int j = 0; j < 9; j++){
            cout << setw(5) << mymatrices.second[i][j];
      }
      cout <<  endl;
  }
	migrafo.print();
	map<char,int> datosDijkstra = migrafo.dijkstra('A');
	for(auto x: datosDijkstra){cout <<x.first<<":"<<x.second<<" ";}
	cout << endl;

	*/
	return 0;
}
