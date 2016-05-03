#include"BFSGraph.h"
#include"Vertex.h"
#include<fstream>
#include<string>
#include<iostream>
using namespace std;

BFSGraph::BFSGraph(int n_input) { // constructor
	n = n_input; // the number of vertices, the ids of the vertices are from 0 to n-1
	color = new colorType[n]; // record the colors of the vertices during BFS
	pre = new int[n]; // record the predecessors during BFS
	dis = new int[n]; // record the shortest path distances during BFS
	adj = new Vertex*[n]; // adj[i] points the head of the adjacency list of vertex i, for i from 0 to n-1
	for (int i = 0; i < n; i++) {
		adj[i] = nullptr;
	}
	color = new colorType[n];
	pre = new int[n];
	dis = new int[n];
	front = 0;
	rear = 0;
	Q = new int[n];
	orderArr = new int[n];
	order = 1;
}
void BFSGraph::buildMatrix(int* adjM) {
	fstream fin;
	fin.open("Assign8BFSInput.txt");
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

void BFSGraph::addToList(int num, Vertex* & list) {
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
void BFSGraph::SetAdjLists(int* adjM){// build the adjacency lists from the adjacency matrix adjM
	for (int i = 0; i < n; i++) {//read through each row.
		for (int j = 0; j < n; j++) {//each column
			//if 1, then [i] is adjacent to [j].
			int tmp = adjM[(i*n)+j];
			if (tmp == 1) {
				//add j to i's list.
				cout << i << " is adj. to " << j << endl;
				addToList(j, adj[i]);
			}
		}
	}
	}
void BFSGraph::PrintAdjLists() {// print the adjacency lists of the graph
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

// the following two functions are for the BFS traversal as we discussed in class
void BFSGraph::BFS(int id) {// BFS traversal, id is the source vertex, with default 0
	Vertex* current;
	// Mark all the vertices as not visited
	for (int i = 0; i < n; i++) {
		color[i] = WHITE;
	}

	//mark first vertex as visited, add it to queue.
	color[id] = GRAY;
	Q[rear] = id;
	rear++;
	orderArr[id] = order;
	order++;
	cout << "BFS: " << id << " ";

	while (front < rear){
		// Dequeue a vertex from queue and print it
		id = Q[front];
		front++;

		// Get all adjacent vertices of the dequeued vertex id
		// If a adjacent has not been visited, then mark it visited
		// and enqueue it
		current = adj[id];
		while(current != nullptr){
			if (color[current->id] == WHITE)
			{
				cout << current->id << " ";
				color[current->id] = GRAY;
				Q[rear] = current->id;
				rear++;
				pre[current->id] = id;
			}
			orderArr[current->id] = order;
			order++;
			current = current->next;
		}
		color[id] = BLACK;
	}
	cout << endl;
}
void BFSGraph::BFSVisit(int id){// actually does BFS, search a connected component from id
	}
void BFSGraph::PrintSP(int source, int v){// Print the shortest path from the source to v and the shortest path distance from source to v
	int length = 0;
	int original = v;
	string output = "";
	while (v != source) {
		length++;
		output += to_string(v) + " ";
		v = pre[v];
	}
	output += to_string(source);
	cout << "Shortest path from " << source << " to " << original << ": " << output << endl;
	cout << "Length: " << length << endl;
	}