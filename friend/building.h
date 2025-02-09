#include <iostream>
#include <string.h>
#ifndef BUILDING_H
#define BUILDING_H
using namespace std;
class Building;
class Goodgay
{
private:
    Building *building; // building是一个Building类的指针
public:
    Goodgay();    //构造函数
    void visit(); //定义Goodgay类定义两个函数
    void visit01();
};
class Building
{
    friend void Goodgay::visit(); // Goodgay类中的visit作为Building的友元
private:
    string bedroom; //只有友元可以访问private变量
public:
    string sittingroom;

public:
    Building();
};
#endif