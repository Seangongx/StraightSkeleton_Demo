#ifndef CLLNODE_H
#define CLLNODE_H

class CLLNode;

#include <memory>
#include "Vertex.h"
#include "CLL.h"

class CLLNode{
public:
    Vertex *item;
    CLL *container;
    CLLNode *forward;
    CLLNode *back;
    CLLNode();
    CLLNode(Vertex *_value);
    CLLNode(CLL *_cont, Vertex *_value);
    CLLNode(CLL *_cont, Vertex *_value, CLLNode *_f,CLLNode *_b);
    void detach();
    void insertBetween(CLL *_cont, CLLNode *_prev,CLLNode *_next);
};
#endif
