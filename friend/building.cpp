#include "building.h"
Goodgay::Goodgay()
{
    building = new Building;
}
void Goodgay::visit()
{
    cout << " goodgay is looking " << building->bedroom << endl;
    cout << " goodgay is looking " << building->sittingroom << endl;
}
void Goodgay::visit01()
{
    // cout<<"goodgay is looking"<<building->bedroom<<endl;
    cout << "goodgay01 is looking" << building->sittingroom << endl;
}
Building::Building()
{
    this->bedroom = "卧室";
    this->sittingroom = "客厅";
}
