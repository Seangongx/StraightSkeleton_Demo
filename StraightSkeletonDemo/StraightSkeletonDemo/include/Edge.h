#ifndef	EDGE_H
#define EDGE_H
#include "line.h"

class Edge{
public:
	Point<double> start;
	Point<double> end;
	Line edgeline;//TODO:

	Edge() {};
	~Edge() {};
	Edge(Point<double> start, Point<double> end){
		this->start = start;
		this->end = end;
	}

	void print(){
		cout << "[" << start.toString() << " -> " << end.toString() << "]" << endl;
	}
	string toString(){
		string re = "[" + start.toString() + " -> " + end.toString() + "]";
		return re;
	}
};
#endif
