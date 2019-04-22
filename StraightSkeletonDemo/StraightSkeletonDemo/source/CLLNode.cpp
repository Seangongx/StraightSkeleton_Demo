#include "CLLNode.h"
#include "Vertex.h"
#include "CLL.h"

CLLNode::CLLNode() {};

CLLNode::CLLNode(Vertex *_value){
	cout << "inside Cllnode" << this << endl;
	cout << _value->coord.toString() << endl;
	item = _value;

	_value->cllNode = (this);
	forward = (this);
	back = (this);
	_value->processed = false;
}

CLLNode::CLLNode(CLL *_cont, Vertex *_value){
	item = _value;
    _value->cllNode = (this);
	container = _cont;
	forward = (this);
	back = (this);
    _value->processed = false;
}

CLLNode::CLLNode(CLL *_cont, Vertex *_value, CLLNode *_f,CLLNode *_b){
	item = _value;
    cout << item->coord.toString() << endl;
    cout << "F: " << _f->item->coord.toString() << endl;
    cout << "B: " << _b->item->coord.toString() << endl;

	_value->cllNode = (this);
	container = _cont;
	forward = _f;
	back= _b;
	_b->forward = (this);
	_f->back= (this);
	_value->processed = false;
    cout << "Done with new addition!" << endl;
}

void CLLNode::detach(){
	back->forward = forward;
	forward->back = back;

	forward = back= NULL;
	container = NULL;
}

void CLLNode::insertBetween(CLL *_cont, CLLNode *_prev,CLLNode *_next){
	_prev->forward = (this);
	this->forward = _next;
	_next->back = (this);
	this->back = _prev;
	this->container = _cont;
}
