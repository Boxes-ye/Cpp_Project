#include <iostream>
#include <string>
#include "staff.h"
#ifndef MANGER_H
#define MANGER_H

class Manger : public Staff
{
public:
    Manger(int number, std::string name, std::string position);
    virtual void showInfo() const override;
    std::string get_job_description() const override;
};
#endif