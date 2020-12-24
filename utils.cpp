#include "Arduino.h"
#include "utils.h"


utils::utils(){
  init();
}

void utils::init(){

}

int utils::motor_speed(int speed_control){
  int motor_speed_val = 1000000 / (speed_control * 8);
  Serial.print("Motor Speed (mm/sn): ");
  Serial.println(motor_speed_val);
  return motor_speed_val;
}

int utils::distance_to_degree(float mm_dist){
  float distance_to_degree = mm_dist * 0.9f;
  int degree_result = distance_to_degree / 1.8f * 16;
  return degree_result;
}