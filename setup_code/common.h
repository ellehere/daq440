#ifndef COMMON_h
#define COMMON_h

/**
 * FILE common.h
 * Common functions and variables used by multiple tasks.
 * This file is for global variables or constants and for basic
 * utility-type functions.
 * 
 * Written by LEH, 10/11/2017
 */



/**
 * Calibration constants
 * (global variables)
 */

// thermistor calibration constants
float TEMPERATURE_CAL_A; float TEMPERATURE_CAL_A_UNC;
float TEMPERATURE_CAL_B; float TEMPERATURE_CAL_B_UNC;
float TEMPERATURE_CAL_C; float TEMPERATURE_CAL_C_UNC;

// elevation of the Arduino Uno, used for equivalent-SLP calculation
float UNO_ELEVATION;

/**
 * FUNCTION message
 * This function takes an argument and prints it out to the serial
 * monitor, preceded by the current time since the arduino was last 
 * reset (in milliseconds).
 * The argument can be a string (character array), float, or int.
 * 
 */
void message(char msg[]) {
  Serial.print(millis());
  Serial.print(": ");
  Serial.println(msg);
}

// message a floating point number
void message(float msg) {
  char ch_msg[15];
  dtostre(msg,ch_msg,3,1);
  message(ch_msg);
}

// message a floating point number, and specify precision
void message(float msg, int digits) {
  char ch_msg[20];
  dtostre(msg,ch_msg,digits,1);
  message(ch_msg);
}

// message an integer
void message(int msg) {
  char ch_msg[20];
  ltoa(msg,ch_msg,10);
  message(ch_msg);
}

// message an integer, and specify the base (default base 10)
void message(int msg, int base) {
  char ch_msg[20];
  ultoa(msg,ch_msg,base);
  message(ch_msg);
}

#endif
