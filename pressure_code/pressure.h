#ifndef PRESSURE_h
#define PRESSURE_h

#include "common.h"
#include "SFE_BMP180.h"

//*****************************************************************************
// Global variables provided by pressure.h
//*****************************************************************************

// error codes defined by BMP180 library
#define ERR_PRS_BUFFER_ERROR 0x1 // Data too long to fit in transmit buffer
#define ERR_PRS_CONNECTION_ERROR 0x2 // Received NACK on transmit of address
#define ERR_PRS_BMP_BUSY 0x3 // Received NACK on transmit of data
#define ERR_PRS_BMP_OTHER 0x4 // Other error
#define ERR_PRS_INVALID_PRS 0x8 // The pressure received was invalid
#define ERR_PRS_INVALID_TMP 0x10 // The temperature received was invalid


// global pressure sensor object variable for the BMP180
SFE_BMP180 BMP180;

//*****************************************************************************
// Functions provided by pressure.h
//*****************************************************************************

// function signatures
int toLocalPrs(float SLP, float tmp, float & prs);
int toSLP(float prs, float tmp, float & SLP);
int readPrsTmp(float & tmp, float & tmp_unc);
int readPrs(float & prs, float & prs_unc);

/**
 * err = readPrs(prs, prs_unc);
 * This function reads the pressure from the BMP180. The pressure
 * uncertainty is set based on the device datasheet.
 * 
 * The function should return 0 if successful and another error if not.
 * A device error code is provided by BMP180.getError();
 * The function should also check that the received pressure is reasonable.
 * If it is not reasonable, or if getError() returns an error, the function 
 * returns an integer including the ERR_PRS_INVALID_PRS flag. For example:
 *   int err = BMP180.getError();
 *   ... {check for invalid value} ...
 *   err = err | ERR_PRS_INVALID_TMP;
 *   return err;
 */
int readPrs(float & prs, float & prs_unc) {
  // write your code here
  message("read");
  message("prs: ", prs);
  message("prs_unc: ", prs_unc);
  return -1;
}
 
/**
 * err = readPrsTmp(tmp, tmp_unc);
 * This function reads the temperature from the BMP180. The temperature
 * uncertainty is set based on the device datasheet.
 * 
 * The function should return 0 if successful and another error if not.
 * A device error code is provided by BMP180.getError(); * 
 * The function should also check that the received temperature is reasonable.
 * If it is not reasonable, or if getError() returns an error, the function 
 * returns an integer including the ERR_PRS_INVALID_TMP flag. For example:
 *   int err = BMP180.getError();
 *   ... {check for invalid value} ...
 *   err = err | ERR_PRS_INVALID_TMP;
 *   return err;
 */
int readPrsTmp(float & tmp, float & tmp_unc) {
  // write your code here
  message("readPrsTmp");
  message("tmp: ", tmp);
  message("tmp_unc: ", tmp_unc);
  return -1;
}

/**
 * err = toSLP(prs, elevation, tmp, SLP);
 * This function calculates the adjusted sea-level pressure using
 * the pressure, temperature, and elevation. Elevation is provided
 * by the calibration file and it is a global variable in common.h.
 * 
 * If the calculation is successful, toSLP should return 0.
 */
int toSLP(float prs, float tmp, float & SLP) {
  float elevation = UNO_ELEVATION;
  // write your code here
  message("toSLP");
  message("prs: ", prs);
  message("tmp: ", tmp);
  message("elevation: ", elevation);
  message("SLP: ", SLP);
  return -1;
}

/**
 * err = toLocalPrs(SLP, tmp, prs);
 * This function calculates the actual surface pressure from 
 * the adjusted sea-level pressure, temperature, and elevation. 
 * Elevation is provided by the calibration file and it is a 
 * global variable in common.h.
 * 
 * If the calculation is successful, toSLP should return 0.
 */
int toLocalPrs(float SLP, float tmp, float & prs) {
  float elevation = UNO_ELEVATION;
  // write your code here
  message("toLocalPrs");
  message("SLP: ", SLP);
  message("tmp: ", tmp);
  message("elevation: ", elevation);
  message("prs: ", prs);
  return -1;
}

#endif
