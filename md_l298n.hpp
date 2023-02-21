#ifndef MD_L298N_HPP
#define MD_L298N_HPP

#include "motor_driver.hpp"

#include "utility.hpp"

class md_l298n : public MotorDriver {
private:
  int motor_a_enable_pin;
  int motor_a_forward_pin;
  int motor_a_backward_pin;
  int motor_b_enable_pin;
  int motor_b_forward_pin;
  int motor_b_backward_pin;
public:
  md_l298n(const int, const int, const int, const int, const int, const int);
  Result forward();
  Result backward();
  Result right();
  Result left();
  Result stop();
  Result test();
};

#endif