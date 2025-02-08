
#include "circle.h"

//设置半径
void Circle::setr(double r)
{
    m_r = r;
}
//获取半径
double Circle::getr()
{
    return m_r;
}

//设置圆心
void Circle::setcenter(point center)
{
    m_center = center;
}
//获取圆心
point Circle::getcenter()
{
    return m_center;
}

//判断点和圆关系
