#include "Arduino.h"

#include "md_l298n.hpp"

#include "utility.hpp"

static const int MOTOR_STOP_SPEED = 0;
static const int MOTOR_START_SPEED = 80;
static const int MOTOR_CRUISE_SPEED = 160;
static const int MOTOR_ROTATION_SPEED = 120;
static const int MOTOR_ACCELERATION_DELAY = 2;

md_l298n::md_l298n(const int a_enable, const int a_forward, const int a_backward, const int b_enable, const int b_forward, const int b_backward)
  : motor_a_enable_pin(a_enable),
    motor_a_forward_pin(a_forward),
    motor_a_backward_pin(a_backward),
    motor_b_enable_pin(b_enable),
    motor_b_forward_pin(b_forward),
    motor_b_backward_pin(b_backward) {
  pinMode(motor_a_enable_pin, OUTPUT);
  pinMode(motor_a_forward_pin, OUTPUT);
  pinMode(motor_a_backward_pin, OUTPUT);

  pinMode(motor_b_enable_pin, OUTPUT);
  pinMode(motor_b_forward_pin, OUTPUT);
  pinMode(motor_b_backward_pin, OUTPUT);

  stop();
}

Result md_l298n::forward() {
  digitalWrite(motor_a_forward_pin, HIGH);
  digitalWrite(motor_a_backward_pin, LOW);
  digitalWrite(motor_b_forward_pin, HIGH);
  digitalWrite(motor_b_backward_pin, LOW);

  for (int speed = MOTOR_START_SPEED; speed <= MOTOR_CRUISE_SPEED; ++speed) {
    analogWrite(motor_a_enable_pin, speed);
    analogWrite(motor_b_enable_pin, speed);
    delay(MOTOR_ACCELERATION_DELAY);
  }

  return Result::SUCCESS;
}
Result md_l298n::backward() {
  digitalWrite(motor_a_forward_pin, LOW);
  digitalWrite(motor_a_backward_pin, HIGH);
  digitalWrite(motor_b_forward_pin, LOW);
  digitalWrite(motor_b_backward_pin, HIGH);

  for (int speed = MOTOR_START_SPEED; speed <= MOTOR_CRUISE_SPEED; ++speed) {
    analogWrite(motor_a_enable_pin, speed);
    analogWrite(motor_b_enable_pin, speed);
    delay(MOTOR_ACCELERATION_DELAY);
  }

  return Result::SUCCESS;
}

Result md_l298n::right() {
  digitalWrite(motor_a_forward_pin, LOW);
  digitalWrite(motor_a_backward_pin, HIGH);
  digitalWrite(motor_b_forward_pin, HIGH);
  digitalWrite(motor_b_backward_pin, LOW);

  for (int speed = MOTOR_START_SPEED; speed <= MOTOR_ROTATION_SPEED; ++speed) {
    analogWrite(motor_a_enable_pin, speed);
    analogWrite(motor_b_enable_pin, speed);
    delay(MOTOR_ACCELERATION_DELAY);
  }

  return Result::SUCCESS;
}

Result md_l298n::left() {
  digitalWrite(motor_a_forward_pin, HIGH);
  digitalWrite(motor_a_backward_pin, LOW);
  digitalWrite(motor_b_forward_pin, LOW);
  digitalWrite(motor_b_backward_pin, HIGH);

  for (int speed = MOTOR_START_SPEED; speed <= MOTOR_ROTATION_SPEED; ++speed) {
    analogWrite(motor_a_enable_pin, speed);
    analogWrite(motor_b_enable_pin, speed);
    delay(MOTOR_ACCELERATION_DELAY);
  }

  return Result::SUCCESS;
}

Result md_l298n::stop() {
  digitalWrite(motor_a_forward_pin, LOW);
  digitalWrite(motor_a_backward_pin, LOW);
  digitalWrite(motor_b_forward_pin, LOW);
  digitalWrite(motor_b_backward_pin, LOW);

  analogWrite(motor_a_enable_pin, MOTOR_STOP_SPEED);
  analogWrite(motor_b_enable_pin, MOTOR_STOP_SPEED);

  return Result::SUCCESS;
}

Result md_l298n::test() {
  stop();
  right();
  delay(2000); //points right
  left();
  delay(4000); //points left
  right();
  delay(2000); //points middle
  forward();
  delay(1000);
  backward();
  delay(1000);
  stop();

  return Result::SUCCESS;
}
