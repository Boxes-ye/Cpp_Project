#include<iostream>
#include<string>
#include<cmath>
#include"circle.h"
#include"point.h"
#include"isincircle.h"
using namespace std;

int main(){
	Circle c;
	point center;
	center.setX(1);
	center.setY(1);
	c.setcenter(center);
	c.setr(2);
	point p;
	p.setX(2);
	p.setY(2);
	isincircle(p,c);
	return 0;
}