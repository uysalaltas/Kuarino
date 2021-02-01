#ifndef gcode_h
#define gcode_h

class gcode {
  private:
    void motor_gcode(char motor_code[], int motor_spd);
    void g_commands();
  public:
    gcode();
    // void split_gcode(char command[], char axes_dir[], char axes_speed[], char g_array[]);
    void g_control(char g_array[]);
};

#endif
