#ifndef PRESSURE_h
#define PRESSURE_h

float UNO_ELEVATION;

/**
 * readPrs
 */
int readPrs(float & prs, float & prs_unc) {
  // write your code here
  message("readPrs");
  return 1;
}
 
/**
 * readPrsTmp
 */
int readPrsTmp(float & tmp, float & tmp_unc) {
  // write your code here
  message("readPrsTmp");
  return 1;
}

/**
 * toSLP
 */
int toSLP(float prs, float elevation, float tmp, float & SLP) {
  // write your code here
  message("toSLP");
  return 1;
}

/**
 * toLocalPrs
 */
int toLocalPrs(float SLP, float elevation, float tmp, float & prs) {
  // write your code here
  message("toLocalPrs");
  return 1;
}

#endif