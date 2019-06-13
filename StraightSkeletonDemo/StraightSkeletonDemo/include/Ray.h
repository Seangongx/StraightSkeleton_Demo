#ifndef RAY_H
#define RAY_H
#include "Direction.h"
#include "Line.h"

class Ray{
public:
	//Vertex *source;
	Point<double> source;
	Direction direction;
	Line rayline;

    Ray();
	Ray(Point<double> s, Direction dir);
	~Ray();

	Line getSupportingLine();
	void print();
};
#endif
