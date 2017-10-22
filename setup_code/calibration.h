#ifndef CALIBRATION_h
#define CALIBRATION_h

/*
 * error codes to be returned by loadCalibrationFile
 */
#define ERR_CAL_NO_FILE = -1; // calibration file is not present
#define ERR_CAL_NO_SD = -2; // SD card is not present
#define ERR_CAL_UNREADABLE = -3; // cannot read the calibration from the file
#define ERR_CAL_NO_T_A = 0x1; // missing TEMPERATURE_CAL_A
#define ERR_CAL_NO_T_B = 0x2; // missing TEMPERATURE_CAL_B
#define ERR_CAL_NO_T_C = 0x4; // missing TEMPERATURE_CAL_C
#define ERR_CAL_NO_T_A_UNC = 0x8; // missing TEMPERATURE_CAL_A_UNC
#define ERR_CAL_NO_T_B_UNC = 0x10; // missing TEMPERATURE_CAL_B_UNC
#define ERR_CAL_NO_T_C_UNC = 0x20; // missing TEMPERATURE_CAL_B_UNC
#define ERR_CAL_NO_ELEV = 0x40; // missing UNO_ELEVATION

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
