#include <iostream>
#include <string>
#include <random> // 随机数库核心头文件
#include <chrono> // 用于获取时间戳(无法正确生成随机数的时候)
#include <memory> //引入 智能指针 和 内存管理 相关的功能

int RandomInt(int min, int max)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count(); //时间戳
    /*mingw版本太低可能无法实现*/
    // static std::random_device rd; // std::random_device：用于生成真随机数种子
    static std::mt19937 engine(seed);
    /*std::mt19937：高性能随机数引擎（梅森旋转算法）,其中mt代表“Mersenne Twister”，19937表示该算法的周期长度为2^19937-1
    engine 是一个 随机数引擎对象，具体类型是 std::mt19937（梅森旋转算法的32位实现）。
    它的核心作用是通过数学算法生成伪随机数序列。你可以把它想象成一个“随机数工厂”，负责生产原始的随机数。*/

    std::uniform_int_distribution<int> dist(min, max); // uniform_int_distribution：整数均匀分布
    return dist(engine);                               /*通过分布对象将引擎生成的原始随机数转换为符合要求的数值。
                                                      dist：一个分布对象（如 uniform_int_distribution<int>），负责将原始随机数映射到指定范围内。*/
}
// make drink
//当每个子函数都需要重写内容可以写纯虚函数virtual void MakeDrink()=0；此时子函数必须重写
class AbstractMakeDrink
{
public:
    virtual ~AbstractMakeDrink() = default;
    virtual void MakeDrink()
    {
        Boiling();
        Brewing();
        FillCup();
    }
    } //先写好制作流程
protected:
    virtual void Boiling()
    {
        int temp = RandomInt(26, 100);
        std::cout << "Initial water's temperature is " << temp << std::endl;
        std::cout << "Heating...... " << std::endl;
        while (temp <= 100)
        {
            temp++;
        }
        std::cout << "Water is done , terminal temperature is " << temp << "°C" << std::endl;
    }
    virtual void Brewing()
    {
        std::cout << "Adding " << getRequiredGrams() << "g " << getMaterialName() << "\n";
        int amount;
        std::cout << "Enter" << getMaterialName() << "amount (minimum" << getRequiredGrams() << "g): " << std::endl;
        std::cin >> amount;
        amount = getRequiredGrams();
        std::cout << "Using " << amount << "g " << getMaterialName() << "\n";
    }
    } //抽象的虚函数

    virtual void FillCup()
    {
        std::cout << "Filling cup...\n\n";
    }
    virtual std::string getMaterialName() const = 0;
    virtual int getRequiredGrams() const = 0;
};


class Tea : public AbstractMakeDrink //多态
{
protected:
    std::string getMaterialName() const override { return "tea"; }
    int getRequiredGrams() const override { return 30; }
}; // Brewing不是纯虚函数，所以只需要重写 getMaterialName()和getRequiredGrams()
// override 是 C++11 引入的一个关键字，用来标明该成员函数是 重写（override） 基类的虚函数。
class Coffee : public AbstractMakeDrink
{
protected:
    std::string getMaterialName() const override { return "tea"; }
    int getRequiredGrams() const override { return 30; }
};

void prepareDrink(std::unique_ptr<AbstractMakeDrink> drink) /*memory库中提供的智能指针
 具有所有权和自动销毁功能*/
{
    
    drink->MakeDrink(); //指针指向MakeDrink实现的功能
}

int main()
{
  
    prepareDrink(std::make_unique<Coffee>()); /*创建一个 std::unique_ptr，并且自动初始化一个指定类型的对象
     创建了一个指向 Coffee 类型的智能指针 std::unique_ptr<Coffee>*/
    prepareDrink(std::make_unique<Tea>());
    return 0;
}
