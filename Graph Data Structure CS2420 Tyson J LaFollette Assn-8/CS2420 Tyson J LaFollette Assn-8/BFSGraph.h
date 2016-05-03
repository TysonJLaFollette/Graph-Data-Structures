#pragma once
#include"Vertex.h"
#include"colorType.h"

class BFSGraph
{
private:
	colorType * color; // record the colors of the vertices during BFS
	int * pre; // record the predecessors during BFS
	int * dis; // record the shortest path distances during BFS
	int* orderArr;
	int* Q;
	int front;
	int rear;
	int order;
public:
	int n; // the number of vertices, the ids of the vertices are from 0 to n-1
	Vertex ** adj; // adj[i] points the head of the adjacency list of vertex i, for i from 0 to n-1
	BFSGraph(int n_input); // constructor
	void addToList(int num, Vertex* & list);
	void buildMatrix(int* adjM);//builds adjM from file
	void SetAdjLists(int * adjM); // build the adjacency lists from the adjacency matrix adjM
	void PrintAdjLists(); // print the adjacency lists of the graph
						  // the following two functions are for the BFS traversal as we discussed in class
	void BFS(int id = 0); // BFS traversal, id is the source vertex, with default 0
	void BFSVisit(int id); // actually does BFS, search a connected component from id
	void PrintSP(int source, int v); // Print the shortest path from the source to v and the
									 // shortest path distance from source to v
};