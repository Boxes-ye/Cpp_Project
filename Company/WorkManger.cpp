#include "WorkManger.h"
#include "worker.h"
#include "boss.h"
#include "manger.h"
#include <memory>

int Randomint(int min, int max)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::mt19937 engine(seed);
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}

WorkManger::WorkManger()
{
    std::ifstream ifs;
    ifs.open(FILENAME, std::ios::in);
    //文件不存在情况
    if (!ifs.is_open())
    {
        std::cout << "文件为空" << std::endl;
        this->m_Staffnum = 0;
        this->isEmpty = true;
        // m_staff.size()=0;//不需要，容器会自动管理
        ifs.close();
        return;
    }
    //文件存在但为空
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        std::cout << "文件为空" << std::endl;
        this->m_Staffnum = 0;
        this->isEmpty = true;
        ifs.close();
        return;
    }
};

WorkManger::~WorkManger(){};

void WorkManger::Show_Menu()
{

    std::cout << "*********  欢迎使用职工管理系统！ **********\n"
              << "*************  0.退出管理程序  *************\n"
              << "*************  1.增加职工信息  *************\n"
              << "*************  2.显示职工信息  *************\n"
              << "*************  3.删除离职职工  *************\n"
              << "*************  4.修改职工信息  *************\n"
              << "*************  5.查找职工信息  *************\n"
              << "*************  6.按照编号排序  *************\n"
              << "*************  7.清空所有文档  *************\n"
              << "********************************************\n"
              << std::endl;
}

void WorkManger::Exit_Menu()
{

    std::cout << "欢迎下次使用" << std::endl;
}

void WorkManger::Load_Staff()
{
    m_staff.clear();
    std::ifstream ifs(FILENAME, std::ios::in);
    if (!ifs.is_open())
    {
        std::cerr << "无法打开文件: " << FILENAME << std::endl;
        return;
    }

    std::string line;
    int staff_count = 0;

    while (std::getline(ifs, line))
    {
        std::stringstream ss(line);
        int num;
        std::string name, position;

        // 先读取数字，再判断后续是否有逗号
        if (ss >> num)
        {
            if (ss.peek() == ',')
            {
                ss.ignore(); // 忽略逗号
            }
            // 读取姓名和职位字段
            if (std::getline(ss, name, ',') && std::getline(ss, position, ','))
            {
                // 成功解析，统计人数
                ++staff_count;

                // 根据职位创建对应的员工对象
                std::unique_ptr<Staff> worker = nullptr;
                if (position == "老板")
                {
                    worker = std::make_unique<Boss>(num, name, position);
                }
                else if (position == "经理")
                {
                    worker = std::make_unique<Manger>(num, name, position);
                }
                else if (position == "员工")
                {
                    worker = std::make_unique<Worker>(num, name, position);
                }
                else
                {
                    std::cout << "无效的职位信息: " << position << std::endl;
                    continue; // 跳过无效记录
                }

                m_staff.push_back(std::move(worker));
            }
            else
            {
                std::cout << "解析失败: " << line << std::endl;
            }
        }
        else
        {
            std::cout << "解析失败: " << line << std::endl;
        }
    }
    // 文件流对象在离开作用域时会自动关闭

    m_Staffnum = staff_count;
    std::cout << "职工人数为" << m_Staffnum << std::endl;
    // 输出所有读取到的员工信息
    for (const auto &staff : m_staff)
    {
        std::cout << "职工号： " << staff->getnumber()
                  << " 职工姓名： " << staff->getname()
                  << " 部门编号： " << staff->getposition() << std::endl
                  << " 岗位职责： " << staff->get_job_description() << std::endl;
    }
}

void WorkManger::Add_Staff()
{
    std::cout << "输入要添加的员工数量" << std::endl;
    int addnum = 0;
    std::cin >> addnum;
    this->Load_Staff();
    for (int i = 0; i < addnum; i++)
    {
        int number = Randomint(1, 10000);
        std::cout << "第" << i + 1 << "位员工的编号是" << number << std::endl;

        std::cout << "输入第" << i + 1 << "位员工的职位：" << std::endl;
        std::string position;
        std::cin >> position;

        std::cout << "输入第" << i + 1 << "位员工的姓名：" << std::endl;
        std::string name;
        std::cin >> name;

        if (position == "老板")
        {
            m_staff.push_back(std::make_unique<Boss>(number, name, position));
        }
        else if (position == "经理")
        {
            m_staff.push_back(std::make_unique<Manger>(number, name, position));
        }
        else if (position == "员工")
        {
            m_staff.push_back(std::make_unique<Worker>(number, name, position));
        }
        else
        {
            std::cout << "无效职位" << std::endl;
        }
    }
    std::ofstream ofs;
    ofs.open(FILENAME, std::ios::app);
    if (!ofs)
    {
        std::cout << "无法打开文件！" << std::endl;
        return;
    }
    for (int i = m_staff.size() - addnum; i < m_staff.size(); ++i)
    {
        ofs << m_staff[i]->getnumber() << ","
            << m_staff[i]->getname() << ","
            << m_staff[i]->getposition() << ","
            << " 岗位职责： " << m_staff[i]->get_job_description() << std::endl;
    }
    this->isEmpty = false;
    std::cout << "成功添加了" << addnum << "个职员信息" << std::endl;
    ofs.close();
    this->Load_Staff();
}

