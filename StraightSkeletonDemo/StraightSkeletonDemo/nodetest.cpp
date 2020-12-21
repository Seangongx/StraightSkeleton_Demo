#include "CLL.h"

int main()
{
	Vertex a1(1.0, 1.0);
	Vertex a2(2.0, 2.0);
	Vertex a3(3.0, 3.0);
	Vertex a4(4.0, 4.0);

	CLLNode n1(&a1);
	CLLNode n2(&a2);
	CLLNode n3(&a3);
	CLLNode n4(&a4);

	CLL cll(&n1);
	cll.print();
	cll.insertNode(&n2, cll.head->prev, cll.head);
	cll.print();
	cll.addLast(&n3);
	cll.print();
	cll.addLast(&n4);
	cll.print();

	return 0;
}