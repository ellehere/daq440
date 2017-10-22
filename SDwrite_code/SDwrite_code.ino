#include "common.h"
#include "SDwrite.h"
#include <SD.h>

/**
 * Write code here to test the functions in SDwrite.h
 */


//*****************************************************************************
//                 The Setup Function.
//*****************************************************************************
void setup() {
  int testStrLength = 50;
  char testString[testStrLength] = "test this";
  // Initialize the serial port.
  Serial.begin(115200);
  message(initSDCard());
  message(writeDataToSDFile(testString,testStrLength));
  message(getSDFileName(testString));
  message(testString);
  message(checkSD());
}



//*****************************************************************************
//                  The Loop Function.
//*****************************************************************************
void loop() {
  
}



