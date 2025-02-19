#include "worker.h"

Worker::Worker(int number, std::string name, std::string position)
{
    this->setnumber(number);
    this->setposition(position);
    this->setname(name);
}

void Worker::showInfo() const
{

    std::cout << "员工编号是" << this->getnumber();
    std::cout << "员工名字是" << this->getname();
    std::cout << "员工职位是" << this->getposition();
}

std::string Worker::get_job_description() const
{
    // 返回岗位职责的描述
    return "完成经理交给的任务";
}