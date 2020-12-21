#ifndef CLLNODE_H
#define CLLNODE_H
#include <memory>
#include "Vertex.h"
#include <vector>

#define V_P_P vector<pair<Point<double>, Point<double>>>

class CLLNode{
public:
    Vertex *item;
    CLLNode *next;
    CLLNode *prev;
	CLLNode *head;

    CLLNode();
    CLLNode(Vertex *_v);
	~CLLNode();

	void setHead(CLLNode *head);
};
#endif
