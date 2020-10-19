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

  g_code = codes[0];
  motor_axis = codes[1];  
  g_commands(g_code);
 
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

void gcode::g_commands(char g_command[]){
  char first_val = g_command[0];
  char * pch = strtok(g_command, "GM");
  int command_code = atoi(pch);
  
  switch(first_val) {
    case 'G':
      Serial.println("Its G");
      switch (command_code){
        case 1:
          Serial.println("Move motors linearly");
          motor_gcode(motor_axis);
          break;
        case 28:
          Serial.println("Home all");
          motor.home_all();
      }
      break;
    case 'M':
      Serial.println("Its M");
      break;
  }
}

void gcode::motor_gcode(char motor_code[]){
  char * pch;
  pch = strpbrk (motor_code, motor_codes);
  
  char motor_axis [3];
  bool motor_axis_dir [3];
  float motor_axis_dist [3];
  int index_size = 0;
  
  while (pch != NULL)
  {    
    int index = pch-motor_code + 1;
    int index_int = 0;
        
    motor_axis[index_size] = *pch;
    
    bool dir = true;
    if(motor_code[index] == '-'){
      dir = false;
      index += 1;
    }
    motor_axis_dir[index_size] = dir;
    
    char * pch_num;
    pch_num = strchr(numbers, motor_code[index]);

    char motor_distance [4] = "    ";
    while(pch_num != NULL)
    {
      motor_distance[index_int] = *pch_num;
      
      index += 1;
      index_int += 1;
      pch_num = strchr(numbers, motor_code[index]);
    }
    
    int distance = atoi(motor_distance);
    motor_axis_dist[index_size] = distance;
    index_size += 1;
    pch = strpbrk (pch+1,motor_codes);
  }
  motor.run_motors(motor_axis, motor_axis_dist, motor_axis_dir);
}
