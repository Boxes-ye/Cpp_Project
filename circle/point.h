#pragma once//防止重复包含
#include <iostream>
using namespace std;
class point
{
private:
	int m_x;
	int m_y;
public:
//设置x
void setX(int x);//point::是指明是成员函数
//获取x
int getX();
//设置y
void setY(int y);
//获取y
int getY();
};
