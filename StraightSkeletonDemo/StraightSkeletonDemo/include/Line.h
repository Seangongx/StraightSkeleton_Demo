#ifndef LINE_H 
#define LINE_H
#include "Point.h"
//Դ�����д������޸�(pΪԴ��1��qΪ�˵�2)

class Line{
public:
	double a, b, c;	
	Line() {};
	~Line() {};
	Line(double a, double b, double c){
		this->a  = a;
		this->b  = b;
		this->c  = c;
	}
	Line(Point<double> p, Point<double> q){
        if (p.y == q.y) // Horizontal lines
        {
            a = 0;
            if (q.x > p.x)
            {
                b = 1;
                c = -p.y;
            }
            else if (q.x == p.x)
            {
                b = 0;
                c = 0;
            }
            else
            {
                b = -1;
                c = p.y;
            }
        }
        else if (p.x == q.x) // Vertical lines
        {
            b = 0;
            if (q.y > p.y)
            {
                a = -1;
                c = p.x;
            }
            else if (q.y == p.y)
            {
                a = 0;
                c = 0;
            }
            else
            {
                a = 1;
                c = -p.x;
            }
        }
        else // General lines
        {
            a = p.y - q.y;
            b = q.x - p.x;
            c = -p.x * a - p.y * b;
        }	
	}
	void print() {
		cout << a << "x + " << b << "y + " << c << " = 0" << endl;
	}
	string toString() {
		string re = to_string(a) + "x + " + to_string(b) + "y + " + to_string(c) + " = 0";
		return re;
	}
};
#endif
