#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <string>
using namespace std;

//点的精度
constexpr double DISTANCE = 0.000001;

template <class T>
class Point {
public:
	T x, y;

	Point() {
		x = 0; y = 0;
	}
	Point(T _x, T _y) {
		this->x = _x;
		this->y = _y;
	}
	~Point() {};

	bool operator == (const Point &rhs) const {
		return (x == rhs.x && y == rhs.y);
	}
	bool operator != (const Point &rhs) const {
		return (x != rhs.x || y != rhs.y);
	}
	Point operator - (const Point &rhs) {
		Point<T> P(x - rhs.x, y - rhs.y);
		return P;
	}
	void print() {
		cout << "(" << x << "," << y << ")";
	}
	string toString() {
		string re = "(" + to_string(x) + "," + to_string(y) + ")";
		return re;
	}
};
#endif