void WorkManger::Del_Staff()
{
    this->Load_Staff(); //无调用无法更新m_Staffnum

    if (m_Staffnum == 0)
    {
        std::cout << "文件不存在" << std::endl;
    }
    else
    {
        std::cout << "要删除的员工号：" << std::endl;
        int delnum = 0;
        std::cin >> delnum;
        auto it = std::find_if(m_staff.begin(), m_staff.end(), [delnum](const std::unique_ptr<Staff> &staff)
                               { return staff->getnumber() == delnum; });
        // it = std::find_if(container.begin(), container.end(), predicate);
        // auto:编译器会自动匹配类型
        // lambda函数：[capture](parameters) -> return_type { body }//返回类型可以省略

        if (it != m_staff.end()) //当没找到元素会返回m_staff.end()m_staff.end()
        {
            // 找到员工，删除
            m_staff.erase(it);
            m_Staffnum--; // 更新员工数量

            // 更新文件
            std::ofstream ofs(FILENAME, std::ios::trunc); // std::ios::trunc：清空内容再写入
            if (!ofs)
            {
                std::cout << "无法打开文件！" << std::endl;
                return;
            }

            for (const auto &staff : m_staff)
            {
                ofs << staff->getnumber() << ","
                    << staff->getname() << ","
                    << staff->getposition() << ","
                    << " 岗位职责： " << staff->get_job_description() << std::endl;
            }

            std::cout << "成功删除员工编号为 " << delnum << " 的信息。" << std::endl;
        }
        else
        {
            std::cout << "未找到员工编号为 " << delnum << " 的员工！" << std::endl;
        }
    }
}

void WorkManger::Mod_Staff()
{
    this->Load_Staff();
    if (m_Staffnum == 0)
    {
        std::cout << "文件不存在" << std::endl;
    }
    else
    {
        std::cout << "要修改的员工号：" << std::endl;
        int modnum = 0;
        std::cin >> modnum;
        auto it = std::find_if(m_staff.begin(), m_staff.end(), [modnum](const std::unique_ptr<Staff> &staff)
                               { return staff->getnumber() == modnum; });
        // it在这里已经索引到staff对象了，可以访问内部所有的信息
        if (it != m_staff.end())
        {

            int option = -1;
            std::cout << "请选择要修改的信息编号:\n";
            std::cout << "1. 编号\n";
            std::cout << "2. 姓名\n";
            std::cout << "3. 职位\n";
            std::cout << "0. 退出修改\n";
            std::cout << "请输入选项: ";
            std::cin >> option;
            switch (option)
            {
            case 1:
            {
                // 修改编号
                int newNumber;
                std::cout << "请输入新的编号: ";
                std::cin.ignore();
                std::cin >> newNumber;
                (*it)->setnumber(newNumber);
                // it 是一个指向 std::unique_ptr<Staff> 对象的迭代器。std::unique_ptr<Staff> 是一个智能指针，它指向 Staff 类型的对象。
                std::cout << "编号修改成功！\n";
                break;
            }
            case 2:
            {
                // 修改姓名
                std::string newName;
                std::cout << "请输入新的姓名: ";
                std::cin.ignore();
                std::getline(std::cin, newName);
                (*it)->setname(newName);
                std::cout << "姓名修改成功！\n";
                break;
            }
            case 3:
            {
                // 修改职位
                std::string newPosition;
                std::cout << "请输入新的职位: ";
                std::cin.ignore();
                std::getline(std::cin, newPosition);
                (*it)->setposition(newPosition);
                std::cout << "职位修改成功！\n";
                break;
            }
            case 0:
                std::cout << "退出修改。\n";
                break;
            default:
                std::cout << "无效的选项！\n";
                break;
            }

            // After modification, save the updated staff data to the file
            std::ofstream ofs(FILENAME, std::ios::trunc); // Overwrite the file
            if (!ofs)
            {
                std::cout << "无法打开文件！\n";
                return;
            }

            for (const auto &staff : m_staff)
            {
                ofs << staff->getnumber() << ","
                    << staff->getname() << ","
                    << staff->getposition() << ","
                    << "岗位职责： " << staff->get_job_description() << std::endl;
            }
            std::cout << "员工信息修改并保存成功！\n";
        }
        else
        {
            std::cout << "未找到编号为 " << modnum << " 的员工！\n";
        }
    }
}

