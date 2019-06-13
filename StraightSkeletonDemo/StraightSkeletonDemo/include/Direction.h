#ifndef DIRECTION_H 
#define DIRECTION_H
#include "Point.h"

class Direction{
public:
	double deltaX, deltaY;
	double dx, dy;

	Direction(){};
	Direction(Point<double> start, Point<double> end){
		Point<double> P = end - start;
		deltaX = P.x;
		deltaY = P.y;
	}
	Direction(double deltaX, double deltaY){
		this->deltaX = deltaX;
		this->deltaY = deltaY;
	}
	~Direction() {};

	double operator * (const Direction &rhs) {
		return (deltaX * rhs.deltaY - deltaY * rhs.deltaX);
	}
	bool operator != (const Direction &rhs) {
		bool x = abs(deltaX - rhs.deltaX) > DISTANCE;
		bool y = abs(deltaY - rhs.deltaY) > DISTANCE;
		return (x || y);
	}
	double mod() {
		return sqrt(deltaX * deltaX + deltaY * deltaY);
	}
    void makeUnit(){
		double M = mod();
        deltaX = deltaX / M;
        deltaY = deltaY / M;
    }
	void print() {
		cout << "<" << deltaX << "," << deltaY << ">" ;
	}
	string toString() {
		string re = "<" + to_string(deltaX) + "," + to_string(deltaY) + ">";
		return re;
	}
};
#endif
