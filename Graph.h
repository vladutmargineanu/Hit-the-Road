/* Copyright 2018 Margineanu Nicolae-Vladut */

#ifndef GRAPH_H__
#define GRAPH_H__

#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>

template <typename T>
class Graph {
private:
	std::vector<std::vector<T> > neigh;
	int numNodes;	
	bool oriented;
	int time;

public:
	int numConnectedComp;
	std::vector<std::vector<T> > Tare_Conexe;
	std::vector<std::vector<T> > components;
	std::vector<std::vector<T> > hamCycles;
	std::vector<T> order;
	std::vector<bool> viz;
	Graph(int n, bool oriented);
	void addEdge(T i, T j);
	bool isEdge(T i, T j);
	void connectedComponents();
	void dfs(int n, std::vector<bool>& visited , std::vector<T> &order);
	int minPath(T& source, std::vector<bool>& viz);
	std::vector<std::vector<T> > get_neigh();
    std::stack<T> minPath(T source, T dest);
};

template <typename T>
Graph<T>::Graph(int n, bool oriented) {
	this->numNodes = n;
	this->oriented = oriented;
	for (int i = 0; i < numNodes; i++) {
		neigh.push_back(std::vector<T>());
	}
}

/* Adaugă o muchie la grafic (ambele moduri dacă este neorientată). */
template <typename T>
void Graph<T>::addEdge(T i, T j) {
	neigh[i].push_back(j);
	if (!oriented) {
		neigh[j].push_back(i);
	}
}

template < typename T>
std::vector< std::vector < T > > Graph<T>:: get_neigh()
{
	return neigh;
}

/* Verifică dacă două noduri sunt conectate printr-o margine. */
template <typename T>
bool Graph<T>::isEdge(T i, T j) {
	std::vector<T> v = neigh[i];
	return std::find(v.begin(), v.end(), j) != v.end();
}

template <typename T>
void Graph<T>::connectedComponents() {
/* Initializam si apelam DFS pentru toate nodurile nevizate.
   Utilizam componente.push_back pentru a crea o componenta noua. */
	std::vector<bool> visited(numNodes, false);
	this->numConnectedComp = 0;
	int i = 0;
	for(auto it = visited.begin(); it != visited.end(); it++) {
		components.push_back(std::vector<T>());
		if(*it == false) {
			dfs(i, visited, order);
			this->numConnectedComp++;
		}
		i++;
	}
	viz = visited;
}

template <typename T>
void Graph<T>::dfs(int node, std::vector<bool>& visited, std::vector<T> &order) {
/* Efectuam DFS pentru a adauga nodul la utilizarea componentelor. */
		visited[node] = true;
		components[numConnectedComp].push_back(node);
		for(int n:neigh[node]) {
			if(!visited[n])
				dfs(n, visited, order );
		}
		order.push_back(node);
}

template <typename T>
int Graph<T>::minPath(T& source, std::vector<bool> &viz) {
/* Initializam si efectuam BFS de la sursa, urmarind distanta si parintele. */

	std::vector<bool> visited;
	visited.resize(numNodes,false);
	std::queue<T> q;
	std::vector<int> dist(numNodes,0);
	q.push(source);
	dist[source] = 0;

	while(!q.empty()) {
		
		int node = q.front();
		q.pop();
		if ( node != source && viz[node] ) return dist[node];
		for(auto x:neigh[node]) {
			if(!visited[x]) {
				visited[x] = true;
				q.push(x);
				dist[x] = dist[node] + 1;
			} 
		}
	}
	return -1;
}

template <typename T>
std::stack<T> Graph<T>::minPath(T source, T dest) {
	std::vector<bool> visited(numNodes,false);
	std::queue<int> q;
	std::vector<int> dist(numNodes,0);
	std::vector<T> parent(numNodes,-1);
	
/* Initializam si efectuam BFS de la sursa, urmarind distanta si parintele. */
	for ( int i = 0 ; i < numNodes ; i++ )
		sort(neigh[i].begin() , neigh[i].end() );
	    q.push(source);
	    dist[source] = 0;

	while(!q.empty()) {
		parent[source] = -1;
		int node = q.front();
		q.pop();
		for(auto x:neigh[node]){
			if(!visited[x]) {
				visited[x] = true;
				q.push(x);
				dist[x] = dist[node] + 1;
				parent[x] = node;
			} 
		}
	}
	
	std::stack<int> path;
	// Aici nu este nici un drum de la sursa la destinatie
	if (parent[dest] == -1) return path;
/* Începem de la destinație, nodul devine părinte și este
bagat in stiva in timp ce sursa nu este atinsa. */
	int crt = dest;
	while(crt != -1) {
		path.push(crt);
		crt = parent[crt];
	}
	return path;
}
#endif  // GRAPH_H__
