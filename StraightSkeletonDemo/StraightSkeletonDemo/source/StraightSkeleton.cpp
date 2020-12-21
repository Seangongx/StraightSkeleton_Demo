#include "StraightSkeleton.h"

double StraightSkeleton::dist(Point<double> v1, Point<double> v2) {
	double dx = v1.x - v2.x, dy = v1.y - v2.y;
	if (abs(dx) < DISTANCE) dx = 0.0;
	if (abs(dy) < DISTANCE) dy = 0.0;
	return sqrt(dx * dx + dy * dy);
}

void StraightSkeleton::initialVertex(vector<Point<double>> P) {
	for (int i = 0; i < P.size(); i++) {
		Vertex *tempVi = new Vertex(P[i]);
		CLLNode *Vi = new CLLNode(tempVi);
		CLLNode *Vc = new CLLNode(tempVi);
		V_T.push_back(Vc);
		cllist.addLast(Vi);
	}

	int VTsize = V_T.size();
	VTsize = cllist.size;

	for (int current = 0; current < VTsize; current++) {
		int forward = current + 1, backward = current - 1;
		if (forward >= VTsize)
			forward = 0;
		if (backward < 0)
			backward = VTsize - 1;
		V_T[current]->head = cllist.head;
		V_T[current]->next = V_T[forward];
		V_T[current]->prev = V_T[backward];
		V_T[forward]->prev = V_T[current];
		V_T[backward]->next = V_T[current];
	}

	cllist.print();
}

void StraightSkeleton::initialEdge() {
	int VTsize = V_T.size();
	VTsize = cllist.size;

	Edge *En = new Edge(cllist.head->prev->item->coord, cllist.head->item->coord);
	cllist.head->item->inEdge = En;
	cllist.head->prev->item->outEdge = En;
	E_T.push_back(En);
	for (CLLNode *ptr = cllist.head->next; ptr != cllist.head; ptr = ptr->next) {
		Edge *En = new Edge(ptr->prev->item->coord, ptr->item->coord);
		ptr->item->inEdge = En;
		ptr->prev->item->outEdge = En;
		E_T.push_back(En);
	}

#ifdef INFORMATION
	cout << ptr->item->coord.toString() << "inEdge:" << ptr->item->inEdge->toString() << endl;
	cout << ptr->prev->item->coord.toString() << "outEdge:" << ptr->prev->item->outEdge->toString() << endl;
#endif
}

void StraightSkeleton::initialBisector() {
	cllist.head->item->calculateBisector();
	for (CLLNode *ptr = cllist.head->next; ptr != cllist.head; ptr = ptr->next) {
		ptr->item->calculateBisector();
	}
}

void StraightSkeleton::initialIntersection() {
	findNearestI(cllist.head->prev, cllist.head, cllist.head->next, 0.0);
	for (CLLNode *cur= cllist.head->next; cur!= cllist.head; cur = cur->next) {
		findNearestI(cur->prev, cur, cur->next, 0.0);
	}
}

void StraightSkeleton::initialEvent() {
	cllist.head->item->setType(NONE);
	for (CLLNode *cur = cllist.head->next; cur != cllist.head; cur = cur->next) {
		cur->item->setType(NONE);
	}
}


StraightSkeleton::StraightSkeleton(vector<Point<double>> P) {
	cout << "//created Vertices from points,and add the vertices to the circular linked list" << endl;
	initialVertex(P);

	cout << "//link edges one by one" << endl;
	initialEdge();

	cout << "//calculate bisector of all vertices" << endl;
	initialBisector();

	cout << "//for each vertex V compute the nearer intersection of the bisector bi with adjacent vertex bisectors bi-1 and bi+1" << endl;
	initialIntersection();

	cout << "//for each vertex V compute the state of event" << endl;
	initialEvent();

	processIntersections();
}

//注意为逆时针判断
bool StraightSkeleton::insidePoly(CLLNode *head, Point<double> Pos) {
	bool result = false;
	CLLNode *cur = head->next, *bck = cur->prev;

	while (cur != head) {
		if ((cur->item->coord.y > Pos.y) != (bck->item->coord.y > Pos.y) &&
			(Pos.x > (Pos.y - cur->item->coord.y) *
			(bck->item->coord.x - cur->item->coord.x) /
				(bck->item->coord.y - cur->item->coord.y) +
				cur->item->coord.x)) {
			result = !result;
		}
		cur = cur->next;
		bck = cur->prev;
	}
	if ((cur->item->coord.y > Pos.y) != (bck->item->coord.y > Pos.y) &&
		(Pos.x > (Pos.y - cur->item->coord.y) *
		(bck->item->coord.x - cur->item->coord.x) /
			(bck->item->coord.y - cur->item->coord.y) +
			cur->item->coord.x)) {
		result = !result;
	}
	return result;
}


bool StraightSkeleton::noInter() {
	if (cllist.head != nullptr && cllist.head->item->type == INTER)
		return false;
	CLLNode *point = cllist.head->next;
	for (; point != cllist.head; point = point->next) {
		if (point != nullptr && point->item->type == INTER)
			return false;
	}
	return true;
}

//最复杂的函数
void StraightSkeleton::findNearestI(CLLNode *vminus1, CLLNode *v, CLLNode *vplus1, double oldDis){
	Intersection Iminus1(vminus1, v);
	Intersection Iplus1(v, vplus1);
    Intersection res;

	if (!Iminus1.intersected && !Iplus1.intersected)
		return;
	if (Iminus1.intersected)
		res = Iminus1;
	if (Iplus1.intersected && Iminus1.distance > Iplus1.distance)
		res = Iplus1;

	if (oldDis > 0.0) {
		res.distance += oldDis;
	}

	if (Iminus1.intersected || Iplus1.intersected) {
		PQ.push(res);
		I_T.push_back(res);
	}
}


//循环处理优先级队列中的节点
void StraightSkeleton::processIntersections(){
    while(!PQ.empty()){
        Intersection X = PQ.top();
        PQ.pop();
		if (insidePoly(cllist.head, X.Pos)) {
			if (X.isProcessed())//如果X两个的两个标记均为已处理，则跳过，循环继续
				continue;
			if (X.createArc(Arc))//否则直接添加骨架，边事件处理，只有当成为最后三条骨架时才continue
			{
				cllist.head = nullptr;
				cllist.size = 0;//应该释放链表才对；
				break;
			}
			X.Va->item->processed = true;
			X.Vb->item->processed = true;
			CLLNode* cllnv = X.createInterNode();
			cllist.insertNode(cllnv, X.Vb->next, X.Va->prev);
			cllist.detachNode(X.Va, cllnv);
			cllist.detachNode(X.Vb, cllnv);
#ifdef INFORMATION
			cout << "//mark " << X.Pos.toString() << " va, vb as processed" << endl;
			cout << "//create new vertex for intersection and return a CLLNode" << endl;
			cout << "//compute the nearer intersection of the bisector bi with adjacent vertex bisectors bi-1 and bi+1" << endl;
			cout << "The intersection is :" << cllnv->item->coord.toString() << endl;
			cout << "and the bisector is :"; cllnv->item->bisector->print();
			cout << "//push it into the priority queue" << endl;
#endif
			findNearestI(cllnv->prev, cllnv, cllnv->next, X.distance);
		}
		cllist.print();
    }
	if (!cllist.isEmpty()) {
		cllist.showRemain(Arc);
	}
}
