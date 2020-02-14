# Data-Strucutures
Homework for the Data Structures course @ ACS, UPB 2018

# Hit-the-Road

 Data inceperii temei: 18-03-2018
 Data finalizarii temei: 04-05-2018

 Problemele intampinate:
 - memory-leak-uri
 - erori de coding-style
 - timp lung de procesare a testelor foarte lungi
   
# Algorithm

 In rezolvarea task-urilor, am aplicat urmatoarele metode, folosind Graph.h
 si hashtable.h.
 Graph.h este un header in care este implementat graful generic. Acesta 
contine urmatoarele functii importante ale clasei Graph:
- tipul grafului (orientat sau neorientat): Graph(int n, bool oriented);
- adaugarea unei muchii: void addEdge(T i, T j);
- verificarea daca este muchie: bool isEdge(T i, T j);
- verificarea componentelor conexe: void connectedComponents();
- parcurgerea DFS: void dfs(int n, std::vector<bool>& visited , 
std::vector<T> &order);
- retinerea celei mai scurte rute: std::stack<T> minPath(T source, T dest);
- parcurgerea BFS pentru obtinerea celui mai scurt drum: 
int minPath(T& source, std::vector<bool>& viz);
- obtinerea vecinilor unui nod: std::vector<std::vector<T> > get_neigh().

 Header-ul hashtable.h ne ajuta in implementarea si utilizarea structurii
 de date hashtable(generica) pentru maparea numelor de orase cu un index, 
si invers. Acesta are urmatoarele functii:
- void put(Tkey key, Tvalue value)=> adaugare 
- void remove(Tkey key)=> stergere
- Tvalue get(Tkey key)=> obtinere
- bool has_key(Tkey key)=> validitatea
- void resize()=> redimensionare
- int get_size()=> dimensiunea
- int get_capacity() => capacitatea
- float current_factor()=> elementul curent

   1) Cel mai aglomerat oras
 Am citit numarul de noduri si muchii, dupa care am creat cate un hash pentru
 codificare si decodificare. Am citit nodurile grafului si le-am codificat 
corespunzator. Am adaugat muchiile si am actualizat gradul interior al fiecarui nod. 
Dupa care am determinat nodul cu grad interior maxim pentru task 1.

   2) validitatea hartii rutiere
 Am apelat functia clasei Graph connectedComponents() pentru a determina numarul de
 componente conexe necesar task-ului 2. Daca este o singura componenta conexa, 
inseamna ca harta este valida si exista drum intre oricare doua orase. In caz contrar,
 harta este nevalida.

   3) pentru un anumit oras, care sunt orasele inaccesibile lui
 In acest caz, am aflat doar in cazul in care exista drum intre oricare doua orase cu
 ajutorul functiei connectedComponents(), afland care harta este valida.

   4) pentru o masina despre care se cunosc cantitatea initiala de combustibil,
 consumul acesteia si orasul in care se afla, trebuie sa determinati cea mai 
apropiata benzinarie in care poate alimenta (daca aceasta exista)
 Pentru acest task, am marcat benzinariile (nodurile in care se afla in graful nostru),
am calculat distanta de la fiecare oras la cea mai apropiata benzinarie cu ajutorul
 BFS-ului al functiei membre clasei Graph: minPath(). Am afisat datele de iesire,
calculand benzina ramasa.

   5) fiind date traseele unor autobuze intre diferite orase, sa se determine traseul
 frecventat de cei mai multi calatori:
 Dupa citirea datelor de intrare pentru task 5, am determinat ruta cu numarul maxim de 
calatori astfel: am determinat nodul de start si nodul de final al rutei cu numarul
 maxim de calatori (cele 2 maxime dintre nodurile cu cei mai multi calatori). Am 
reconstitui ruta ceruta cu ajutorul unui BFS din functa minPath() cu doi parametri.
 Am afisat orasele care apartin rutei dorite retinute intr-un vector de stringuri. 
