#ifndef	EDGE_H
#define EDGE_H
#include "line.h"

class Edge{
public:
	Point<double> start;
	Point<double> end;
	Line edgeline;//TODO:

	Edge() {};
	Edge(Point<double> _start, Point<double> _end){
		this->start = _start;
		this->end = _end;
		edgeline = Line(_start, _end);
	}
	~Edge() {};

	void print(){
		cout << "[" << start.toString() << " -> " << end.toString() << "] : ";
		edgeline.print();
	}
	string toString(){
		string re = "[" + start.toString() + " -> " + end.toString() + "] : " + edgeline.toString();
		return re;
	}
};
#endif
