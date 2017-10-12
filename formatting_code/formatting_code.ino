#include "common.h"
#include "formatting.h"

/**
 * Write code here to test the formatting function in formatting.h
 */


//*****************************************************************************
//                 The Setup Function.
//*****************************************************************************
void setup() {
  float testArray[3] = {2.3, 5212.2, -23.0};
  char testOut[40];
  // Initialize the serial port.
  Serial.begin(115200);
  message(formatValues(testOut, 40, testArray, 3));
  message(testOut);
  message(validateTmp(10.0));
  message(validateRH(10.0));
  message(validatePrs(10.0));
}



//*****************************************************************************
//                  The Loop Function.
//*****************************************************************************
void loop() {
  
}



