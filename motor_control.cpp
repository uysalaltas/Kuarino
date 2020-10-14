#include "motor_control.h"
#include "Arduino.h"

const int stepsPerRevolution = 200;
float stepPerAngle = 1.8;

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

void motor_control::motorOn(char motor_axis, float mm, char motor_direction = '+'){
  Serial.println(motor_axis);
  Serial.println(mm);
  Serial.println(motor_direction);

  if(motor_axis == 'X'){
    if(motor_direction == '-'){
      digitalWrite(X_DIR_PIN, LOW);
    } else {
      digitalWrite(X_DIR_PIN, HIGH);
    }
    float distance_to_degree_x = mm * 0.9f;
    int numStep_x = distance_to_degree_x / stepPerAngle * 16;
    
    for(int x = 0; x < numStep_x; x++)
    {
      digitalWrite(X_STEP_PIN, HIGH);
      delayMicroseconds(100);
      digitalWrite(X_STEP_PIN, LOW);
      delayMicroseconds(100);
    }
    Serial.println("X motor endend");
  } 
  else if (motor_axis == 'Y'){
    if(motor_direction == '-'){
      digitalWrite(Y_DIR_PIN, LOW);
    } else {
      digitalWrite(Y_DIR_PIN, HIGH);
    }
    float distance_to_degree_y = mm * 0.9f;
    int numStep_y = distance_to_degree_y / stepPerAngle * 16;
    for(int x = 0; x < numStep_y; x++)
    {
      digitalWrite(Y_STEP_PIN, HIGH);
      delayMicroseconds(100);
      digitalWrite(Y_STEP_PIN, LOW);
      delayMicroseconds(100);
    }
    Serial.println("Y motor ended");
  }
  
}
