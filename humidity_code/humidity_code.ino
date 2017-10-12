#include "common.h"
#include "humidity.h"

/**
 * Write code here to test humidity.h
 */

//*****************************************************************************
//                 The Setup Function.
//*****************************************************************************
void setup() {
  float RH,RH_unc,tmp,tmp_unc,dewPoint,dewPoint_unc;
  // Initialize the serial port.
  Serial.begin(115200);
  message(readRH(RH, RH_unc));
  message(RH);
  message(RH_unc);
  message(readRHTmp(tmp, tmp_unc));
  message(tmp);
  message(tmp_unc);
  message(calculateDewPoint(tmp, tmp_unc, RH, RH_unc, 
      dewPoint, dewPoint_unc));
  message(dewPoint);
  message(dewPoint_unc);
  message(checkRH());
}



//*****************************************************************************
//                  The Loop Function.
//*****************************************************************************
void loop() {
  
}



