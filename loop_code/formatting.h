#ifndef FORMATTING_h
#define FORMATTING_h

#include <math.h>
#include "common.h"

//*****************************************************************************
// Variables and errors defined for formatting.h
//*****************************************************************************

// error constants for formatting.h
#define ERR_FMT_INVALID_TMP 0x1 // temperature value is invalid/impossible
#define ERR_FMT_INVALID_RH 0x2 // RH value is invalid/impossible
#define ERR_FMT_INVALID_PRS 0x4 // PRS value is invalid/impossible
#define ERR_FMT_STR_TOO_SMALL 0x8 // the output string is too short to fit the values
#define ERR_FMT_NAN_VALUE ERR_NAN_VALUE // one of the values is nan
#define ERR_FMT_INF_VALUE ERR_INF_VALUE // one of the values is inf/-inf

//*****************************************************************************
// Functions
//*****************************************************************************

// signatures of functions in this file
int formatValues(char output[], int outputSize, float values[], int arraySize);
int validateTmp(float & tmp);
int validateRH(float & RH);
int validatePrs(float & prs);

/*
 * err = formatValues(outputline,lineLength,outputValues,nValues);
 *
 * Line format:
 * R_th, T_th, T_th_unc, T_th_std, T_th_skew, T_th_kurt,
 *   RH, T_RH, Td, Td_unc, Td_std, Td_std, Td_skew, Td_kurt,
 *   Prs, Prs_unc, T_prs, P_SLP, Prs_std, Prs_skew, Prs_kurt
 * 21 floating-point numbers (on one line) separated by a comma
 * and a space (", ")
 *
 * Each value, x, should be 10 characters long with as many decimal
 * places as possible. Format as follows:
 *   > "#.########" to "#####.####" (for 1 <= x < 99999)
 *   > "-#.#######" to "-####.####" (for -1 >= x > -9999)
 *   > "#.####e+##" (for 0 < x < 1 OR 99999 < x)
 *   > "-#.###e+##" (for -1 < x < 0 OR x < -99999)
 *
 * The minimum length of any output string will be n*11+(n-1)*2+1, where n
 * is the number of floats in the array values.
 *
 * The output string for the line format given above will
 * be (21*10 + (21-1)*2 + 1 = 272) characters long.
 *
 * The variable output is a string/char array of length outputSize (ie. 
 * int outputSize = 272; char output[272];)
 * The variable values is an array of floating point numbers to be written
 * to output. This array has a length of arraySize (ie. int arraySize = 21;
 * float values[arraySize];)
 * 
 * See the functions in common.h to convert numbers to strings.
 */
int formatValues(char output[], int outputSize, float values[], int arraySize) {
  message("formatValues");
  message("output: ", output);
  message("outputSize: ", outputSize);
  message("values[0]: ", values[0]);
  message("arraySize: ", arraySize);
  return -1;
}

/*
 * err = validateTmp(tmp);
 * check that temperature (in deg C) makes sense
 * Set tmp to -99.0 and return ERR_FMT_INVALID_TMP if the temperature
 * is outside of a realistic range.
 * If temperature is reasonable, return zero and do not change tmp.
 */
int validateTmp(float & tmp) {
  message("validateTmp");
  message("tmp: ",tmp);
  return -1;
}

/*
 * err = validateRH(RH);
 * Check that RH (in %) makes sense.
 * Set RH to -99.0 and return ERR_FMT_INVALID_RH if the humidity
 * is outside of a realistic range.
 * If RH is reasonable, return zero and do not change RH.
 */
int validateRH(float & RH) {
  message("validateRH");
  message("RH: ",RH);
  return -1;
}

/*
 * err = validatePrs(prs);
 * Check that pressure (in Pa) makes sense.
 * Set prs to -99.0 and return ERR_FMT_INVALID_TMP if the pressure
 * is outside of a realistic range.
 * If pressure is reasonable, return zero and do not change prs.
 */
int validatePrs(float & prs) {
  message("validatePrs");
  message("prs: ",prs);
  return -1;
}

#endif
