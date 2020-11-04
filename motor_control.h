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

#define E0_STEP_PIN        26
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      24
#ifndef E0_CS_PIN
  #define E0_CS_PIN        42
#endif

#define E1_STEP_PIN        36
#define E1_DIR_PIN         34
#define E1_ENABLE_PIN      30
#ifndef E1_CS_PIN
  #define E1_CS_PIN        44
#endif

#define V1_ENABLE_PIN      6
#define V1_IN_1            4
#define V1_IN_2            5

class motor_control {
  private:
    int motor_speed(int speed);
    int distance_to_degree(float mm_dist);
  public:
    motor_control();
    void init();
    void run_motors(char motor_axis[], float mm[], bool motor_direction[], int motor_spd);
    void home_all();
    void extruder_motor(float mm[]);
    void disable_all_motors();
    void run_vacuum();
    void stop_vacuum();
//    void control_x(float mm, char motor_direction = '+');
//    void control_y(float mm, char motor_direction = '+');
//    void motor_on(char motor_axis, float mm, char motor_direction='+');
};

#endif
