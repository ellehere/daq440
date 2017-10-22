#include "common.h"
// all of the other codes
#include "calibration.h"
#include "clock.h"
#include "formatting.h"
#include "humidity.h"
#include "pressure.h"
#include "stats.h"
#include "temperature.h"

/**
 * In this file, write the main setup code to initialize the Arduino Uno
 * before it begins data acquisition
 * 
 * Refer to *.h files to determine what must be initialized and in what order.
 */


//*****************************************************************************
//                 The Setup Function.
//*****************************************************************************
void setup() {
  // Initialize the serial port.
  Serial.begin(115200);
}



//*****************************************************************************
//                  The Loop Function.
//*****************************************************************************
void loop() {
  
}



