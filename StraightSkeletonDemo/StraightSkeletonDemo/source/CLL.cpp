#include "CLL.h"
#include "CLLNode.h"

CLL::CLL(){
	this->head = nullptr;
	this->size = 0;
}

CLL::CLL(CLLNode *_head) {
    this->head = _head;
	this->size = getSize();
}

CLL::~CLL() {
	head = nullptr;
}

int CLL::getSize() {
	int count = 1;
	CLLNode *first = head, *last = head->prev;
	while (first != last) {
		first = first->next;
		count++;
	}
	return count;
}

bool CLL::verifyNode(CLLNode* node){
	return (node->head == this->head);
}

bool CLL::isEmpty() {
	if (this->head == nullptr)
		return true;
	if (this->size == 0)
		return true;
	
	return false;
}

void CLL::showRemain(V_P_P &Arc) {
	if (this->size == 1)
		return;
	CLLNode *point = this->head;
	while (point != this->head->prev) {
		if (point->item->type == INTER)	{
			break;
		}
		point = point->next;
	}
	CLLNode *comp = point->next;
	while (point->item->type == INTER && comp != point) {
		Arc.push_back(make_pair(point->item->coord, comp->item->coord));
		comp = comp->next;
	}
}

void CLL::print(){
    if(head != nullptr){
        cout << "current CLL and the head: " << head->item->coord.toString() << endl;
        CLLNode *x = head;
        do{
			cout << x->item->coord.toString() << "->";
			x = x->next;
		} while (x != head);
    }
    cout << endl;
}

void CLL::insertNode(CLLNode *vertex, CLLNode *forward, CLLNode *back) {
	if(head == nullptr){
		head = vertex;//同时顶点的head就是顶点本身
		head->next = forward;
		head->prev = back;
		forward->prev = head;
		back->next = head;
		forward->next = back;
		back->prev = forward;

#ifdef INFORMATION
		cout << "NO head so we add head:" << head->item->coord.toString() << " and the pointer:" << vertex << endl;
		cout << "it's forward node is: " << head->next->item->coord.toString() << endl;
		cout << "and it's backward node is: " << head->prev->item->coord.toString() << endl;
#endif
    }  
	else {
		vertex->head = head;
		vertex->next = forward;
		vertex->prev = back;
		forward->prev = vertex;
		back->next = vertex;

#ifdef INFORMATION
		cout << "add node between:" << vertex->prev->item->coord.toString() << " and " << vertex->next->item->coord.toString() << endl;
#endif
	}

	this->size++;
}

//如果不是一次性添加完，则print会出现问题
void CLL::addLast(CLLNode *vertex) {
	if (head == nullptr) {
		head = vertex;//同时顶点的head就是顶点本身
#ifdef INFORMATION
		cout << "NO head so we add head:" << vertex->item->coord.toString() << " and the pointer:" << vertex << endl;
#endif
	}
	else {
		CLLNode *rear = head->prev;
		vertex->head = head;
		vertex->next = head;
		vertex->prev = rear;
		rear->next = vertex;
		head->prev = vertex; 
#ifdef INFORMATION
			cout << "add node at rear:" << vertex->item->coord.toString() << " and the pointer:" << vertex << endl;
#endif
	}

	this->size++;
}

void CLL::detachNode(CLLNode *node, CLLNode *itsc) {
	if (node == head) {
		if (itsc != nullptr) {
			updateHead(itsc);
		}
		else {
			updateHead(node->next);
		}
	}

	this->size--;
}

void CLL::updateHead(CLLNode *newhead) {
	this->head = newhead;
	for (CLLNode *current = head->next; current != head; current = current->next) {
		current->head = newhead;
	}
}