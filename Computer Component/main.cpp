#include <iostream>
#include <memory>

#include "CPU.h"
#include "Hardware.h"

class VideoCard : public HardWare {
 public:
  virtual void operate() const override = 0;
  virtual ~VideoCard() = 0;
};

VideoCard::~VideoCard() {
  // 析构函数的实现
  std::cout << "VideoCard is being destroyed..." << std::endl;
}

class LenovoVideoCard : public VideoCard {
 public:
  void operate() const override {
    std::cout << "LenovoVideoCard is displaying..." << std::endl;
  }
};

class IntelVideoCard : public VideoCard {
 public:
  void operate() const override {
    std::cout << "IntelVideoCard is displaying..." << std::endl;
  }
};

class Memory : public HardWare {
 public:
  virtual void operate() const override = 0;
  virtual ~Memory() = 0;
};

Memory::~Memory() {
  // 析构函数的实现
  std::cout << "Memory is being destroyed..." << std::endl;
}

class IntelMemory : public Memory {
 public:
  void operate() const override {
    std::cout << "IntelMemory is remenber..." << std::endl;
  }
};
class LenovoMemory : public Memory {
 public:
  void operate() const override {
    std::cout << "LenovoMemory is remenber..." << std::endl;
  }
};

class Computer {
 private:
  std::unique_ptr<CPU> m_cpu;
  std::unique_ptr<VideoCard> m_vc;
  std::unique_ptr<Memory> m_me;

 public:
  Computer(std::unique_ptr<CPU> cpu, std::unique_ptr<VideoCard> vc,
           std::unique_ptr<Memory> me)
      : m_cpu(std::move(cpu)), m_vc(std::move(vc)), m_me(std::move(me)) {}
  void work() {
    m_cpu->operate();
    m_vc->operate();
    m_me->operate();
  }
};

void test01() {
  std::unique_ptr<CPU> IntelCpu = std::make_unique<IntelCPU>();
  std::unique_ptr<VideoCard> IntelVc = std::make_unique<IntelVideoCard>();
  std::unique_ptr<Memory> IntelMe = std::make_unique<IntelMemory>();
  Computer IntelComputer(std::move(IntelCpu), std::move(IntelVc),
                         std::move(IntelMe));
  std::cout << "Intel Computer :";
  IntelComputer.work();
}
void test02() {
  std::unique_ptr<CPU> LenovoCpu = std::make_unique<LenovoCPU>();
  std::unique_ptr<VideoCard> LenovoVc = std::make_unique<LenovoVideoCard>();
  std::unique_ptr<Memory> LenovoMe = std::make_unique<LenovoMemory>();
  Computer LenovoComputer(std::move(LenovoCpu), std::move(LenovoVc),
                          std::move(LenovoMe));
  std::cout << "Lenovo Computer :";
  LenovoComputer.work();
}
int main() {
  test01();
  test02();
}
