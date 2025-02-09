#pragma once
#include <iostream>
using namespace std;
#include "point.h"

class Circle
{
private:
	double m_r;

	point m_center;

public:
	//设置半径
	void setr(double r);
	//获取半径
	double getr();

	//设置圆心
	void setcenter(point center);
	//获取圆心
	point getcenter();
};
//判断点和圆关系
