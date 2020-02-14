/* Copyright 2018 Margineanu Nicolae-Vladut */

#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <stack>

#include "Graph.h"
#include "hashtable.h"
#include "hash_functions.h"


std::ofstream g("task1.out");
std::ofstream g2("task2.out");
std::ofstream g4("task4.out");
std::ofstream g5("task5.out");


int main() {
	int nNodes, nEdges;
	// Citim numarul de noduri si muchii
	std::cin >> nNodes >> nEdges;
	int grad_interior[nNodes];
	// Cream un graf orientat
	Graph<int> g1(nNodes, true);
    // Cream  cate un hashtable pentru codificare / decodificare
	Hashtable<std::string, int> Hash(10, &charHashingFunction);
	Hashtable<int, std::string> Hash1(10, &hashingFunction);
	std::string TOWNS[nNodes];
	int index[nNodes];
	// Citim nodurile grafului si le codificam corespunzator
	for ( int i = 0 ; i < nNodes ; i++ ) {
		std::string x;
		std::cin >> x;
		 TOWNS[i] = x;
		Hash.put(x,i);
		index[i] = Hash.get(x);
		grad_interior[index[i]] = 0;
	}
    // Citim muchiile grafului, le adaugam
    // si actualizam gradul interior al fiecarui nod
	for (int i = 0; i < nEdges; i++) {
		std::string u, v;
		std::cin >> u >> v;
		int x = Hash.get(u);
		int y = Hash.get(v);
		grad_interior[y]++;
		g1.addEdge(x, y);
	}
	std::string ans;
	// Determinam nodul cu grad interior maxim pentru task 1
	int max = grad_interior[index[0]];
	for ( int i = 1; i < nNodes; i++ ) {
		int nr = grad_interior[index[i]];
		if ( max < nr ){
			max = nr;
			ans = TOWNS[i];
		}
	}

	g << ans << " " << max;

    // Determinam numarul de componente conexe necesar task-ului 2
	g1.connectedComponents();
	
	if ( g1.numConnectedComp == 1 )
	{
		g2 << "HARTA VALIDA";
		std::ofstream g3("task3.out");
		g3 << "Exista drum intre oricare doua orase";
	} else
		g2 << "HARTA INVALIDA";

    // Citim restul datelor de intrare
	int nr_benzinarii;
	std::cin >> nr_benzinarii;
	std::vector < bool > exista_bezinarie;
	std::string Oras_benzinarie[nr_benzinarii];
	exista_bezinarie.resize(nNodes, false);
	for ( int i = 0; i < nNodes ; i++ )
		exista_bezinarie[i] = 0;

	for ( int i = 0 ; i < nr_benzinarii ; i++ ) {
		std::cin >> Oras_benzinarie[i];
		exista_bezinarie[Hash.get(Oras_benzinarie[i])] = true;
		// Marcam benzinariile
	}

	int nr_orase;
	std::cin >> nr_orase;
	std::string Oras_task3[nr_orase];
	for ( int i = 0; i < nr_orase ; i++ )
		std::cin >> Oras_task3[i];

	int x,y,z;
	std::cin >> x;
	std::string a;
	for ( int i = 0;  i < x; i++ ) {
		std::cin >> a >> y >> z; 
		int indd = Hash.get(a);
		// Calculam distanta de la fiecare oras la cea mai
		// apropiata benzinarie cu ajutorul BFS-ului
		int ddd = g1.minPath(indd, exista_bezinarie);
		// Afisam datele de iesire pentru task 4
		if (y < z * ddd)
		{
			g4 << "NU" << "\n" ;
		} else
		{
		   g4 << "DA " << y - z*ddd << "\n" ;
		}
	}

	// Determinam ruta cu numarul maxim de calatori
	std::vector< std::pair < std::pair < std::string, std::string> , int > > SS;
	std::vector<int> nr_calatori;
	nr_calatori.resize(nNodes,0);
	std::string b;
	// Citirea datelor de intrare pentru task 5
	std::cin >> x;
	for ( int i = 0; i < x; i++ ){
		std::cin >> a >> b >> z;
		int x = Hash.get(a);
		int y = Hash.get(b);
		nr_calatori[x] += z;
		nr_calatori[y] += z;
		SS.push_back(make_pair(make_pair(a,b),z));
	}
    // Determinam nodul de start si nodul de final
    // al rutei cu numarul maxim de calatori
	int nr_max = -1111111, st= 0, dr = 0;
	for ( int i = 0; i < x; i++ )
	{
		std::string a = SS[i].first.first;
		std::string b = SS[i].first.second;
		int x = Hash.get(a);
		int y = Hash.get(b);
		int nr_c = std::min( nr_calatori[x], nr_calatori[y] );
		if ( nr_max < nr_c )
		{
			nr_max = nr_c ;
			st = x;
			dr = y;
		} else
		{
			if ( nr_max == nr_c && a > TOWNS[st] )
			{
				nr_max = nr_c;
				st = x;
				dr = y;
			}
		}
	}
	g5 << nr_max << " " ;
	// Reconstituim ruta ceruta la task-ul 5
	// cu ajutorul unui BFS
	std::stack<int> stiva = g1.minPath(st,dr);

	while(!stiva.empty())
		{  
			int x = stiva.top();
			// Afisam orasele care apartin rutei dorite
			g5  << TOWNS[x] << " " ; 
			stiva.pop();
		} 

	return 0;
}
