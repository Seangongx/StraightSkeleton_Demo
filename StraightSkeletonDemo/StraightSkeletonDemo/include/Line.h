#ifndef LINE_H 
#define LINE_H
#include "Point.h"
//Դ�����д������޸�(pΪԴ��source��qΪ�˵�end)

class Line {
public:
	double a, b, c;

	//�˴���Ĭ�Ϲ����Ƿ���֮��ļ̳���ʹ��Ĭ�Ϲ��캯��
	Line() {};
	Line(double _a, double _b, double _c) {
		this->a = _a;
		this->b = _b;
		this->c = _c;
	}
	Line(Point<double> _p, Point<double> _q) {
		if (_p.y == _q.y) // Horizontal lines
		{
			a = 0;
			if (_q.x > _p.x)
			{
				b = 1;
				c = -_p.y;
			}
			else if (_q.x == _p.x)
			{
				b = 0;
				c = 0;
			}
			else
			{
				b = -1;
				c = _p.y;
			}
		}
		else if (_p.x == _q.x) // Vertical lines
		{
			b = 0;
			if (_q.y > _p.y)
			{
				a = -1;
				c = _p.x;
			}
			else if (_q.y == _p.y)
			{
				a = 0;
				c = 0;
			}
			else
			{
				a = 1;
				c = -_p.x;
			}
		}
		else // General lines
		{
			a = _p.y - _q.y;
			b = _q.x - _p.x;
			c = -_p.x * a - _p.y * b;
		}
	}
	~Line() {};

	void print() {
		cout << a << "x + " << b << "y + " << c << " = 0" << endl;
	}
	string toString() {
		string re = to_string(a) + "x + " + to_string(b) + "y + " + to_string(c) + " = 0";
		return re;
	}
};
#endif
