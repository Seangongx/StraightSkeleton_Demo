#include "CLL.h"
#include "CLLNode.h"

CLL::CLL(){
	head = nullptr;
}

CLL::CLL(CLLNode* head){
    this->head = head;
}

bool CLL::verifyNode(CLLNode* node){
	return (node->head == this->head);
}

void CLL::print(){
    if(head != nullptr){
        cout << "current CLL and the head: " << head->item->coord.toString() << endl;
        CLLNode *x = head;
        do{
			cout << x->item->coord.toString() << "->";
			x = x->forward;
		} while (x != head);
    }
    cout << endl;
}

//void CLL::addLast(Vertex *_v){
//    if(head == nullptr){
//		CLLNode *clln(new CLLNode(_v));
//		cout << "NO head so we add head:" << clln->item->coord.toString() << "and the pointer:" << clln << endl;
//        //_v->cllNode = clln;��仰��ʱע�Ϳ������
//		head = clln;
//    }
//	else {
//		cout << "cannot create no head node!" << endl;
//	}
//}

//�������һ��������꣬��print���������
void CLL::addLast(CLLNode *vertex, CLLNode *forward, CLLNode *back) {
	if(head == nullptr){
#ifdef INFORMATION
		cout << "NO head so we add head:" << vertex->item->coord.toString() << " and the pointer:" << vertex << endl;
#endif
		//_v->cllNode = clln;��仰��ʱע�Ϳ������
		head = vertex;//ͬʱ�����head���Ƕ��㱾��
		vertex->forward = forward;
		vertex->back = back;
		forward->back = vertex;
		back->forward = vertex;
		forward->forward = head;
		head->back = forward;
    }
	else {
		//CLLNode* clln(new CLLNode(_v, head, head->back, head));//�м�����Ĵ����Ǹ�ֵû�и���
		//CLLNode* clln(new CLLNode(vertex, forward, back, head));
#ifdef INFORMATION
		cout << "add node at rear:" << vertex->item->coord.toString() << " and the pointer:" << vertex << endl;
#endif
		vertex->head = head;
		vertex->forward = forward;
		vertex->back = back;
		forward->back = vertex;
		back->forward = vertex;
	}
}
