#ifndef STRAIGHTSKELETON_H
#define STRAIGHTSKELETON_H
#include <vector>
#include <queue>
#include <utility>
#include "Intersection.h"
#include "CLL.h"


class StraightSkeleton{
public:
	vector<CLLNode*> V_T;//顶点集合
	vector<Edge*> E_T;
	vector<Intersection> I_T;//用于对角线交点第一次计算比较的数组，与
	//vector<Ray*> R_T;
	V_P_P Arc;

	struct OrderByDistance {
		bool operator() (Intersection &a, Intersection &b) {
			return a.distance > b.distance;
		}
	};//a>b为小顶堆，默认a<b是大顶堆
	priority_queue<Intersection, vector<Intersection>, OrderByDistance> PQ;

	StraightSkeleton(vector<Point<double>> P);

	double dist(Point<double> v1, Point<double> v2);
    void findNearestI(CLLNode *vminus1, CLLNode *v, CLLNode *vplus1);
    void processIntersections();
};
#endif

