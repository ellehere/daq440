#include "common.h"
#include "temperature.h"

/**
 * Write code here to test 
 */

//*****************************************************************************
//                 The Setup Function.
//*****************************************************************************
void setup() {
  float Rth,Rth_unc,tmp,tmp_unc;
  // Initialize the serial port.
  Serial.begin(115200);
  message(readMeanResistance(Rth, Rth_unc));
  message(Rth);
  message(Rth_unc);
  message(calcTmp(Rth, Rth_unc, tmp, tmp_unc));
  message(tmp);
  message(tmp_unc);
}



//*****************************************************************************
//                  The Loop Function.
//*****************************************************************************
void loop() {
  
}



