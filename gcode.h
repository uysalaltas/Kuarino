#include "Arduino.h"

#ifndef gcode_h
#define gcode_h

class gcode {
  private:
    void split_gcode(char g_array[]);
    void motor_gcode(char motor_code[]);
  public:
    gcode();
    void g_control(char g_array[]);
};

#endif
