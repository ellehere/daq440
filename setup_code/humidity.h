#ifndef HUMIDITY_h
#define HUMIDITY_h

#include "common.h"
#include "Adafruit_Si7021.h"

//*****************************************************************************
// Global variables and error values provided by humidity.h
//*****************************************************************************

// RH sensor object
Adafruit_Si7021 Si7021;
int checkRH();

// humidity.h error codes
#define ERR_RH 0x500
#define ERR_RH_NO_CONTACT (ERR_RH | 0x1) // cannot contact RH sensor
#define ERR_RH_INVALID_RH (ERR_RH | 0x2) // RH value is invalid or outside of reasonable range
#define ERR_RH_INVALID_TMP (ERR_RH | 0x4) // temperature value is invalid or outside of reasonable range
#define ERR_RH_DP_ERR (ERR_RH | 0x8) // error with dewpoint calculation
#define ERR_RH_NAN (ERR_RH | ERR_NAN_VALUE) // nan encountered (0x580)
#define ERR_RH_INF (ERR_RH | ERR_INF_VALUE) // inf encountered (0x5c0)

//*****************************************************************************
// Functions provided by humidity.h
//*****************************************************************************

// function signatures
int readRH(float & RH, float & RH_unc);
int readRHTmp(float & tmp, float & tmp_unc);
float dewPtBoegel(float tmp, float RH);
float dewPtBuck(float tmp, float RH);
int checkRH();
int calculateDewPoint(float tmp, float tmp_unc, float RH, float RH_unc, 
      float & dewPoint, float & dewPoint_unc);

/**
 * err = readRH(RH,RH_unc)
 * Reads the humidity from the Si7021 humidity sensor. The variable RH
 * shall be set to the humidity value, and RH_unc shall be set according
 * to the error specified in the Si7021 datasheet.
 * 
 * The function readRH shall call checkRH() to ensure that the sensor is
 * online. If it is not, readRH returns ERR_RH_NO_CONTACT.
 * The function readRH shall check the RH value returned by 
 * Si7021.readHumidity() to ensure that it is a realistic number (between 
 * 0 and 100). If the number returned for RH is not realistic, readRH 
 * returns ERR_RH_INVALID_RH.
 * If the reading was successful, readRH returns 0.
 */
int readRH(float & RH, float & RH_unc) {
  // write your code here
  message("readRH");
  message("RH: ",RH);
  message("RH_unc: ",RH_unc);
  return 1;
}

/**
 * err = readRHTmp(tmp,tmp_unc)
 * Reads the temperature from the Si7021 humidity sensor. The variable tmp
 * shall be set to the temperature value returned by Si7021.readTemperature(), 
 * and tmp_unc shall be set according to the temperature error specified in 
 * the Si7021 datasheet.
 * 
 * The function readRHTmp shall call checkRH() to ensure that the sensor is
 * online. If it is not, readRHTmp returns ERR_RH_NO_CONTACT.
 * The function readRHTmp shall check the RH value returned by 
 * Si7021.readTemperature() to ensure that it is a realistic number (in 
 * degrees celsius). If the number returned for temperature is not realistic, 
 * readRHTmp returns ERR_RH_INVALID_TMP.
 * If the reading was successful, readRHTmp returns 0.
 */
int readRHTmp(float & tmp, float & tmp_unc) {  
  // write your code here
  message("readRHTmp");
  message("tmp: ",tmp);
  message("tmp_unc: ",tmp_unc);
  return 1;
}



/**
 * err = calculateDewPoint(tmp, tmp_unc, RH, RH_unc, dewPoint, dewPoint_unc);
 * The function calculateDewPoint uses the temperature tmp and the relative
 * humidity RH to calculate the dew point temperature, Td. The Td uncertainty
 * is calculated using the temperature and RH uncertainty given in tmp_unc 
 * and in RH_unc. The uncertainty returned should always be a positive number.
 * 
 * The function calculateDewPoint returns 0 if successful. If the temperature
 * is not realistic, it returns ERR_RH_INVALID_TMP. If the RH is not realistic,
 * the function returns ERR_RH_INVALID_RH.
 */
int calculateDewPoint(float tmp, float tmp_unc, float RH, float RH_unc, 
      float & dewPoint, float & dewPoint_unc) {
  // write your code here
  message("calculateDewPoint");
  message("tmp: ",tmp);
  message("RH: ",RH);
  message("RH_unc: ",RH_unc);
  message("tmp_unc: ",tmp_unc);
  return -1;
}

float dewPtBoegel(float tmp, float RH) {
  // Dew point calculation using the Boegel equation
  // write your code here
  message("dewPtBoegel");
  message("tmp: ",tmp);
  message("RH: ",RH);
  return 0.0;
}

float dewPtBuck(float tmp, float RH) {
  // Dewpoint calculation using the equations in Buck (JAMC, 1981)
  // write your code here
  message("dewPtBuck");
  message("tmp: ",tmp);
  message("RH: ",RH);
  return 0.0;
}

/**
 * err = checkRH()
 * The function checkRH check to make sure the Si7021 is online
 * and working. This is done by reading RH and temperature. If they 
 * both return errors, we can assume that there is a problem contacting
 * the Si7021 and return ERR_RH_NO_CONTACT.
 */
int checkRH() {
  // write your code here
  message("checkRH");
  return -1;
}


#endif
