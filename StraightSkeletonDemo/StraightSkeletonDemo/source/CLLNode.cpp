#include "CLLNode.h"

CLLNode::CLLNode() {};

CLLNode::CLLNode(Vertex *_v){
	this->item = _v;
	this->next = (this);
	this->prev = (this);
	this->head = (this);
	_v->processed = false;

#ifdef INFORMATION
	cout << "init single Cllnode" << item->coord.toString() << "and its pointer:" << this << endl;
#endif
}

CLLNode::~CLLNode() {
	this->item = nullptr;
	this->next = nullptr;
	this->prev = nullptr;
	this->head = nullptr;
}

void CLLNode::setHead(CLLNode *_head) {
	this->head = _head;
}