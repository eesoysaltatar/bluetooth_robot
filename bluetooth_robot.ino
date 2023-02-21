/*
  TODO-1: Check return values for those who makes sense.
*/
#include "motor_driver.hpp"
#include "md_l298n.hpp"

#include "utility.hpp"
#include "pins.hpp"

static const int RECEIVE_DELAY = 3;
static MotorDriver* motor_driver = nullptr;

void setup() {
  //create motor driver
  motor_driver = new md_l298n(MD_ENA, MD_AFWD, MD_ABWD, MD_ENB, MD_BFWD, MD_BBWD);
  motor_driver->test();

  //initialize BT communication
  Serial.begin(9600);
}

String receivedData;
void loop() {
  while (Serial.available()) {
    delay(RECEIVE_DELAY);
    receivedData += static_cast<char>(Serial.read());
  }

  if (receivedData.length() > 0) {
    if (receivedData == "FWD") {
      motor_driver->forward();
      receivedData="";
    } else if (receivedData == "BWD") {
      motor_driver->backward();
      receivedData="";
    } else if (receivedData == "LHS") {
      motor_driver->left();
      receivedData="";
    } else if (receivedData == "RHS") {
      motor_driver->right();
      receivedData="";
    } else if (receivedData == "STP") {
      motor_driver->stop();
      receivedData="";
    } else if (receivedData == "TST") {
      motor_driver->test();
      receivedData="";
    }else {
      motor_driver->stop();
      receivedData="";
    }
  } else {
    //not enough data
  }
}
