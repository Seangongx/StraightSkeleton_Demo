#ifndef CLLNODE_H
#define CLLNODE_H
#include <memory>
#include "Vertex.h"

class CLLNode{
public:
    Vertex *item;
    CLLNode *forward;
    CLLNode *back;
	CLLNode *head;

    CLLNode();
    CLLNode(Vertex *_v);
	//CLLNode(Vertex *_v);
	CLLNode(Vertex *_value, CLLNode *_f, CLLNode *_b, CLLNode *_h);

	void setHead(CLLNode *head);
    void detach();
	void insertBetween(CLLNode *_prev,CLLNode *_next);
};
#endif
