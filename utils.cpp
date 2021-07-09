#include "Arduino.h"
#include "utils.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>


#define GCODE_MAX_LEN 3
#define AXIS_MAX_LEN 12
#define SPEED_MAX_LEN 4

utils::utils(){
  init();
}

void utils::init(){

}

void utils::split_gcode(char command[], char axes_dir[], char axes_speed[], char gcode_array[]){
  initialize_char_array(GCODE_MAX_LEN, command);
  initialize_char_array(AXIS_MAX_LEN , axes_dir);
  initialize_char_array(SPEED_MAX_LEN, axes_speed);

  int code_index = 0;
  int arr_len = strlen(gcode_array);
  
  int temp_inx = 0;
  int temp_len = 12;
  char temp_arr[temp_len];
  
  for (int i = 0; i < arr_len; i++)
  {
    if (i == 0)
    {
      for (int j = 0; j < temp_len; j++)
      {
        temp_arr[j] = 0;
      }
    }
    else
    {
      if (gcode_array[i] == 32 || gcode_array[i] == 10)
      {
        if (code_index == 0)
        {
          char_array_to_char_array(command, temp_arr, GCODE_MAX_LEN);
        }
        else if (code_index == 1)
        {
          char_array_to_char_array(axes_dir, temp_arr, AXIS_MAX_LEN);
        }
        else if (code_index == 2)
        {
          char_array_to_char_array(axes_speed, temp_arr, SPEED_MAX_LEN);
        }

        code_index += 1;
        temp_inx = 0;
        for (int j = 0; j < temp_len; j++)
        {
          temp_arr[j] = 0;
        }
      }
      else
      {
        Serial.println(gcode_array[i]);
        temp_arr[temp_inx] = gcode_array[i];      
        temp_inx += 1;
      }
    }
  }  
}

char* utils::convert_integer_to_char(int N, int* digit_out){
  int m = N;
  int digit = 0;
  char* arr;
  while (m) {
    digit++;
    m /= 10;
  }
  char arr1[digit];
  arr = (char*)malloc(digit);
  int index = 0;
  while (N) {
    arr1[++index] = N % 10 + '0';
    N /= 10;
  }
  int i;
  for (i = 0; i < index; i++) {
    arr[i] = arr1[index - i];
  }
  *digit_out = digit;
  arr[i] = '\0';

  return arr;
}

void utils::char_array_to_char_array(char out[], char in[], int len_arr){

  for (int x = 0; x < len_arr; x++)
  {
    out[x] = in[x];
  }
}

void utils::initialize_char_array(int max_len, char char_arr[]){
  for (int i = 0; i < max_len; i++)
  {
    char_arr[i] = 0;
  }
}

int utils::motor_speed(int speed_control){
  int motor_speed_val = 1000000 / (speed_control * 8);
  // Serial.print("Motor Speed (mm/sn): ");
  // Serial.println(motor_speed_val);
  return motor_speed_val;
}

int utils::distance_to_degree(float mm_dist){
  float distance_to_degree = mm_dist * 0.9f;
  int degree_result = distance_to_degree / 1.8f * 16;
  return degree_result;
}


