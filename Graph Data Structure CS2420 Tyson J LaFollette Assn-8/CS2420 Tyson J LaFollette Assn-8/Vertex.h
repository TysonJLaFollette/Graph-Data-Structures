#pragma once
class Vertex {
public:
	int id;   // id for the vertex 
	Vertex * next;   // the next vertex in the adj list 
	Vertex(int input_id, Vertex *input_next = nullptr) {
		id = input_id;
		next = input_next;
	}
};