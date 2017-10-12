#ifndef TEMPERATURE_h
#define TEMPERATURE_h


float TEMPERATURE_CAL_A; float TEMPERATURE_CAL_A_UNC;
float TEMPERATURE_CAL_B; float TEMPERATURE_CAL_B_UNC;
float TEMPERATURE_CAL_C; float TEMPERATURE_CAL_C_UNC;

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
