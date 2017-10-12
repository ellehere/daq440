#ifndef TEMPERATURE_h
#define TEMPERATURE_h

#include "common.h"

/**
 * readMeanResistance
 */
int readMeanResistance(float & Rth, float & Rth_unc) {
  // write your code here
  message("readMeanResistance");
  return 1;
}


/**
 * calcTmp
 */
int calcTmp(float Rth, float & tmp, float & tmp_unc) {
  // write your code here
  message("calcTmp");
  message(Rth);
  return 1;
}



#endif
