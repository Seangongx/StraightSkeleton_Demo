#ifndef CLL_H
#define CLL_H
#include "CLLNode.h"

class CLL{
public:
	CLLNode *head;

	CLL();
	CLL(CLLNode *head);


    void print();
	bool verifyNode(CLLNode *node);
    //void addLast(Vertex *_v);
	void addLast(CLLNode *vertex, CLLNode *forward, CLLNode *back);
};
#endif
