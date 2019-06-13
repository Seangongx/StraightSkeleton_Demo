#include "Ray.h"

Ray::Ray() {};

Ray::Ray(Point<double> s, Direction dir){
	source = s;
	direction = dir;
	rayline = getSupportingLine();
}

Ray::~Ray() {};

Line Ray::getSupportingLine(){
	double a, b, c;
	a = direction.deltaY;//a = -direction.deltaY;
	b = -direction.deltaX;//b = direction.deltaX;
	c = -a * source.x - b * source.y;
	Line L(a, b, c);
	return L;
}

void Ray::print(){
	source.print();
	cout << "and the direction:";
	direction.print();
}

