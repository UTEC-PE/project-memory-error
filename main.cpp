
#include <iostream>
#include <thread>
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
	graph migrafo(0,"graph_construct3.txt");
	migrafo.print();
	map<char,int> datosDijkstra = migrafo.dijkstra('A');
	for(auto x: datosDijkstra){cout <<x.first<<":"<<x.second<<" ";}
	cout << endl;
	threads[0] = thread(printA_estrella,migrafo,'A','J');
	threads[1] = thread(printA_estrella,migrafo,'J','A');
	threads[2] = thread(printA_estrella,migrafo,'H','E');
	threads[3] = thread(printA_estrella,migrafo,'I','A');
	for(int i = 0; i < NUM_THREADS;i++){threads[i].join();}
	return 0;
}
