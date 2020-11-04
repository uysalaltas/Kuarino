#include "motor_control.h"
#include "gcode.h"
#include "end_stop.h"

float justOnce = true;
String serial_data;
int loopX = 1;

gcode gcode_read;

void setup() {
  Serial.begin(115200);
  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Y_ENABLE_PIN, HIGH);
  digitalWrite(E1_ENABLE_PIN, HIGH);
}

void loop() {
  
  if (Serial.available() > 0) {
    serial_data = Serial.readString();
    char read_g_code [serial_data.length()];
    serial_data.toCharArray(read_g_code, serial_data.length());
    Serial.println("G-Code: ");
    Serial.println(read_g_code);
    gcode_read.g_control(read_g_code);
  }
}
