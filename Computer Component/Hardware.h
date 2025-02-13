#ifndef HARDWARE_H
#define HARDWARE_H
#include <iostream>

class HardWare {
 public:
  virtual void operate() const;
  virtual ~HardWare() = 0;
};

#endif
