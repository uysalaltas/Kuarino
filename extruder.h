#include "Arduino.h"

#ifndef exturder_h
#define exturder_h

class exturder {
  public:
    exturder();
    void init();
    void selenoid_on();
    void selenoid_off();
    void vacuum_control();
    void extruder_in(int mm, int motor_speed_val);
    void extruder_out(int mm, int motor_speed_val);
};

#endif