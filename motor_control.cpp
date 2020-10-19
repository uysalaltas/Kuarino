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

  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
}

void motor_control::run_motors(char motor_axis[], float mm[], bool motor_direction[]){
  //--- Value Initializing ---
  int index_x = 0;
  int index_y = 0;
  int index_z = 0;

  for(int i = 0; i < 3; i++){
    if(motor_axis[i] == 'X'){
      index_x = i;
    } 
    else if(motor_axis[i] == 'Y'){
      index_y = i;
    }    
    else if(motor_axis[i] == 'Z'){
      index_z = i;
    }
  }
  
  float num_step = 0;
  for(int i = 0; i < 3; i++){
    if(num_step < mm[i]){
      num_step = mm[i];
    }
  }
  float distance_to_degree = num_step * 0.9f;
  num_step = distance_to_degree / stepPerAngle * 16;

  float distance_to_degree_x = mm[index_x] * 0.9f;
  int num_step_x = distance_to_degree_x / stepPerAngle * 16;
  bool dir_x = motor_direction[index_x];
  Serial.println(dir_x);
  if(dir_x == false){
//    Serial.println("NEG");
    digitalWrite(X_DIR_PIN, LOW);
  } else {
//    Serial.println("POS");
    digitalWrite(X_DIR_PIN, HIGH);
  }

  float distance_to_degree_y = mm[index_y] * 0.9f;
  int num_step_y = distance_to_degree_y / stepPerAngle * 16;
  bool dir_y = motor_direction[index_y];
  if(dir_y == false){
    digitalWrite(Y_DIR_PIN, LOW);
  } else {
    digitalWrite(Y_DIR_PIN, HIGH);
  }
  
  float distance_to_degree_z = mm[index_z] * 0.9f;
  int num_step_z = distance_to_degree_z / stepPerAngle * 16;
  bool dir_z = motor_direction[index_z];
  if(dir_z == false){
    digitalWrite(Z_DIR_PIN, LOW);
  } else {
    digitalWrite(Z_DIR_PIN, HIGH);
  }

//  Serial.print("X: ");
//  Serial.println(motor_direction[index_x]);
//  Serial.println(mm[index_x]);
//
//  Serial.print("Y: ");
//  Serial.println(motor_direction[index_y]);
//  Serial.println(mm[index_y]);

  //--- Motor movement ---
  
  for(int val = 0; val < num_step; val++)
  {
    // Motor X
    if(val < num_step_x){
      digitalWrite(X_STEP_PIN, HIGH);
      delayMicroseconds(100);
      digitalWrite(X_STEP_PIN, LOW);
      delayMicroseconds(100);
    }

    // Motor Y
    if(val < num_step_y){
      digitalWrite(Y_STEP_PIN, HIGH);
      delayMicroseconds(100);
      digitalWrite(Y_STEP_PIN, LOW);
      delayMicroseconds(100);
    }

    // Motor Z
    if(val < num_step_z){
      digitalWrite(Z_STEP_PIN, HIGH);
      delayMicroseconds(100);
      digitalWrite(Z_STEP_PIN, LOW);
      delayMicroseconds(100);
    }
  }
  Serial.println("Done!");
}

void motor_control::home_all(){
  Serial.println("Home All Started");
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
  Serial.println("OK.");
  Serial.println("-------------------");
}

//void motor_control::motor_on(char motor_axis, float mm, char motor_direction = '+'){
//  Serial.println(motor_axis);
//  Serial.println(mm);
//  Serial.println(motor_direction);
//
//  if(motor_axis == 'X'){
//    if(motor_direction == '-'){
//      digitalWrite(X_DIR_PIN, LOW);
//    } else {
//      digitalWrite(X_DIR_PIN, HIGH);
//    }
//    float distance_to_degree_x = mm * 0.9f;
//    int numStep_x = distance_to_degree_x / stepPerAngle * 16;
//    
//    for(int x = 0; x < numStep_x; x++)
//    {
//      digitalWrite(X_STEP_PIN, HIGH);
//      delayMicroseconds(100);
//      digitalWrite(X_STEP_PIN, LOW);
//      delayMicroseconds(100);
//    }
//    Serial.println("X motor endend");
//  }
//  else if (motor_axis == 'Y'){
//    if(motor_direction == '-'){
//      digitalWrite(Y_DIR_PIN, LOW);
//    } else {
//      digitalWrite(Y_DIR_PIN, HIGH);
//    }
//    float distance_to_degree_y = mm * 0.9f;
//    int numStep_y = distance_to_degree_y / stepPerAngle * 16;
//    for(int x = 0; x < numStep_y; x++)
//    {
//      digitalWrite(Y_STEP_PIN, HIGH);
//      delayMicroseconds(100);
//      digitalWrite(Y_STEP_PIN, LOW);
//      delayMicroseconds(100);
//    }
//    Serial.println("Y motor ended");
//  }
//}

//void motor_control::control_x(float mm, char motor_direction = '+'){
//  if(motor_direction == '-'){
//    digitalWrite(X_DIR_PIN, LOW);
//  } else {
//    digitalWrite(X_DIR_PIN, HIGH);
//  }
//  float distance_to_degree_x = mm * 0.9f;
//  int numStep_x = distance_to_degree_x / stepPerAngle * 16; 
//  for(int x = 0; x < numStep_x; x++)
//  {
//    digitalWrite(X_STEP_PIN, HIGH);
//    delayMicroseconds(100);
//    digitalWrite(X_STEP_PIN, LOW);
//    delayMicroseconds(100);
//  }
//  Serial.println("X motor endend");
//}
//
//void motor_control::control_y(float mm, char motor_direction = '+'){
//  if(motor_direction == '-'){
//    digitalWrite(Y_DIR_PIN, LOW);
//  } else {
//    digitalWrite(Y_DIR_PIN, HIGH);
//  }
//  float distance_to_degree_y = mm * 0.9f;
//  int numStep_y = distance_to_degree_y / stepPerAngle * 16; 
//  for(int x = 0; x < numStep_y; x++)
//  {
//    digitalWrite(Y_STEP_PIN, HIGH);
//    delayMicroseconds(100);
//    digitalWrite(Y_STEP_PIN, LOW);
//    delayMicroseconds(100);
//  }
//  Serial.println("Y motor endend");
//}
