#include "common.h"
#include "calibration.h"

/**
 * Write code here to test the calibration code in calibration.h
 */
 
//*****************************************************************************
//                 The Setup Function.
//*****************************************************************************
void setup() {
  // Initialize the serial port.
  Serial.begin(115200);
  message(loadCalibrationFile());
}



//*****************************************************************************
//                  The Loop Function.
//*****************************************************************************
void loop() {
  
}



