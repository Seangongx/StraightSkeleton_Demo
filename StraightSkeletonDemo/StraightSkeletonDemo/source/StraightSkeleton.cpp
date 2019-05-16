#include "StraightSkeleton.h"

double StraightSkeleton::dist(Point<double> v1, Point<double> v2) {
	double dx = v1.x - v2.x, dy = v1.y - v2.y;
	if (abs(dx) < DISTANCE) dx = 0.0;
	if (abs(dy) < DISTANCE) dy = 0.0;
	return sqrt(dx * dx + dy * dy);
}

StraightSkeleton::StraightSkeleton(vector<Point<double>> P) {
	cout << "//created Vertices from points" << endl;
	for (int i = 0; i < P.size(); i++) {
		Vertex *tempVi = new Vertex(P[i]);
		CLLNode *Vi = new CLLNode(tempVi);
		V_T.push_back(Vi);
	}
	int VTsize = V_T.size();

	cout << "//add the vertices to the circular linked list" << endl;
	CLL* lav(new CLL());
	cout << "YES" << endl;
	for (int current = 0; current < VTsize; current++) {
		int forward = current + 1, backward = current - 1;
		if (forward >= VTsize)
			forward = 0;
		if (backward < 0)
			backward = VTsize - 1;
		V_T[current]->item->coord.print();
		lav->addLast(V_T[current], V_T[forward], V_T[backward]);
	}

	lav->print();

	cout << "//link edges one by one" << endl;
	//��β�����ĵ�һ����
	Edge *En(new Edge(V_T[VTsize - 1]->item->coord, V_T[0]->item->coord));
	E_T.push_back(En);
	V_T[0]->item->inEdge = En;
	cout << V_T[0]->item->coord.toString() << "inEdge:" << V_T[0]->item->inEdge->toString() << endl;
	V_T[VTsize - 1]->item->outEdge = En;
	cout << V_T[VTsize - 1]->item->coord.toString() << "outEdge:" << V_T[VTsize - 1]->item->outEdge->toString() << endl;

	for (int i = 1; i < VTsize; i++) {
		Edge* Ei(new Edge(V_T[i - 1]->item->coord, V_T[i]->item->coord));
		V_T[i]->item->inEdge = Ei;
		cout << V_T[i]->item->coord.toString() << "inEdge" << V_T[i]->item->inEdge->toString() << endl;
		V_T[i - 1]->item->outEdge = Ei;
		cout << V_T[i - 1]->item->coord.toString() << "outEdge" << V_T[i - 1]->item->outEdge->toString() << endl;
		E_T.push_back(Ei);
	}

	cout << "//calculate bisector of all vertices" << endl;
	for (int i = 0; i < VTsize; i++) {
		V_T[i]->item->calculateBisector();
	}

	cout << "//for each vertex V compute the nearer intersection of the bisector bi with adjacent vertex bisectors bi-1 and bi+1" << endl;
	int N = VTsize;
	findNearestI(V_T[N - 2], V_T[N - 1], V_T[0]);
	findNearestI(V_T[N - 1], V_T[0], V_T[1]);
	for (int i = 1; i < N - 1; i++) {

		findNearestI(V_T[i - 1], V_T[i], V_T[i + 1]);
	}/*
	for (vector<Intersection>::iterator it = I_T.begin(); it != I_T.end(); it++)
	{
		PQ.push(*it);
	}*/

	processIntersections();
}

//��ӵĺ���
void StraightSkeleton::findNearestI(CLLNode *vminus1, CLLNode *v, CLLNode *vplus1){
	Intersection Iminus1(vminus1, v);
	Intersection Iplus1(v, vplus1);
    Intersection res;

	if (Iminus1.intersected)
		res = Iminus1;
	if (Iplus1.intersected && dist(res.Pos , v->item->coord) > dist(Iplus1.Pos, v->item->coord))
		res = Iplus1;

	vector<Intersection>::iterator it;
	if (Iminus1.intersected || Iplus1.intersected)
	{
		if (I_T.size() == 0)//��һ�֣���I_T��û���κ�Ԫ����
		{
			I_T.push_back(res);
			PQ.push(res);
			return;
		}
		for (it = I_T.begin(); it != I_T.end(); it++)
		{
			if (res == *it)
			{
				break;
			}
		}
		if (it == I_T.end())
		{
			if (I_T[I_T.size() - 1].distance >= res.distance)
			{
				if (I_T[I_T.size() - 1] == res)
				{
					return;
				}
				else
				{
					PQ.push(res);
				}
			}
			I_T.push_back(res);
		}
	}
}

//ѭ���������ȼ������еĽڵ�
void StraightSkeleton::processIntersections(){
    while(!PQ.empty()){
        Intersection X = PQ.top();
        PQ.pop();
        if(X.isProcessed())//���X������������Ǿ�Ϊ�Ѵ�����������ѭ������
            continue;
        if(X.createArc(Arc))//����ֱ����ӹǼܣ����¼�����ֻ�е���Ϊ��������Ǽ�ʱ��continue
            continue;
        cout << "//mark " << X.Pos.toString() << " va, vb as processed" << endl;
        X.Va->item->processed = true;
        X.Vb->item->processed = true;
        cout << "//create new vertex for intersection and return a CLLNode" << endl;
        CLLNode* cllnv = X.createInterNode();
        cout << "//compute the nearer intersection of the bisector bi with adjacent vertex bisectors bi-1 and bi+1" << endl;
		cout << "The intersection is :" << cllnv->item->coord.toString() << endl;
		cout << "and the bisector is :"; cllnv->item->bisector->print();
		cout << "//push it into the priority queue" << endl;
        findNearestI(cllnv->back, cllnv, cllnv->forward);
    }
}
