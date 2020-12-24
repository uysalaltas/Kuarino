#include "end_stop.h"
#include "Arduino.h"
#include "pins.h"

end_stop::end_stop(){
  init();
}

void end_stop::init(){

}

int end_stop::stop_x(){
  
  int x_min_switch = digitalRead(X_MIN_PIN);
  int x_max_switch = digitalRead(X_MAX_PIN);
  
  return x_min_switch;
}

int end_stop::stop_y(){
  
  int y_min_switch = digitalRead(Y_MIN_PIN);
  int y_max_switch = digitalRead(Y_MAX_PIN);
  
  return y_min_switch;
}

int end_stop::stop_z(){
  
  int z_min_switch = digitalRead(Z_MIN_PIN);
  int z_max_switch = digitalRead(Z_MAX_PIN);

  return z_min_switch;
}
