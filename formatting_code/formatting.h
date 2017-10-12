#ifndef FORMATTING_h
#define FORMATTING_h

#include "common.h"

float validateTmp(float tmp);
float validateRH(float RH);
float validatePrs(float prs);


/**
 * formatValues
 */
int formatValues(char output[], int outputSize, float values[], int arraySize) {
  // write your code here
  message("formatValues");
  return 1;
}

/**
 * validateTmp
 */
float validateTmp(float tmp) {
  // write your code here
  message("validateTmp");
  message(tmp);
  return 1.0;
}

/**
 * validateRH
 */
float validateRH(float RH) {
  // write your code here
  message("validateRH");
  message(RH);
  return 1.0;
}

/**
 * validatePrs
 */
float validatePrs(float prs) {
  // write your code here
  message("validatePrs");
  message(prs);
  return 1.0;
}






#endif
