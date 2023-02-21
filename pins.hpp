#ifndef PINS_HPP
#define PINS_HPP

enum PIN {
  // reserved BT_RX = 0,  //Arduino Rx, BT Tx
  // reserved BT_TX = 1,  //Arduino Tx, BT Rx
  MD_ABWD = 2,
  MD_BFWD = 3,
  MD_BBWD = 4,
  MD_ENA = 5,  //PWM
  MD_ENB = 6,  //PWM
  MD_AFWD = 7,
};

#endif