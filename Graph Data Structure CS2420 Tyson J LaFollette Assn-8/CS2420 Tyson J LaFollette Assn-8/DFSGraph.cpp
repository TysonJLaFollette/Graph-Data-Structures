#include"DFSGraph.h"
#include"Vertex.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

DFSGraph::DFSGraph(int n_input) {// constructor 
	n = n_input; // the number of vertices, the ids of the vertices are from 0 to n-1
	color = new colorType[n]; // record the colors of the vertices during BFS
	pre = new int[n]; // record the predecessors during BFS
	adj = new Vertex*[n]; // adj[i] points the head of the adjacency list of vertex i, for i from 0 to n-1
	for (int i = 0; i < n; i++) {
		adj[i] = nullptr;
	}
	color = new colorType[n];
	pre = new int[n];
	count = 1;
	order = new int[n];
	for (int i = 0; i < n; i++) {
		order[i] = -1;
	}
}
void DFSGraph::buildMatrix(int* adjM) {
	fstream fin;
	fin.open("Assign8DFSInput.txt");
	int numberOfNodes;
	string tmp;
	getline(fin, tmp);
	numberOfNodes = stoi(tmp);
	cout << "Matrix built: ";
	for (int i = 0; i < numberOfNodes*numberOfNodes; i++) {
		fin >> adjM[i];
		cout << adjM[i] << " ";
	}
	cout << endl;
	fin.close();
}
void DFSGraph::addToList(int num, Vertex* & list) {
	Vertex* prev = nullptr;
	Vertex* current;
	current = list;
	if (current == nullptr) {//list is empty.
		list = new Vertex(num, nullptr);
	}
	else {//List has at least one item.
		while (current != nullptr) {
			if (num < current->id) {
				//insert below current
				prev->next = new Vertex(num, current);
				break;
			}
			prev = current;
			current = current->next;
		}
		//if num is bigger than any content, append to end of list.
		if (current == nullptr) {
			current = new Vertex(num, nullptr);
			prev->next = current;
		}
	}
}
void DFSGraph::setAdjLists(int * adjM) {// build the adjacency lists from the adjacency matrix adjM 
	for (int i = 0; i < n; i++) {//read through each row.
		for (int j = 0; j < n; j++) {//each column
									 //if 1, then [i] is adjacent to [j].
			int tmp = adjM[(i*n) + j];
			if (tmp == 1) {
				//add j to i's list.
				cout << i << " is adj. to " << j << endl;
				addToList(j, adj[i]);
			}
		}
	}
}
void DFSGraph::printAdjLists() {// print the adjacency lists of the graph 
	Vertex* current;
	for (int i = 0; i < n; i++) {
		current = adj[i];
		cout << i << ": ";
		while (current != nullptr) {
			cout << current->id << " ";
			current = current->next;
		}
		cout << endl;
	}
}

// the following two functions are for the DFS traversal as we discussed in class 
void DFSGraph::DFS(int id){// DFS traversal, id is the source vertex, with default 0 
	//initialize all vertices to be undiscovered.
	for (int i = 0; i < n; i++) {
		color[i] = WHITE;
	}
	DFSVisit(id);    
}
void DFSGraph::DFSVisit(int id){// actually does DFS, search a connected component from id 
	Vertex* current;
	//label id as discovered
	color[id] = GRAY;
	order[id] = count;
	count++;
	//read through adjacency list, recursively calling DFS on each adjacent item.
	current = adj[id];
	while (current != nullptr) {
		//if vertex w is not labeled as discovered then
		if (color[current->id] == WHITE)//for some reason gray is counting as white in this comparison.
		{
			//recursively call DFS()
			DFSVisit(current->id);
		}
		current = current->next;
	}
	color[id] = BLACK;
}
void DFSGraph::printColors() {
	for (int i = 0; i < n; i++) {
		if (color[i] == WHITE) {
			cout << i << ":W ";
		}
		else if (color[i] == GRAY) {
			cout << i << ":G ";
		}
		else if (color[i] == BLACK){
			cout << i << ":B ";
		}
	}
}
void DFSGraph::PrintReachableNodes(int source){// Print all nodes that can be reached by source 
	cout << "Nodes reachable from " << source << ": ";
	for (int i = 0; i < n; i++) {
		if (color[i] != WHITE) {
			cout << i << " ";
		}
	}
	cout << endl;
	cout << "Order of visits: ";
	for (int i = 0; i < n; i++) {
		if (order[i] > -1) {
			cout << i << ":" << order[i] << " ";
		}
	}
	cout << endl;
}

