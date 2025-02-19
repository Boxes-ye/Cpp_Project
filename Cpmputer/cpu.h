#pragma once
#ifndef CPU_H
#define CPU_H

#include "Hardware.h"

class CPU : public HardWare {
 public:
  virtual void operate() const override = 0;
  virtual ~CPU() = 0;
};

class IntelCPU : public CPU {
 public:
  void operate() const override;
};

class LenovoCPU : public CPU {
 public:
  void operate() const override;
};

#endif