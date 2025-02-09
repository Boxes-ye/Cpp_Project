#include "isincircle.h"
//判断点与圆位置关系
void isincircle(point p, Circle c)
{
	//计算距离
	double distance = sqrt((p.getX() - c.getcenter().getX()) * (p.getX() - c.getcenter().getX()) + (p.getY() - c.getcenter().getY()) * (p.getY() - c.getcenter().getY()));
	//计算半径的平方
	double r = c.getr() * c.getr();
	//判断
	if (distance > r)
	{
		cout << "点在圆外" << endl;
	}
	else if (distance == r)
	{
		cout << "点在圆上" << endl;
	}
	else if (distance < r)
	{
		cout << "点在圆内" << endl;
	}
}