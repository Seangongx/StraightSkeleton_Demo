#ifndef STRAIGHTSKELETON_H
#define STRAIGHTSKELETON_H
#include <vector>
#include <queue>
#include <utility>
#include "Intersection.h"
#include "CLL.h"

class StraightSkeleton{
public:
	//�����
	vector<CLLNode*> V_T;
	//�߽��
	vector<Edge*> E_T;
	//�����
	vector<Intersection> I_T;
	//�Ǽܶ�
	V_P_P Arc;
	//vector<Ray*> R_T;

	//a>bΪС���ѣ�Ĭ��a<b�Ǵ󶥶�
	struct OrderByDistance {
		bool operator() (Intersection &a, Intersection &b) {
			return a.distance > b.distance;
		}
	};
	priority_queue<Intersection, vector<Intersection>, OrderByDistance> PQ;

	StraightSkeleton(vector<Point<double>> P);

	double dist(Point<double> v1, Point<double> v2);
	bool insidePoly(CLLNode *head, Point<double> Pos);
    void findNearestI(CLLNode *vminus1, CLLNode *v, CLLNode *vplus1, double oldDis);
	//void findNearestI2(CLLNode *vminus1, CLLNode *v, CLLNode *vplus1, double oldDis);
    void processIntersections();
};
#endif

