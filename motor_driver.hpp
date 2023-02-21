#ifndef MOTOR_DRIVER_HPP
#define MOTOR_DRIVER_HPP

#include "utility.hpp"

class MotorDriver {
public:
  virtual Result forward() = 0;
  virtual Result backward() = 0;
  virtual Result right() = 0;
  virtual Result left() = 0;
  virtual Result stop() = 0;
  virtual Result test() = 0;
};

#endif