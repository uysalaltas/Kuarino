
#include "gcode.h"
#include "motor_control.h"
#include "Arduino.h"
#include "string.h"

motor_control motor;
char * codes [3];
char * g_code;
char * motor_axis;
char distance_mm;
char motor_dir;

char motor_codes[] = "XYZ";
char numbers[] = "0123456789";

gcode::gcode(){
  
}

// G1 X5Y5 F250
void gcode::g_control(char g_array[]){
  split_gcode(g_array);

  motor_axis = codes[1];
  motor_gcode(motor_axis);
}

void gcode::split_gcode(char gcode_array[]){
  int code_index = 0;
  char * ptr = strtok(gcode_array, " ");

  while(ptr != NULL)
  {
    codes[code_index] = ptr;
    ptr = strtok(NULL, " ");
    code_index += 1;
  }
}

void gcode::motor_gcode(char motor_code[]){
  char * pch;
  pch = strpbrk (motor_code, motor_codes);
  while (pch != NULL)
  {
    int index = pch-motor_code + 1;
    int index_int = 0;
    
    char dir = '+';
    if(motor_code[index] == '-'){
      dir = '-';
      index += 1;
    }
    
    char * pch_num;
    pch_num = strchr(numbers, motor_code[index]);

    char motor_distance [4];
    while(pch_num != NULL)
    {
      motor_distance[index_int] = *pch_num;
      index += 1;
      index_int += 1;
      pch_num = strchr(numbers, motor_code[index]);
    }

    int distance = atoi(motor_distance);
    motor.motorOn(*pch, distance, dir);
    pch = strpbrk (pch+1,motor_codes);
  }
}
