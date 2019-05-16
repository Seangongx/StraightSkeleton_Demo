#ifndef INTERSECTION_H
#define INTERSECTION_H
#include <vector>
#include <utility> //pair<>
#include "CLLNode.h"

constexpr double DISTANCE = 0.000001;

#define V_P_P vector<pair<Point<double>, Point<double>>>

class Intersection{
public:
	double distance;
	bool intersected;
	Point<double> Pos;
	//Va is the current node
	CLLNode *Va;
	//Vb is the next node(reverse clock)
	CLLNode *Vb;

    Intersection();
	//rayi is the angular bisector of current node vi
	Intersection(CLLNode *_va, CLLNode *_vb);

	void intersect(Ray* ray1, Ray* ray2);
	double getDistance();
    bool isProcessed();
	bool createArc(V_P_P &Arc);
	bool operator == (const Intersection &rhs) const;
    CLLNode* createInterNode();
};
#endif
