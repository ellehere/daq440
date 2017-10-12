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
  char testString[50] = "test this";
  // Initialize the serial port.
  Serial.begin(115200);
  message(initSDCard());
  message(writeDataToSDFile(testString));
  message(getSDFileName(testString,50));
  message(testString);
  message(checkSD());
}



//*****************************************************************************
//                  The Loop Function.
//*****************************************************************************
void loop() {
  
}



