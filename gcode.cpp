#include "gcode.h"
#include "motor_control.h"
#include "Arduino.h"
#include "string.h"

motor_control motor;
char * codes [3];
char * g_code;
char * motor_axis;
char * motor_speed;
// char distance_mm;
// char motor_dir;

char motor_codes[3] = {'X', 'Y', 'Z'};
char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

gcode::gcode(){
  
}

void gcode::g_control(char g_array[]){
  split_gcode(g_array);

  g_code = codes[0];
  motor_axis = codes[1];
  motor_speed = codes[2];

  g_commands(g_code, motor_speed);
 
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

void gcode::g_commands(char g_command[], char motor_speed_val[]){
  char first_val = g_command[0];
  char * pch = strtok(g_command, "GM");
  int command_code = atoi(pch);
  
  switch(first_val) {
    case 'G':
      Serial.println("Its G");
      switch (command_code){
        case 1:
          Serial.println("Move motors linearly");
          if (motor_speed_val != NULL)
          {
            int speed_of_motor = atoi(motor_speed_val);
            motor.motor_speed(speed_of_motor);
          }
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
  Serial.println("---START---");
  char motor_axis [3];
  bool motor_axis_dir [3];
  float motor_axis_dist [4];
  int index_size = 0;

  char * pch_motor;
  for(char x:motor_codes){
    pch_motor = strchr (motor_code, x);
    if (pch_motor != NULL) 
    {
      int index = pch_motor-motor_code + 1; 
      int index_int = 0;
      motor_axis[index_size] = *pch_motor;
      
      bool dir = true;
      if(motor_code[index] == '-'){
        dir = false;
        index += 1;
      }
      Serial.print("Direction: ");
      Serial.println(dir);
      motor_axis_dir[index_size] = dir;

      int val = motor_code[index] - '0';
      char motor_distance [4] = "   ";

      while (val >= 0 && val <= 9)
      {
        motor_distance[index_int] = motor_code[index];
        index += 1;
        index_int += 1;
        val = motor_code[index] - '0';
      }
      
      int distance = atoi(motor_distance);
      Serial.print("Distance: ");
      Serial.println(distance);

      motor_axis_dist[index_size] = distance;
      index_size += 1;
    } 
    else
    {
      Serial.println("NULL");
    }
    
  }
  Serial.println(motor_axis);
  Serial.println("---END---");
  motor.run_motors(motor_axis, motor_axis_dist, motor_axis_dir);

  // char * pch;
  // pch = strstr (motor_code, motor_codes);
  
  // char motor_axis [3];
  // bool motor_axis_dir [3];
  // float motor_axis_dist [3];
  // int index_size = 0;
  
  // while (pch != NULL)
  // {
  //   int index = pch-motor_code + 1;
  //   int index_int = 0;
        
  //   motor_axis[index_size] = *pch;
    
  //   bool dir = true;
  //   if(motor_code[index] == '-'){
  //     dir = false;
  //     index += 1;
  //   }
  //   motor_axis_dir[index_size] = dir;
    
  //   char * pch_num;
  //   pch_num = strchr(numbers, motor_code[index]);

  //   char motor_distance [4] = "   ";
  //   while(pch_num != NULL)
  //   {
  //     motor_distance[index_int] = *pch_num;
      
  //     index += 1;
  //     index_int += 1;
  //     pch_num = strchr(numbers, motor_code[index]);
  //   }
    
  //   int distance = atoi(motor_distance);
  //   motor_axis_dist[index_size] = distance;
  //   index_size += 1;
  //   pch = strpbrk (pch+1,motor_codes);
  // }
}
