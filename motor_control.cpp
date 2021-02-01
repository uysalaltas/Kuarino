#include "motor_control.h"
#include "end_stop.h"
#include "Arduino.h"
#include "pins.h"
#include "utils.h"


utils tools1;
const int stepsPerRevolution = 200;
float stepPerAngle = 1.8;
end_stop limit_switch;

motor_control::motor_control(){
  init();
}

void motor_control::init(){

}

void motor_control::run_motors(char motor_axis[], float mm[], bool motor_direction[], int motor_spd){

  //--- Value Initializing ---
  int index_x = 0;
  int index_y = 0;
  int index_z = 0;

  int bool_x = false;
  int bool_y = false;
  int bool_z = false;

  for(int i = 0; i < 3; i++){
    if(motor_axis[i] == 'X'){
      index_x = i;
      bool_x = true;
    } 
    else if(motor_axis[i] == 'Y'){
      index_y = i;
      bool_y = true;
    }    
    else if(motor_axis[i] == 'Z'){
      index_z = i;
      bool_z = true;
    }
  }

  Serial.print("Motor Axis: ");
  Serial.println(motor_axis);

  float num_step = 0;
  for(int i = 0; i < 3; i++){
    if(num_step < mm[i]){
      num_step = mm[i];
    }
  }
  Serial.print("Distance: ");
  Serial.println(num_step);

  num_step = tools1.distance_to_degree(num_step);

  int num_step_x = tools1.distance_to_degree(mm[index_x]);
  bool dir_x = motor_direction[index_x];
  if(dir_x == false){
    digitalWrite(X_DIR_PIN, LOW);
  } else {
    digitalWrite(X_DIR_PIN, HIGH);
  }

  int num_step_y = tools1.distance_to_degree(mm[index_y]);
  bool dir_y = motor_direction[index_y];
  if(dir_y == false){
    digitalWrite(Y_DIR_PIN, LOW);
  } else {
    digitalWrite(Y_DIR_PIN, HIGH);
  }
  
  int num_step_z = tools1.distance_to_degree(mm[index_z]);
  bool dir_z = motor_direction[index_z];
  if(dir_z == false){
    digitalWrite(Z_DIR_PIN, LOW);
  } else {
    digitalWrite(Z_DIR_PIN, HIGH);
  }

  //--- Motor movement ---
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  // digitalWrite(Z_ENABLE_PIN, LOW);

  Serial.print("Speed: ");
  Serial.println(motor_spd);

  int motor_speed_val = tools1.motor_speed(motor_spd);
  
  for(int val = 0; val < num_step; val++)
  {
    // Motor X
    if(val < num_step_x && bool_x){
      // Serial.println("X");
      digitalWrite(X_STEP_PIN, HIGH);
      delayMicroseconds(motor_speed_val / 2);
      digitalWrite(X_STEP_PIN, LOW);
      delayMicroseconds(motor_speed_val / 2);
    }

    // Motor Y
    if(val < num_step_y && bool_y){
      // Serial.println("Y");
      digitalWrite(Y_STEP_PIN, HIGH);
      delayMicroseconds(motor_speed_val / 2);
      digitalWrite(Y_STEP_PIN, LOW);
      delayMicroseconds(motor_speed_val / 2);
    }

    // Motor Z
    if(val < num_step_z && bool_z){
      // Serial.println("Z");
      digitalWrite(Z_STEP_PIN, HIGH);
      delayMicroseconds(motor_speed_val / 2);
      digitalWrite(Z_STEP_PIN, LOW);
      delayMicroseconds(motor_speed_val / 2);
    }
  }

  Serial.println("Done!");
}

void motor_control::home_all(){
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(E1_ENABLE_PIN, LOW);

  digitalWrite(X_DIR_PIN, LOW);
  for(;;){
    int stop_val_x = limit_switch.stop_x();
    if(stop_val_x == 0){
      break;
    }
    digitalWrite(X_STEP_PIN, HIGH);
    delayMicroseconds(100);
    digitalWrite(X_STEP_PIN, LOW);
    delayMicroseconds(100);
  }

  digitalWrite(Y_DIR_PIN, LOW);
  for(;;){
    int stop_val_y = limit_switch.stop_y();
    if(stop_val_y == 0){
      break;
    }
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(100);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(100);
  }

  digitalWrite(E1_DIR_PIN, HIGH);
  for(;;){
    int stop_val_z = limit_switch.stop_z();
    if(stop_val_z == 0){
      break;
    }
    digitalWrite(E1_STEP_PIN, HIGH);
    delayMicroseconds(200);
    digitalWrite(E1_STEP_PIN, LOW);
    delayMicroseconds(200);
  }

  char home_motor_codes[3] = {'X', 'Y'};
  float home_motor_mm[3] = {100, 100};
  bool home_motor_dir[2] = {true, true};
  int home_motor_spd = 1000;

  run_motors(home_motor_codes, home_motor_mm, home_motor_dir, home_motor_spd);

  Serial.println("---END---");
}

void motor_control::disable_all_motors(){
  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Y_ENABLE_PIN, HIGH);
  digitalWrite(E1_ENABLE_PIN, HIGH);
  Serial.println("---END---");
}
