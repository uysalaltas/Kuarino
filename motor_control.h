#include "Arduino.h"

#ifndef motor_control_h
#define motor_control_h

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#ifndef X_CS_PIN
  #define X_CS_PIN         53
#endif

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#ifndef Y_CS_PIN
  #define Y_CS_PIN         49
#endif

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#ifndef Z_CS_PIN
  #define Z_CS_PIN         40
#endif

class motor_control { 
  public:
    motor_control();
    void init();
    void run_motors(char motor_axis[], float mm[], bool motor_direction[]);
    void home_all();
    void motor_speed(int speed);
//    void control_x(float mm, char motor_direction = '+');
//    void control_y(float mm, char motor_direction = '+');
//    void motor_on(char motor_axis, float mm, char motor_direction='+');
};

#endif
