#include "gcode.h"
#include "motor_control.h"
#include "extruder.h"
#include "Arduino.h"
#include "string.h"

motor_control motor;
exturder ext;

char * codes [3];
char * g_code;
char * motor_axis;
char * motor_speed;
// char distance_mm;
// char motor_dir;

char motor_codes[3] = {'X', 'Y', 'Z'};
char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

bool selanoidValve = false;
int extruder_distance;
int extruder_motor_speed;

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
  codes[2] = NULL;
  int code_index = 0;
  char * ptr = strtok(gcode_array, " ");
  while(ptr != NULL)
  {
    Serial.println(ptr);
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
            motor_gcode(motor_axis, speed_of_motor);
          }
          else
          {
            motor_gcode(motor_axis, 500);
          }
          break;
        case 28:
          Serial.println("Home all");
          motor.home_all();
          break;
      }
      break;
    case 'M':
      Serial.println("Its M");
      switch (command_code){
        case 3:
          extruder_motor_speed = 2000;
          extruder_distance = 350;

          if (motor_speed_val != NULL)
          {
            extruder_motor_speed = atoi(motor_speed_val);
            extruder_distance = atoi(motor_axis);
          }
          ext.selenoid_off();
          ext.extruder_in(extruder_distance, extruder_motor_speed);
          delay(1000);
          ext.extruder_out(extruder_distance, extruder_motor_speed);
          break;
        case 4:
          extruder_motor_speed = 2000;
          extruder_distance = 350;

          if (motor_speed_val != NULL)
          {
            extruder_motor_speed = atoi(motor_speed_val);
            extruder_distance = atoi(motor_axis);
          }
          ext.extruder_in(extruder_distance, extruder_motor_speed);
          delay(100);
          ext.selenoid_on();
          delay(100);
          ext.extruder_out(extruder_distance, extruder_motor_speed);
          break;
        case 5:
          extruder_motor_speed = 2000;
          extruder_distance = 350;

          if (motor_speed_val != NULL)
          {
            extruder_motor_speed = atoi(motor_speed_val);
            extruder_distance = atoi(motor_axis);
          }
          ext.extruder_in(extruder_distance, extruder_motor_speed);
          Serial.println("---END---");
          break;
        
        case 6:
          extruder_motor_speed = 2000;
          extruder_distance = 350;

          if (motor_speed_val != NULL)
          {
            extruder_motor_speed = atoi(motor_speed_val);
            extruder_distance = atoi(motor_axis);
          }
          ext.extruder_out(extruder_distance, extruder_motor_speed);
          break;

        case 18:
          motor.disable_all_motors();
          break;
        case 20:
          ext.vacuum_control();
          break;
        case 26:
          Serial.println("Vacuum valve settings...");
          if (selanoidValve == false)
          {
            Serial.println("Vacuum Valve On!");
            ext.selenoid_on();
            selanoidValve = true;
          }
          else
          {
            Serial.println("Vacuum Valve Off!");
            ext.selenoid_off();
            selanoidValve = false;
          }  
          break;
      }
      break;
  }
}

void gcode::motor_gcode(char motor_code[], int motor_spd){
  Serial.println("---START---");
  char motor_axis [3] = {' ',' ',' '};
  bool motor_axis_dir [3];
  float motor_axis_dist [4] = {};
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

      motor_axis_dist[index_size] = distance;
      index_size += 1;
    } 
    else
    {
      Serial.println("NULL");
    }
    
  }
  Serial.println(motor_axis);
  motor.run_motors(motor_axis, motor_axis_dist, motor_axis_dir, motor_spd);
  Serial.println("---END---");
}
