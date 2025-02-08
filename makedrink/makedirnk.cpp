#include <iostream>
#include <string>
#include <random> // 随机数库核心头文件
#include <chrono> // 用于获取时间戳(无法正确生成随机数的时候)
#include <memory>

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

    virtual void FillCup()
    {
        std::cout << "Filling cup...\n\n";
    }
    virtual std::string getMaterialName() const = 0;
    virtual int getRequiredGrams() const = 0;
};

class Tea : public AbstractMakeDrink
{
protected:
    std::string getMaterialName() const override { return "tea"; }
    int getRequiredGrams() const override { return 30; }
};

class Coffee : public AbstractMakeDrink
{
protected:
    std::string getMaterialName() const override { return "tea"; }
    int getRequiredGrams() const override { return 30; }
};
void prepareDrink(std::unique_ptr<AbstractMakeDrink> drink)
{
    drink->MakeDrink();
}

int main()
{
    prepareDrink(std::make_unique<Coffee>());
    prepareDrink(std::make_unique<Tea>());
    return 0;
}