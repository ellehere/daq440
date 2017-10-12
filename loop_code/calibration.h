#ifndef CALIBRATION_h
#define CALIBRATION_h


float TEMPERATURE_CAL_A; float TEMPERATURE_CAL_A_UNC;
float TEMPERATURE_CAL_B; float TEMPERATURE_CAL_B_UNC;
float TEMPERATURE_CAL_C; float TEMPERATURE_CAL_C_UNC;
float UNO_ELEVATION;

/**
 * loadCalibrationFile
 */
int loadCalibrationFile() {
  // write your code here
  message("loadCalibrationFile");
  return 1;
}

#endif
