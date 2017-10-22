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
  message(validateTmp(testArray[0]));
  message(validateRH(testArray[1]));
  message(validatePrs(testArray[2]));
}



//*****************************************************************************
//                  The Loop Function.
//*****************************************************************************
void loop() {
  
}



