#include "motor_control.h"
#include "end_stop.h"
#include "Arduino.h"

const int stepsPerRevolution = 200;
float stepPerAngle = 1.8;
end_stop limit_switch;

motor_control::motor_control(){
  init();
}

void motor_control::init(){
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_CS_PIN, OUTPUT);

  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_CS_PIN, OUTPUT);

  pinMode(Z_ENABLE_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_CS_PIN, OUTPUT);

  pinMode(E0_ENABLE_PIN, OUTPUT);
  pinMode(E0_STEP_PIN, OUTPUT);
  pinMode(E0_DIR_PIN, OUTPUT);
  pinMode(E0_CS_PIN, OUTPUT);

  pinMode(E1_ENABLE_PIN, OUTPUT);
  pinMode(E1_STEP_PIN, OUTPUT);
  pinMode(E1_DIR_PIN, OUTPUT);
  pinMode(E1_CS_PIN, OUTPUT);

  pinMode(V1_ENABLE_PIN, OUTPUT);
  pinMode(V1_IN_1, OUTPUT);
  pinMode(V1_IN_2, OUTPUT);
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

  num_step = distance_to_degree(num_step);

  int num_step_x = distance_to_degree(mm[index_x]);
  bool dir_x = motor_direction[index_x];
  Serial.print("DirX: ");
  Serial.println(dir_x);

  if(dir_x == false){
    digitalWrite(X_DIR_PIN, LOW);
  } else {
    digitalWrite(X_DIR_PIN, HIGH);
  }

  int num_step_y = distance_to_degree(mm[index_y]);
  bool dir_y = motor_direction[index_y];
  Serial.print("DirY: ");
  Serial.println(dir_y);

  if(dir_y == false){
    digitalWrite(Y_DIR_PIN, LOW);
  } else {
    digitalWrite(Y_DIR_PIN, HIGH);
  }
  
  int num_step_z = distance_to_degree(mm[index_z]);
  bool dir_z = motor_direction[index_z];
  if(dir_z == false){
    digitalWrite(Z_DIR_PIN, LOW);
  } else {
    digitalWrite(Z_DIR_PIN, HIGH);
  }

  //--- Motor movement ---
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  // digitalWrite(E1_ENABLE_PIN, LOW);

  Serial.print("Speed: ");
  Serial.println(motor_spd);

  int motor_speed_val = motor_speed(motor_spd);
  
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
  Serial.println("Home All Started");
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(E1_ENABLE_PIN, LOW);

  digitalWrite(X_DIR_PIN, LOW);
  for(;;){
    int stop_val_x = limit_switch.stop_x();
    if(stop_val_x == 0){
      Serial.println("Loop Break.");
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
      Serial.println("Loop Break.");
      break;
    }
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(100);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(100);
  }

  digitalWrite(E1_DIR_PIN, LOW);
  for(;;){
    int stop_val_z = limit_switch.stop_z();
    if(stop_val_z == 0){
      Serial.println("Loop Break.");
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

void motor_control::extruder_motor(float mm[]){
  Serial.println("Extruder is moving!");
  Serial.println(mm[0]);
  int ext_dist = distance_to_degree(mm[0]);
  int motor_speed_ext = 50;
  digitalWrite(E1_DIR_PIN, HIGH);
  
  for (int val = 0; val < ext_dist; val++)
  {
    digitalWrite(E1_STEP_PIN, HIGH);
    delayMicroseconds(motor_speed_ext);
    digitalWrite(E1_STEP_PIN, LOW);
    delayMicroseconds(motor_speed_ext);
  }

  delay(500);
  digitalWrite(E1_DIR_PIN, LOW);
  
  for (int val = 0; val < ext_dist; val++)
  {
    digitalWrite(E1_STEP_PIN, HIGH);
    delayMicroseconds(motor_speed_ext);
    digitalWrite(E1_STEP_PIN, LOW);
    delayMicroseconds(motor_speed_ext);
  }
  Serial.println("Extruder is done!");
  Serial.println("---END---");
}

void motor_control::disable_all_motors(){
  Serial.println("All motors disabling...");
  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Y_ENABLE_PIN, HIGH);
  digitalWrite(E1_ENABLE_PIN, HIGH);
  Serial.println("All motors disabled!");
  Serial.println("---END---");
}

void motor_control::run_vacuum(){
  Serial.println("Vacuum Started...");
  bool control_vacuum = true;
  int counter = 0;

  analogWrite(V1_ENABLE_PIN, 255);
  digitalWrite(V1_IN_1, HIGH);
  digitalWrite(V1_IN_2, LOW);
}

void motor_control::stop_vacuum(){
  digitalWrite(V1_IN_1, LOW);
  digitalWrite(V1_IN_2, LOW);
  Serial.println("Vacuum Ended");
}

int motor_control::motor_speed(int speed_control){
  int motor_speed_val = 1000000 / (speed_control * 8);
  Serial.print("Motor Speed (mm/sn): ");
  Serial.println(motor_speed_val);
  return motor_speed_val;
}

int motor_control::distance_to_degree(float mm_dist){
  float distance_to_degree = mm_dist * 0.9f;
  int degree_result = distance_to_degree / 1.8f * 16;
  return degree_result;
}
