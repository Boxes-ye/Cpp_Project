#include <iostream>
#include <string>
#include "staff.h"
#ifndef BOSS_H
#define BOSS_H

class Boss : public Staff
{
public:
    Boss(int number, std::string name, std::string position);
    virtual void showInfo() const override;
    std::string get_job_description() const override;
};
#endif