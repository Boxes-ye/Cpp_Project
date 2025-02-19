#include <iostream>
#include <string>
#ifndef STAFF_H
#define STAFF_H

class Staff
{

private:
    int m_number;
    std::string m_name;
    std::string m_position;

public:
    virtual void showInfo() const = 0;

    void setnumber(int num) { m_number = num; }
    int getnumber() const { return m_number; };
    void setname(std::string name) { m_name = name; }
    std::string getname() const { return m_name; };
    void setposition(std::string pos) { m_position = pos; }
    std::string getposition() const { return m_position; };
    virtual std::string get_job_description() const = 0;
};
#endif