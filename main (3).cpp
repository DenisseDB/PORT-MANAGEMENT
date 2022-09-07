// =================================================================
//
// File: main.cpp
// Author: Denisse Dominguez Bolaños
// Date: 19 de noviembre del 2021
//
// =================================================================
#include <iostream>
#include "ugraph.h"

using namespace std;

/***********************************************************/
/******************* BFS PARA SABER ALCANCE*****************/
/******************** BUSQUEDA EN AMPLITUD *****************/
std::set<string> bfs(string& start, UnweightedGraph<string>& graph, int cantidad_busquedas){
	std::set<string> visited;
	std::queue<string> pending; // pendientes a visitar
	typename std::set<string>::iterator itr; // sirve para preguntar si esta visitado

	std::queue<int> saltos;
	std::queue<string> puertos;
	saltos.push(0); // saltos que llevo desde el origen
	puertos.push(start); // metemos el primer puerto

	while (!puertos.empty()) { // mientras que el stack no este vacio
		int saltos_actuales = saltos.front(); saltos.pop(); // obtener los valores de arriba
		if (saltos_actuales>cantidad_busquedas){ // al llegar al maximo, se detiene
			break;
		}
		string v = puertos.front(); puertos.pop(); // sacamos el elemento que esta al frente
		if (visited.find(v) == visited.end()) { // si no ha sido visitado, visited lo busca con find
			visited.insert(v); // lo agregamos a visitado
			std::set<string> connected =
					graph.getConnectionFrom(v); // y agregamos todas las conexiones que sale de ese vertice, se mandan a pending
					// que mientras no este vacio, se repite desde el while

			// Cada una de las conexiones las agrego a la pila
			for (itr = connected.begin();
					itr != connected.end(); itr++) {
				puertos.push( (*itr) );
				saltos.push(saltos_actuales+1); // agregar salto + 1
			}
		}
	}
	return visited; // regresamos el vertice
}

int main(int argc, char* argv[]) {
	int numero_conexiones;
	string puerto_a;
	string puerto_b;
	// ver cuantas conexiones tiene el grafo
	cin >> numero_conexiones;
	// creamos el grafo
	UListGraph<string> grafo_puertos(false);
// hacemos las conexiones
	for(int i=0; i<numero_conexiones;i++){
		cin>> puerto_a >> puerto_b;
		// añadir los datos al grafo
		grafo_puertos.addEdge(puerto_a, puerto_b);
	}
	int numero_puertos = grafo_puertos.getVertexes().size(); //obtener vertices en vector y sacar su size
	// ver cuantas veces me solicitan realizar la busqueda
	int cantidad_busquedas;
	cin >> cantidad_busquedas;
	// ver cual es el puerto de inicio
	string puerto_inicial;
	// ver cuantos arcos desplazarme
	int numero_movimientos;
	// creamos el queue de acuerdo al numero de busquedas solicitados
	int no_alacanzados;
	for(int i=0; i<cantidad_busquedas; i++){
		// recibimos el puerto de salida
		cin >> puerto_inicial >> numero_movimientos;
		// guardamos el regreso de la funcion bfs en un set
		std::set<string> puertos_alcanzados = bfs(puerto_inicial, grafo_puertos, numero_movimientos);
		// realizamos la resta del numero de puertos con el resultado del bfs obteniendo
		// los puertos no alcanzados
		no_alacanzados = numero_puertos - puertos_alcanzados.size();
		cout << "Case " << i+1 << ": " << no_alacanzados << " ports not reachable from port " << puerto_inicial << " with MNP = " << numero_movimientos << "." << endl;
	}
	return 0;
}

// p
