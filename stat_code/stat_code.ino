#include "common.h"
#include "stats.h"

/**
 * Write code here to test the statistical functions in stats.h
 */

float statArray[5];

//*****************************************************************************
//                 The Setup Function.
//*****************************************************************************
void setup() {
  float fstat = 0.0;
  // Initialize the serial port.
  Serial.begin(115200);
  initStats(statArray);
  updateStats(11.1111, statArray);
  updateStats(5.3, statArray);
  updateStats(8.41619, statArray);
  fstat = calcMean(statArray);
  message(fstat);
  message(calcStd(statArray));
  message(calcSkewness(statArray));
  message(calcKurtosis(statArray));
}



//*****************************************************************************
//                  The Loop Function.
//*****************************************************************************
void loop() {
  
}



