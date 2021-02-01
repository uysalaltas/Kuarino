#include "extruder.h"
#include "utils.h"
#include "pins.h"
#include "Arduino.h"

utils tools2;
bool vacuumValve = false;

exturder::exturder(){
  init();
}

void exturder::init(){

}

void exturder::extruder_in(int mm, int motor_speed_val){
  digitalWrite(E1_ENABLE_PIN, LOW);

  int ext_dist = tools2.distance_to_degree(mm);
  int motor_speed_ext = tools2.motor_speed(motor_speed_val);
  digitalWrite(E1_DIR_PIN, LOW);
  
  for (int val = 0; val < ext_dist; val++)
  {
    digitalWrite(E1_STEP_PIN, HIGH);
    delayMicroseconds(motor_speed_ext);
    digitalWrite(E1_STEP_PIN, LOW);
    delayMicroseconds(motor_speed_ext);
  }
}

void exturder::extruder_out(int mm, int motor_speed_val){
  int motor_speed_ext = tools2.motor_speed(motor_speed_val);
  int ext_dist = tools2.distance_to_degree(mm);
  digitalWrite(E1_DIR_PIN, HIGH);

  for (int val = 0; val < ext_dist; val++)
  {
    digitalWrite(E1_STEP_PIN, HIGH);
    delayMicroseconds(motor_speed_ext);
    digitalWrite(E1_STEP_PIN, LOW);
    delayMicroseconds(motor_speed_ext);
  }
  Serial.println("---END---");
}

void exturder::vacuum_control(){
  
  if (vacuumValve == false)
  {
    analogWrite(V1_ENABLE_PIN, 255);
    digitalWrite(V1_IN_1, HIGH);
    digitalWrite(V1_IN_2, LOW);
    vacuumValve = true;
  }
  else
  {
    digitalWrite(V1_IN_1, LOW);
    digitalWrite(V1_IN_2, LOW);
    vacuumValve = false;
  }
  Serial.println("---END---");
  
}

void exturder::selenoid_on(){
  digitalWrite(SELENOID, HIGH);
  Serial.println("---END---");
}

void exturder::selenoid_off(){
  digitalWrite(SELENOID, LOW);
  Serial.println("---END---");
}