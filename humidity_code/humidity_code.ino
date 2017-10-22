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
  message("readRH: ",readRH(RH, RH_unc));
  message("RH: ",RH);
  message("RH_unc: ",RH_unc);
  message("readRHTmp: ",readRHTmp(tmp, tmp_unc));
  message("tmp: ",tmp);
  message("tmp_unc: ",tmp_unc);
  message("calculateDewPoint: ",calculateDewPoint(tmp, tmp_unc, RH, RH_unc, dewPoint, dewPoint_unc));
  message("dewPoint: ",dewPoint);
  message("dewPoint_unc: ",dewPoint_unc);
  message("checkRH: ",checkRH());
}



//*****************************************************************************
//                  The Loop Function.
//*****************************************************************************
void loop() {
  
}



