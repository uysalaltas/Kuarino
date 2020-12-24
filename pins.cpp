#include "Arduino.h"
#include "pins.h"


pins::pins(){
  init();
}

void pins::init(){
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

  pinMode(SELENOID, OUTPUT);
  
  pinMode(X_MIN_PIN, INPUT_PULLUP);
  pinMode(X_MAX_PIN, INPUT_PULLUP);
}