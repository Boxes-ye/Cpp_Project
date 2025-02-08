#include<iostream>
#include<string.h>
#ifndef BUILDING_H
#define BUILDING_H
using namespace std;
class Building;
class Goodgay{
    private:
    Building *building;
    public:
    Goodgay();
    void visit();
    void visit01();
    
};
class  Building{
    friend void Goodgay::visit();
    private:
    string bedroom;
    public:
    string sittingroom;
    public:
    Building();


};
#endif