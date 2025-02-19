#include "boss.h"

Boss::Boss(int number, std::string name, std::string position)
{
    this->setnumber(number);
    this->setposition(position);
    this->setname(name);
}

void Boss::showInfo() const
{

    std::cout << "员工编号是" << this->getnumber();
    std::cout << "员工名字是" << this->getname();
    std::cout << "员工职位是" << this->getposition();
}

std::string Boss::get_job_description() const
{
    // 返回岗位职责的描述
    return "负责管理公司所有事务";
}