void WorkManger::Find_Staff()
{
    this->Load_Staff();
    if (m_Staffnum == 0)
    {
        std::cout << "文件不存在" << std::endl;
    }

    std::cout << "请选择查找方式：" << std::endl;
    std::cout << "1. 按编号查找" << std::endl;
    std::cout << "2. 按姓名查找" << std::endl;
    std::cout << "0. 退出查找" << std::endl;
    int find;
    std::cin >> find;
    switch (find)
    {
    case 1:
    {
        std::cout << "请输入要查找的员工编号：" << std::endl;
        int searchNumber;
        std::cin.ignore();
        std::cin >> searchNumber;

        auto it = std::find_if(m_staff.begin(), m_staff.end(), [searchNumber](const std::unique_ptr<Staff> &staff)
                               { return staff->getnumber() == searchNumber; });

        if (it != m_staff.end())
        {
            std::cout << "找到员工：" << std::endl;
            std::cout << "职工号： " << (*it)->getnumber()
                      << " 职工姓名： " << (*it)->getname()
                      << " 部门编号： " << (*it)->getposition() << std::endl
                      << " 岗位职责： " << (*it)->get_job_description() << std::endl;
        }
        else
        {
            std::cout << "未找到编号为 " << searchNumber << " 的员工！" << std::endl;
        }
        break;
    }
    case 2:
    {
        std::cout << "请输入要查找的员工姓名：" << std::endl;
        std::string searchName;
        std::cin.ignore();
        std::cin >> searchName;

        auto it = std::find_if(m_staff.begin(), m_staff.end(), [searchName](const std::unique_ptr<Staff> &staff)
                               { return staff->getname() == searchName; });

        if (it != m_staff.end())
        {
            std::cout << "找到员工：" << std::endl;
            std::cout << "职工号： " << (*it)->getnumber()
                      << " 职工姓名： " << (*it)->getname()
                      << " 部门编号： " << (*it)->getposition() << std::endl
                      << " 岗位职责： " << (*it)->get_job_description() << std::endl;
        }
        else
        {
            std::cout << "未找到姓名为 " << searchName << " 的员工！" << std::endl;
        }
        break;
    }
    case 0:
        std::cout << "退出修改。\n";
        break;
    default:
        std::cout << "无效的选项！\n";
        break;
    }
}

void WorkManger::Sort_Staff()
{
    this->Load_Staff();
    if (m_Staffnum == 0)
    {
        std::cout << "当前没有员工信息，请先添加员工！" << std::endl;
        return;
    }

    std::cout << "请选择排序方式：" << std::endl;
    std::cout << "1. 升序排序（从小到大）" << std::endl;
    std::cout << "2. 降序排序（从大到小）" << std::endl;
    int sort;
    std::cin >> sort;

    switch (sort)
    {
    case 1:
    {
        std::sort(m_staff.begin(), m_staff.end(), [](const std::unique_ptr<Staff> &a, const std::unique_ptr<Staff> &b)
                  { return a->getnumber() < b->getnumber(); });
        std::cout << "员工已按照编号升序排序！" << std::endl;
        break;
    }
    case 2:
    {
        std::sort(m_staff.begin(), m_staff.end(), [](const std::unique_ptr<Staff> &a, const std::unique_ptr<Staff> &b)
                  { return a->getnumber() > b->getnumber(); });
        std::cout << "员工已按照编号升序排序！" << std::endl;
        break;
    }
    }

    std::ofstream ofs;
    ofs.open(FILENAME, std::ios::in);

    // 可选：显示排序后的员工信息
    for (int i = 0; i < m_staff.size(); ++i)
    {
        ofs << m_staff[i]->getnumber() << ","
            << m_staff[i]->getname() << ","
            << m_staff[i]->getposition() << ","
            << " 岗位职责： " << m_staff[i]->get_job_description() << std::endl;
    }
}

void WorkManger::Clear_File()
{
    std::ofstream ofs(FILENAME, std::ios::trunc); // 打开文件并清空内容
    if (!ofs)
    {
        std::cout << "无法打开文件！" << std::endl;
        return;
    }

    // 清空文件后，更新数据结构
    m_staff.clear();
    m_Staffnum = 0;
    isEmpty = true;

    std::cout << "文件已清空！" << std::endl;
}

// void WorkManger::test01()
// {
//     std::unique_ptr<Staff> staff1 = std::make_unique<Worker>(21, "职位1", "张三");
//     staff1->showInfo();
//     staff1->work();
// }

// void WorkManger::test02()
// {
//     std::unique_ptr<Staff> staff2 = std::make_unique<Manger>(25, "职位2", "李四");
//     staff2->showInfo();
//     staff2->work();
// }