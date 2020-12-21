#ifndef CLL_H
#define CLL_H
#include "CLLNode.h"

class CLL{
public:
	CLLNode *head;
	//��Ҫ���µ�size��С
	int size;

	CLL();
	CLL(CLLNode *_head);
	~CLL();

	int getSize();
    void print();
	bool verifyNode(CLLNode *node);//ûɶ��
	bool isEmpty();
	void showRemain(V_P_P &Arc);
	void insertNode(CLLNode *node, CLLNode *forward, CLLNode *back);
	void addLast(CLLNode *vertex);
	void detachNode(CLLNode *node, CLLNode *its);
	void updateHead(CLLNode *newhead);
};
#endif
