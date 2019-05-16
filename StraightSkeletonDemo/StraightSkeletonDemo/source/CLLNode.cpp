#include "CLLNode.h"

CLLNode::CLLNode() {};

CLLNode::CLLNode(Vertex *_v){
	item = _v;
	forward = (this);
	back = (this);
	head = (this);

	//_v->cllNode = (this);
	_v->processed = false;
	cout << "init single Cllnode" << item->coord.toString() << "and its pointer:" << this << endl;
}

//CLLNode::CLLNode(Vertex *_v){
//	cout << "inita Cllnode current: " << _v->coord.toString() << endl;
//	item = _v;
//	forward = (this);
//	back = (this);
//
//	//_v->cllNode = (this);
//	_v->processed = false;
//}

CLLNode::CLLNode(Vertex *_v, CLLNode *_f,CLLNode *_b, CLLNode * _h){
	item = _v;
	forward = _f;
	back = _b;
	head = _h;
   
	//_v->cllNode = (this);
	_b->forward = (this);
	_f->back= (this);
	_v->processed = false;

	cout << "init current Cllnode: " << item->coord.toString() << "and its pointer:" << this << endl;
	cout << "it's forward node is: " << forward->item->coord.toString() << endl;
	cout << "and it's backward node is: " << back->item->coord.toString() << endl;
}

void CLLNode::detach(){
	back->forward = forward;
	forward->back = back;

	forward = nullptr;
	back = nullptr;
	head = nullptr;
}

void CLLNode::insertBetween(CLLNode *_prev, CLLNode *_next) {
	_prev->forward = (this);
	forward = _next;
	_next->back = (this);
	back = _prev;
}

void CLLNode::setHead(CLLNode *_head) {
	head = _head;
}

