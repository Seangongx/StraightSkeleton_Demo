#include "Vertex.h"

Vertex::Vertex(double x, double y){
	coord = Point<double>(x, y);
	bisector = new Ray();
	inEdge = NULL;
	outEdge = NULL;
}

Vertex::Vertex(Point<double> X){
	coord = X;
	bisector = new Ray();
	inEdge = NULL;
	outEdge = NULL;
}

Vertex::~Vertex() {};


//感觉并不会有什么引用
Vertex Vertex::operator - (const Vertex &rhs){
	Point<double> P(coord.x - rhs.coord.x, coord.y - rhs.coord.y);
	return Vertex(P);
}

double Vertex::operator * (const Vertex &rhs){
	return (coord.x*rhs.coord.y - coord.y*rhs.coord.x);
}

//计算几何判断
Type Vertex::getType(){
	Direction in(inEdge->start, inEdge->end), out(outEdge->start, outEdge->end);
	if((in * out) > 0)//面积大于零则第二条方向位于第一条左边（逆时针方向）
		type = EDGE;
	else
		type = SPLIT;
	return type;
}

void Vertex::calculateBisector(){
    cout << "Calculate Bisector for " << coord.toString() << endl;
	cout << "the inward edge:" << inEdge->end.toString() <<  inEdge->start.toString()<< endl;
	cout << "and the outward edge:" << outEdge->end.toString() <<  outEdge->start.toString()<< endl;

	Direction Din(inEdge->end, inEdge->start);
	Direction Dout(outEdge->start, outEdge->end);
	Din.makeUnit();
	Dout.makeUnit();

	Din.deltaX = (Din.deltaX + Dout.deltaX)/2;
	Din.deltaY = (Din.deltaY + Dout.deltaY)/2;
	bisector->source = Point<double>(coord.x, coord.y);
	bisector->direction = Din;
	bisector->rayline = bisector->getSupportingLine();
	cout << "so the bisector is:";
	bisector->print();
}



