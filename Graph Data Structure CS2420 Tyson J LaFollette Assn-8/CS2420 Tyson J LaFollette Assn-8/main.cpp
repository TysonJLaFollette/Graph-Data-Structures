#include"BFSGraph.h"
#include"DFSGraph.h"
#include<iostream>
using namespace std;

int main() {
	BFSGraph* myBFS = new BFSGraph(8);
	int* M1 = new int[64];
	myBFS->buildMatrix(M1);
	myBFS->SetAdjLists(M1);
	myBFS->PrintAdjLists();
	myBFS->BFS();
	for (int i = 1; i < 8; i++) {
		myBFS->PrintSP(0, i);
	}

	cout << "Now Depth First Search: \n";
	DFSGraph* myDFS = new DFSGraph(8);
	int* M2 = new int[64];
	myDFS->buildMatrix(M2);
	myDFS->setAdjLists(M2);
	myDFS->printAdjLists();
	myDFS->DFS(0);
	myDFS->PrintReachableNodes(0);
	system("pause");
}