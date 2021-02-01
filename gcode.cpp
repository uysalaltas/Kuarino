#include "gcode.h"
#include "motor_control.h"
#include "extruder.h"
#include "string.h"
#include "utils.h"
// #include "utils.cpp"

motor_control motor;
exturder ext;
utils tools_gcode;

#define GCODE_MAX_LEN 3
#define AXIS_MAX_LEN 12
#define SPEED_MAX_LEN 4

char * codes [3];
char g_code [GCODE_MAX_LEN];
char motor_axis [AXIS_MAX_LEN];
char motor_speed [SPEED_MAX_LEN];
// char distance_mm;
// char motor_dir;

bool selanoidValve = false;
int extruder_distance;
int extruder_motor_speed;

gcode::gcode(){

}

void gcode::g_control(char g_array[]){
  tools_gcode.split_gcode(g_code, motor_axis, motor_speed, g_array);
  g_commands();
}

void gcode::g_commands(){
  char first_val = g_code[0];
  char * pch = strtok(g_code, "GM");
  int command_code = atoi(pch); 
  switch(first_val) {
    case 'G':
      switch (command_code){
        case 1:
          if (motor_speed[0] != NULL)
          {
            int speed_of_motor = atoi(motor_speed);
            motor_gcode(motor_axis, speed_of_motor);
          }
          else
          {
            Serial.println("Null Here");
            motor_gcode(motor_axis, 500);
          }
          break;
        case 28:
          motor.home_all();
          break;
      }
      break;
    case 'M':
      switch (command_code){
        case 3:
          extruder_motor_speed = 2000;
          extruder_distance = 350;
          if (motor_speed[0] != NULL)
          {
            extruder_motor_speed = atoi(motor_speed);
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
          if (motor_speed[0] != NULL)
          {
            extruder_motor_speed = atoi(motor_speed);
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
          if (motor_speed[0] != NULL)
          {
            extruder_motor_speed = atoi(motor_speed);
            extruder_distance = atoi(motor_axis);
          }
          ext.extruder_in(extruder_distance, extruder_motor_speed);
          Serial.println("---END---");
          break;
        case 6:
          extruder_motor_speed = 2000;
          extruder_distance = 350;
          if (motor_speed[0] != NULL)
          {
            extruder_motor_speed = atoi(motor_speed);
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
          if (selanoidValve == false)
          {
            ext.selenoid_on();
            selanoidValve = true;
          }
          else
          {
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
    Serial.println(x);
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
  motor.run_motors(motor_axis, motor_axis_dist, motor_axis_dir, motor_spd);
  Serial.println("---END---");
}
