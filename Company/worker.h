#include <iostream>
#include <string>
#include "staff.h"
#ifndef WORKER_H
#define WORKER_H
#endif

class Worker : public Staff
{
public:
    Worker(int number, std::string name, std::string position);
    virtual void showInfo() const override;
    std::string get_job_description() const override;
};