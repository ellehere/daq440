#ifndef CALIBRATION_h
#define CALIBRATION_h

#include "common.h"

// calibration.h error codes
// to be returned by loadCalibrationFile
#define ERR_CAL 0x200
#define ERR_CAL_UNREADABLE (ERR_CAL | 0x7f) // cannot read the calibration from the file, file is not present, or SD card is not present
#define ERR_CAL_NO_T_A (ERR_CAL | 0x1) // missing TEMPERATURE_CAL_A
#define ERR_CAL_NO_T_B (ERR_CAL | 0x2) // missing TEMPERATURE_CAL_B
#define ERR_CAL_NO_T_C (ERR_CAL | 0x4) // missing TEMPERATURE_CAL_C
#define ERR_CAL_NO_T_A_UNC (ERR_CAL | 0x8) // missing TEMPERATURE_CAL_A_UNC
#define ERR_CAL_NO_T_B_UNC (ERR_CAL | 0x10) // missing TEMPERATURE_CAL_B_UNC
#define ERR_CAL_NO_T_C_UNC (ERR_CAL | 0x20) // missing TEMPERATURE_CAL_B_UNC
#define ERR_CAL_NO_ELEV (ERR_CAL | 0x40) // missing UNO_ELEVATION
#define ERR_CAL_NAN (ERR_CAL | ERR_NAN_VALUE) // nan encountered (0x280)
#define ERR_CAL_INF (ERR_CAL | ERR_INF_VALUE) // inf encountered (0x2c0)

/*
 * format of the calibration file is as follows:
 *  > one calibration value per line
 *  > two or three characters as a label at the beginning of the line
 *  > one space following the label characters
 *  > the calibration number is at the end of the line
 *  > example:
 * TA 1.4151e3
 * TB 5.132e-6
 * TC 6.1566e-3
 * TAU 1.5e2
 * TBU 1.5e2
 * TCU 1.5e2
 * EL 1346.2
 * 
 * calibration file name is "cal.dat" (see example)
 */
 
/**
 * loadCalibrationFile
 */
int loadCalibrationFile() {
  // write your code here
  message("loadCalibrationFile");
  return 1;
}

#endif
