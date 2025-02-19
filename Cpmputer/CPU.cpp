#include "cpu.h"

CPU::~CPU() {
  // 析构函数的实现
  std::cout << "CPU is being destroyed..." << std::endl;
}

void IntelCPU::operate() const {
  std::cout << "Intel CPU is calculating..." << std::endl;
}

void LenovoCPU::operate() const {
  std::cout << "Lenovo CPU is calculating..." << std::endl;
}
