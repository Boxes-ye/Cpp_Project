#include <iostream>
#include <string>
#include <memory>
class Animal
{
public:
    Animal()
    {
        std::cout << "Animal的构造函数调用" << std::endl;
    }
    virtual void speak() = 0; //纯虚数，等子函数重写
    virtual ~Animal() = 0;
};
Animal ::~Animal()
{
    std::cout << "Animal 的析构函数调用" << std::endl;
}
class Cat : public Animal
{
private:
    std::unique_ptr<std::string> m_Name; //定义一个智能指针，类型位string，名字为m_Name

public:
    Cat(const std::string &name) //利用引用不用拷贝副本
    {
        std::cout << "Cat 构造函数调用" << std::endl;
        m_Name = std::make_unique<std::string>(name); //将m_Name初始化为一个string类型，name对象，并返回unique_ptr智能指针
    }
    virtual void speak()
    {
        std::cout << *m_Name << "小猫在说话" << std::endl;
    }
    ~Cat()
    {
        std::cout << "Cat的析构函数调用" << std::endl;
    }
};
void test01()
{
    std::unique_ptr<Animal> animal = std::make_unique<Cat>("Tom"); //将Cat类型赋予Animal基类指针，可以统一管理
    animal->speak();
}
int main()
{
    test01();
}