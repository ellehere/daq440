#include "common.h"
#include "pressure.h"

/**
 * Write code here to test pressure.h
 */

//*****************************************************************************
//                 The Setup Function.
//*****************************************************************************
void setup() {
  float prs,prs_unc,tmp,tmp_unc,SLP;
  // Initialize the serial port.
  Serial.begin(115200);
  message(readPrs(prs, prs_unc));
  message(prs);
  message(prs_unc);
  message(readPrsTmp(tmp, tmp_unc));
  message(tmp);
  message(tmp_unc);
  message(toSLP(prs, tmp, SLP));
  message(SLP);
  message(toLocalPrs(SLP, tmp, prs));
  message(prs);
}



//*****************************************************************************
//                  The Loop Function.
//*****************************************************************************
void loop() {
  
}



