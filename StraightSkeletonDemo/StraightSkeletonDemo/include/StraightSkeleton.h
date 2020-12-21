#ifndef STRAIGHTSKELETON_H
#define STRAIGHTSKELETON_H
#include <vector>
#include <queue>
#include <utility>
#include "Intersection.h"
#include "CLL.h"

class StraightSkeleton{
public:
	//双向循环活动顶点链表
	CLL cllist;
	//顶点表
	vector<CLLNode*> V_T;
	//边界表
	vector<Edge*> E_T;
	//交点表
	vector<Intersection> I_T;
	//骨架对
	V_P_P Arc;

	//a>b为小顶堆，默认a<b是大顶堆
	struct OrderByDistance {
		bool operator() (Intersection &a, Intersection &b) {
			return a.distance > b.distance;
		}
	};
	priority_queue<Intersection, vector<Intersection>, OrderByDistance> PQ;

	StraightSkeleton(vector<Point<double>> P);

	void initialVertex(vector<Point<double>> P);
	void initialEdge();
	void initialBisector();
	void initialIntersection();
	void initialEvent();

	double dist(Point<double> v1, Point<double> v2);
	bool insidePoly(CLLNode *head, Point<double> Pos);
	bool noInter();
    void findNearestI(CLLNode *vminus1, CLLNode *v, CLLNode *vplus1, double oldDis);
    void processIntersections();
};
#endif

