#include "Hardware.h"

// 实现纯虚析构函数
HardWare::~HardWare() {
  std::cout << "HardWare is being destroyed..." << std::endl;
}

// 如果需要实现其他成员函数，按需添加
void HardWare::operate() const {}
