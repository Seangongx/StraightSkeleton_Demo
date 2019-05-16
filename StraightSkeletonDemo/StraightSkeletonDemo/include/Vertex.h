#ifndef VERTEX_H
#define VERTEX_H
#include <memory>
#include "Edge.h"
#include "Ray.h"

enum Type{
	EDGE, 
	SPLIT
};

class Vertex{
public:
	Point<double> coord;
	Ray *bisector;
	Edge *inEdge;
	Edge *outEdge;
    //CLLNode *cllNode;
	bool processed;
	Type type;

	Vertex(double x, double y);
	Vertex(Point<double> X);
	~Vertex();

	Vertex operator - (const Vertex &rhs);
	double operator * (const Vertex &rhs);
	Type getType();
    void calculateBisector();
};
#endif
