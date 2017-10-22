#ifndef TEMPERATURE_h
#define TEMPERATURE_h

#include "common.h"

//*****************************************************************************
// Global variables provided by temperature.h
//*****************************************************************************

// number of times to sample each time readMeanResistance is called
int NTH = 50;

// temperature.h error codes
#define ERR_TEMP 0x700
#define ERR_TEMP_INVALID_RTH (ERR_TEMP | 0x1) // resistance value is invalid/impossible
#define ERR_TEMP_INVALID_TMP (ERR_TEMP | 0x2) // temperature value is invalid/impossible
#define ERR_TEMP_NAN (ERR_TEMP | ERR_NAN_VALUE) // nan encountered (0x7c0)
#define ERR_TEMP_INF (ERR_TEMP | ERR_INF_VALUE) // inf encountered (0x780)

//*****************************************************************************
// Global functions provided by temperature.h
//*****************************************************************************

/**
 * err = readMeanResistance(Rth,Rth_unc)
 * This function reads the thermistor ADC and determines the resistance 
 * of the thermistor. This function should read the thermistor NTH times
 * each time it is called, and average the values to get the actual 
 * resistance. The uncertainty in the resistance measurement is be based 
 * on the variance of the NTH measurements, and on the uncertainty of the 
 * circuit (ie. the 20kOhm resistor has 0.1% tolerance).
 * 
 * When the function is successful, it should return zero.
 */
int readMeanResistance(float & Rth, float & Rth_unc) {
  // write your code here
  message("readMeanResistance");
  message("Rth: ", Rth);
  message("Rth_unc: ", Rth_unc);
  return -1;
}


/**
 * err = calcTmp(Rth, Rth_unc, tmp, tmp_unc);
 * This function should use the calibration constants TEMPERATURE_CAL_* in the
 * file common.h to calculate the temperature corresponding to the measured 
 * resistance of the thermistor. The temperature uncertainty is based on the 
 * resistance uncertainty, the uncertainty of the calibration constants, and the 
 * uncertainty specified by the manufacturer in the thermistor datasheet.
 * 
 * The temperature returned in tmp should be in degrees celsius.
 * 
 * If the calculations are successful, the function should return 0.
 */
int calcTmp(float Rth, float Rth_unc, float & tmp, float & tmp_unc) {
  // write your code here
  message("calcTmp");
  message("Rth: ", Rth);
  message("Rth_unc: ", Rth_unc);
  message("tmp: ", tmp);
  message("tmp_unc: ", tmp_unc);
  return -1;
}



#endif
