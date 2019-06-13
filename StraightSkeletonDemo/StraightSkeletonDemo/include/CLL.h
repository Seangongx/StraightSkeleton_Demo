#ifndef CLL_H
#define CLL_H
#include "CLLNode.h"

class CLL{
public:
	CLLNode *head;
	//int count;

	CLL();
	CLL(CLLNode *head);

	int Size();
    void print();
	bool verifyNode(CLLNode *node);
    //void addLast(Vertex *_v);
	void addLast(CLLNode *vertex, CLLNode *forward, CLLNode *back);
};
#endif
