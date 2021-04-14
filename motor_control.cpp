#include "motor_control.h"
#include "end_stop.h"
#include "Arduino.h"
#include "pins.h"
#include "utils.h"


utils tools1;
const int stepsPerRevolution = 200;
float stepPerAngle = 1.8;
unsigned long myTime1;
unsigned long myTime2;
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

  int bool_x = false;
  int bool_y = false;

  for(int i = 0; i < 3; i++){
    if(motor_axis[i] == 'X'){
      index_x = i;
      bool_x = true;
    } 
    else if(motor_axis[i] == 'Y'){
      index_y = i;
      bool_y = true;
    }    
    // else if(motor_axis[i] == 'Z'){
    //   index_z = i;
    //   bool_z = true;
    // }
  }

  float num_step = 0;
  for(int i = 0; i < 3; i++){
    if(num_step < mm[i]){
      num_step = mm[i];
    }
  }

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
    digitalWrite(Z_DIR_PIN, LOW);
  } else {
    digitalWrite(Y_DIR_PIN, HIGH);
    digitalWrite(Z_DIR_PIN, HIGH);
  }

  //--- Motor movement ---
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);

  int motor_speed_val = tools1.motor_speed(motor_spd);
  
  // double mx = 5;
  // double mn = 0;
  // double temp_jerk;
  // double jerk_step;
  // double jerk_step1;
  // double jerk_step2;

  int jerk_int;
  float era = num_step * ACCEL_CURVE;
  float era2 = num_step - (era * 2);
  float era3 = num_step;

  Serial.print("Speed : ");
  Serial.println(motor_speed_val);
  
  for(int val = 0; val < num_step; val++)
  {
    // temp_jerk = ((mx - mn) / num_step) * val;
    // jerk_step1 = 1 / (1 + exp(ACCEL_SLOPE * (temp_jerk - HALF_POINT_C1)));
    // jerk_step2 = 1 / (1 + exp(DECEL_SLOPE * (temp_jerk - HALF_POINT_C2)));
    // jerk_step = (motor_speed_val * 2) - (abs(jerk_step1 - jerk_step2) * motor_speed_val);

    if (val <= era)
    {
      jerk_int = motor_speed_val + (motor_speed_val - ( (val / era) * motor_speed_val));
    } 
    else if (val > era && val <= era2)
    {
      jerk_int = motor_speed_val;
    } 
    else
    {
      jerk_int = motor_speed_val + ( ( (val - era2) / era ) * motor_speed_val);
    }

    // Motor X
    if(val < num_step_x && bool_x){
      digitalWrite(X_STEP_PIN, HIGH);
      delayMicroseconds(jerk_int / 2);
      digitalWrite(X_STEP_PIN, LOW);
      delayMicroseconds(jerk_int / 2);
    }

    // Motor Y
    if(val < num_step_y && bool_y){
      digitalWrite(Y_STEP_PIN, HIGH);
      digitalWrite(Z_STEP_PIN, HIGH);
      delayMicroseconds(jerk_int / 2);
      digitalWrite(Y_STEP_PIN, LOW);
      digitalWrite(Z_STEP_PIN, LOW);
      delayMicroseconds(jerk_int / 2);
    }

    jerk_int = 0;
    // jerk_step = 0;
    // jerk_step1 = 0;
    // jerk_step2 = 0;
  }
  // Serial.println(myTime1 - myTime2);

  int x_step_count = 0;
  bool x_step_val = true;
  unsigned long previousMillisX = 0;

  int y_step_count = 0;
  bool y_step_val = true;
  unsigned long previousMillisY = 0;

  Serial.println(motor_speed_val);

  // for (;;)
  // {
  //   unsigned long currentMillis = millis();
  //   Serial.println("FOR");
  //   Serial.println(x_step_val);
  //   Serial.println(currentMillis - previousMillisX);
  //   if (currentMillis - previousMillisX >= motor_speed_val/2 && x_step_count < num_step_x)
  //   {
  //     digitalWrite(X_STEP_PIN, HIGH);
  //     previousMillisX = currentMillis;
  //     Serial.println("X H");
  //     digitalWrite(X_STEP_PIN, LOW);
  //     x_step_count += 1;
  //   } 
  //   if (currentMillis - previousMillisY >= motor_speed_val/2 && y_step_count < num_step_y)
  //   {
  //     digitalWrite(Y_STEP_PIN, HIGH);
  //     digitalWrite(Z_STEP_PIN, HIGH);
  //     previousMillisY = currentMillis;
  //     Serial.println("Y H");
  //     digitalWrite(Y_STEP_PIN, LOW);
  //     digitalWrite(Z_STEP_PIN, LOW);
  //     y_step_count += 1;
  //   } 
  //   if (y_step_count > num_step_y && x_step_count > num_step_x)
  //   {
  //     break;
  //   }
  // } 
}

void motor_control::cartridge_motor(int mm, int motor_spd){
  digitalWrite(E0_ENABLE_PIN, LOW);
  float dist_cart_mm = tools1.distance_to_degree(mm);
  int cart_speed = tools1.motor_speed(motor_spd);
  
  int jerk_int;
  float era = dist_cart_mm / 4;
  float era2 = (dist_cart_mm / 2) + era;
  float era3 = dist_cart_mm;

  for (int i = 0; i < dist_cart_mm; i++)
  {
    if (i <= era)
    {
      jerk_int = cart_speed + (cart_speed - ( (i / era) * cart_speed));
    } else if (i > era && i <= era2)
    {
      jerk_int = cart_speed;
    } else
    {
      jerk_int = cart_speed + ( ( (i - era2) / era ) * cart_speed);
    }
    
    digitalWrite(E0_STEP_PIN, HIGH);
    delayMicroseconds(jerk_int / 2);
    digitalWrite(E0_STEP_PIN, LOW);
    delayMicroseconds(jerk_int / 2);
    jerk_int = 0;
  }
  
}

void motor_control::home_all(){
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);
  digitalWrite(E1_ENABLE_PIN, LOW);

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
  digitalWrite(Z_DIR_PIN, LOW);
  for(;;){
    int stop_val_y = limit_switch.stop_y();
    if(stop_val_y == 0){
      break;
    }
    digitalWrite(Y_STEP_PIN, HIGH);
    digitalWrite(Z_STEP_PIN, HIGH);
    delayMicroseconds(100);
    digitalWrite(Y_STEP_PIN, LOW);
    digitalWrite(Z_STEP_PIN, LOW);
    delayMicroseconds(100);
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
  digitalWrite(Z_ENABLE_PIN, HIGH);
  digitalWrite(E0_ENABLE_PIN, HIGH);
  digitalWrite(E1_ENABLE_PIN, HIGH);
  Serial.println("---END---");
}
