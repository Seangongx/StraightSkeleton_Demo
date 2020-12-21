#ifndef VERTEX_H
#define VERTEX_H
#include <memory>
#include "Edge.h"
#include "Ray.h"

enum Type{
	NONE,
	EDGE, 
	SPLIT,
	INTER
};

class Vertex{
public:
	Point<double> coord;
	Ray *bisector;
	Edge *inEdge;
	Edge *outEdge;
	bool processed;
	Type type;

	Vertex(double x, double y);
	Vertex(Point<double> X);
	~Vertex();

	Vertex operator - (const Vertex &rhs);
	double operator * (const Vertex &rhs);
    void calculateBisector();
	void setType(Type t);
};
#endif
