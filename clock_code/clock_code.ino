#include "common.h"
#include "clock.h"
#include "RTClib.h"

/**
 * Write code here to test the code in clock.h
 */


//*****************************************************************************
//                 The Setup Function.
//*****************************************************************************
void setup() {
  char timeStr[9] = "12:03:12";
  char dateStr[11] = "11/23/1926";
  // Initialize the serial port.
  Serial.begin(115200);
  message(getTimeString(timeStr));
  message(timeStr);
  message(getDateString(dateStr));
  message(dateStr);
  message(checkClock());
}



//*****************************************************************************
//                  The Loop Function.
//*****************************************************************************
void loop() {
  
}



