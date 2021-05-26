#include "Arduino.h"

#ifndef motor_control_h
#define motor_control_h

#define ACCEL_SLOPE     16
#define DECEL_SLOPE     16
#define HALF_POINT_C1   0.25
#define HALF_POINT_C2   4.75
#define ACCEL_CURVE     0.05


class motor_control {
  public:
    motor_control();
    void init();
    void run_motors(char motor_axis[], float mm[], bool motor_direction[], int motor_spd);
    void cartridge_motor(int mm, int motor_spd);
    void home_all();
    void disable_all_motors();
};

#endif
