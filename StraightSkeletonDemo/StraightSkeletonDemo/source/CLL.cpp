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
//        //_v->cllNode = clln;这句话暂时注释看看情况
//		head = clln;
//    }
//	else {
//		cout << "cannot create no head node!" << endl;
//	}
//}

//如果不是一次性添加完，则print会出现问题
void CLL::addLast(CLLNode *vertex, CLLNode *forward, CLLNode *back) {
	if(head == nullptr){
#ifdef INFORMATION
		cout << "NO head so we add head:" << vertex->item->coord.toString() << " and the pointer:" << vertex << endl;
#endif
		//_v->cllNode = clln;这句话暂时注释看看情况
		head = vertex;//同时顶点的head就是顶点本身
		vertex->forward = forward;
		vertex->back = back;
		forward->back = vertex;
		back->forward = vertex;
		forward->forward = head;
		head->back = forward;
    }
	else {
		//CLLNode* clln(new CLLNode(_v, head, head->back, head));//切记这里的错误是赋值没有附上
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
