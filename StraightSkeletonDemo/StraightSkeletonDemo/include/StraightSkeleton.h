#ifndef STRAIGHTSKELETON_H
#define STRAIGHTSKELETON_H
#include <vector>
#include <queue>
#include <utility>
#include "Intersection.h"
#include "CLL.h"

class StraightSkeleton{
public:
	//˫��ѭ�����������
	CLL cllist;
	//�����
	vector<CLLNode*> V_T;
	//�߽��
	vector<Edge*> E_T;
	//�����
	vector<Intersection> I_T;
	//�Ǽܶ�
	V_P_P Arc;

	//a>bΪС���ѣ�Ĭ��a<b�Ǵ󶥶�
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

