#include "Arduino.h"

#ifndef motor_control_h
#define motor_control_h

class motor_control {
  public:
    motor_control();
    void init();
    void run_motors(char motor_axis[], float mm[], bool motor_direction[], int motor_spd);
    void home_all();
    void disable_all_motors();
};

#endif
