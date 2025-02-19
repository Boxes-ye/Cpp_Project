#include "manger.h"

Manger::Manger(int number, std::string name, std::string position)
{
    this->setnumber(number);
    this->setposition(position);
    this->setname(name);
}

void Manger::showInfo() const
{

    std::cout << "员工编号是" << this->getnumber();
    std::cout << "员工名字是" << this->getname();
    std::cout << "员工职位是" << this->getposition();
}

std::string Manger::get_job_description() const
{
    // 返回岗位职责的描述
    return "完成老板交给的任务,并下发任务给员工";
}