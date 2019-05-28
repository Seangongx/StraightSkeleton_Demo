#include "Intersection.h"

//ray1 is the angular bisector of current node vi
Intersection::Intersection()
{};

Intersection::Intersection(CLLNode *_va, CLLNode *_vb) {

	Va = _va;
	Vb = _vb;
	intersect(_va->item->bisector, _vb->item->bisector);
}

void Intersection::intersect(Ray* ray1, Ray* ray2) {
	Line L1 = ray1->getSupportingLine();
	Line L2 = ray2->getSupportingLine();
#ifdef INFORMATION
	cout << L1.toString() << " intersect with " << L2.toString() << endl;
#endif
	double det = L1.a*L2.b - L2.a*L1.b;
	double x, y;
	if (det == 0) {
		intersected = false;
		return;
	}
	else {
		intersected = true;
		x = (L2.b*(-L1.c) - L1.b*(-L2.c)) / det;
		y = (L1.a*(-L2.c) - L2.a*(-L1.c)) / det;
	}
	Pos.x = x;
	Pos.y = y;

	//calculate the distance from Ei
	getDistance();
}

double Intersection::getDistance() {
	
	Point<double> Vtx = Va->item->coord;
	//End������Va->item->outEdge->end,��Ϊ֮��Ķ�̬�ڵ�û������va��vb�����ӱ���
	Point<double> End = Vb->item->coord;//

	Direction VE(Vtx, End);
	Direction VP(Vtx, Pos);
	distance = abs((VP*VE) / (VE.mod()));//�������
	return distance;
}

//����
bool Intersection::isProcessed() {
	//According to Paper Va->processed && Vb->processed
	return (Va->item->processed || Vb->item->processed);
}

bool Intersection::createArc(V_P_P &Arc) {
	Point<double> Pa = Va->item->coord;
	Point<double> Pb = Vb->item->coord;
	if (Va->back->back->item == Vb->item) {
		Point<double> Pc = Va->back->item->coord;
		Arc.push_back(make_pair(Pa, Pos));//�ƺ�Դ������©д��
		Arc.push_back(make_pair(Pb, Pos));
		Arc.push_back(make_pair(Pc, Pos));
		Va->item->processed = true;//��ǰ����
		Vb->item->processed = true;
		Va->back->item->processed = true;//Ҳ����Pc
		return true;
	}
	Arc.push_back(make_pair(Pa, Pos));
	Arc.push_back(make_pair(Pb, Pos));
	return false;
}

CLLNode* Intersection::createInterNode() {
	Vertex* v(new Vertex(Pos));
	CLLNode* clln(new CLLNode(v, Vb->forward, Va->back, Va->head));//ע���ʼ�������Ĳ���
	//clln->insertBetween(Vb->forward, Va->back);//ע���ʼ�������Ĳ���
	clln->item->inEdge = Va->item->inEdge;
	clln->item->outEdge = Vb->item->outEdge;
	clln->item->calculateBisector();
	return clln;
}


bool Intersection::operator == (const Intersection &rhs) const {
	bool cx = abs(this->Pos.x - rhs.Pos.x) < DISTANCE;
	bool cy = abs(this->Pos.y - rhs.Pos.y) < DISTANCE;
	bool pva = this->Va == rhs.Va;
	bool pvb = this->Vb == rhs.Vb;
	return (cx && cy && pva && pvb);
}

