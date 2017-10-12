#ifndef HUMIDITY_h
#define HUMIDITY_h

#include "common.h"

/**
 * readRH
 */
int readRH(float & RH, float & RH_unc) {
  // write your code here
  message("readRH");
  return 1;
}

/**
 * readRHTmp
 */
int readRHTmp(float & tmp, float & tmp_unc) {
  // write your code here
  message("readRHTmp");
  return 1;
}

/**
 * calculateDewPoint
 */
int calculateDewPoint(float tmp, float tmp_unc, float RH, float RH_unc, 
      float & dewPoint, float & dewPoint_unc) 
{
  // write your code here
  message("calculateDewPoint");
  message(tmp);
  message(RH);
  message(RH_unc);
  message(tmp_unc);
  return 1;
}

/**
 * checkRH
 */
int checkRH() {
  // write your code here
  message("checkRH");
  return 1;
}










#endif
