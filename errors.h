#ifndef ERRORS_H_
#define ERRORS_H_

#include "common.h"

/*
  This file contains all of the error codes used by all of the header files
 */

// function-specific error values
// these indicate approximately where any error originated
#define ERR_SD 0x100
#define ERR_CAL 0x200
#define ERR_RTC 0x300
#define ERR_FMT 0x400
#define ERR_RH 0x500
#define ERR_PRS 0x600
#define ERR_TEMP 0x700
#define ERR_STAT 0x800
#define ERR_SETUP 0x900
#define ERR_LOOP 0xa00

// error values for nan and inf/-inf
#define ERR_NAN_VALUE 0x80 // 0b1000 0000
#define ERR_INF_VALUE 0xc0 // 0b1100 0000

// -------------------------------------------------
// SDwrite.h error codes
#define ERR_SD_INIT_FAIL (ERR_SD | 0x1) // could not initialize the SD card
#define ERR_SD_FILENAME_ERROR (ERR_SD | 0x2) // error getting the filename (probably a clock error)
#define ERR_SD_FILE_OPEN (ERR_SD | 0x4) // cannot open the file
#define ERR_SD_WRITE_LENGTH (ERR_SD | 0x8) // the wrong number of bytes were written to the file
#define ERR_SD_NAN (ERR_SD | ERR_NAN_VALUE) // nan encountered (0x180)
#define ERR_SD_INF (ERR_SD | ERR_INF_VALUE) // inf encountered (0x1c0)

// -------------------------------------------------
// calibration.h error codes
// to be returned by loadCalibrationFile
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

// -------------------------------------------------
// clock.h error codes
#define ERR_RTC_INVALID_HOUR (ERR_RTC | 0x1)
#define ERR_RTC_INVALID_MIN (ERR_RTC | 0x2)
#define ERR_RTC_INVALID_SEC (ERR_RTC | 0x4)
#define ERR_RTC_INVALID_YEAR (ERR_RTC | 0x8)
#define ERR_RTC_INVALID_MONTH (ERR_RTC | 0x10)
#define ERR_RTC_INVALID_DAY (ERR_RTC | 0x20)
#define ERR_RTC_LOST_POWER (ERR_RTC | 0x40) // the clock lost power, time is probably incorrect
#define ERR_RTC_NO_CONNECTION (ERR_RTC | 0x3f) // cannot connect to the clock or clock is not updating time
#define ERR_RTC_NAN (ERR_RTC | ERR_NAN_VALUE) // nan encountered (0x380)
#define ERR_RTC_INF (ERR_RTC | ERR_INF_VALUE) // inf encountered (0x3c0)

// -------------------------------------------------
// formatting.h error codes
#define ERR_FMT_INVALID_TMP (ERR_FMT | 0x1) // temperature value is invalid/impossible
#define ERR_FMT_INVALID_RH (ERR_FMT | 0x2) // RH value is invalid/impossible
#define ERR_FMT_INVALID_PRS (ERR_FMT | 0x4) // PRS value is invalid/impossible
#define ERR_FMT_STR_TOO_SMALL (ERR_FMT | 0x8) // the output string is too short to fit the values
#define ERR_FMT_NAN_VALUE (ERR_FMT | ERR_NAN_VALUE) // one of the values is nan (0x480)
#define ERR_FMT_INF_VALUE (ERR_FMT | ERR_INF_VALUE) // one of the values is inf/-inf (0x4c0)

// -------------------------------------------------
// humidity.h error codes
#define ERR_RH_NO_CONTACT (ERR_RH | 0x1) // cannot contact RH sensor
#define ERR_RH_INVALID_RH (ERR_RH | 0x2) // RH value is invalid or outside of reasonable range
#define ERR_RH_INVALID_TMP (ERR_RH | 0x4) // temperature value is invalid or outside of reasonable range
#define ERR_RH_DP_ERR (ERR_RH | 0x8) // error with dewpoint calculation
#define ERR_RH_NAN (ERR_RH | ERR_NAN_VALUE) // nan encountered (0x580)
#define ERR_RH_INF (ERR_RH | ERR_INF_VALUE) // inf encountered (0x5c0)

// -------------------------------------------------
// pressure.h error codes 
// errors returned by BMP180.getError()
#define BMP_BUFFER_ERROR 0x1
#define BMP_CONNECTION_ERROR 0x2
#define BMP_BUSY_ERROR 0x3
#define BMP_OTHER_ERROR 0x4
// errors returned by pressure.h functions
#define ERR_PRS_BUFFER_ERROR (ERR_PRS | BMP_BUFFER_ERROR) // Data too long to fit in transmit buffer
#define ERR_PRS_CONNECTION_ERROR (ERR_PRS | BMP_CONNECTION_ERROR) // Received NACK on transmit of address
#define ERR_PRS_BMP_BUSY (ERR_PRS | BMP_BUSY_ERROR) // Received NACK on transmit of data
#define ERR_PRS_BMP_OTHER (ERR_PRS | BMP_OTHER_ERROR) // "Other error"
// errors defined by pressure.h
#define ERR_PRS_INVALID_PRS (ERR_PRS | 0x10) // The pressure received was invalid
#define ERR_PRS_INVALID_TMP (ERR_PRS | 0x20) // The temperature received was invalid
#define ERR_PRS_NAN (ERR_PRS | ERR_NAN_VALUE) // nan encountered (0x680)
#define ERR_PRS_INF (ERR_PRS | ERR_INF_VALUE) // inf encountered (0x6c0)

// -------------------------------------------------
// temperature.h error codes
#define ERR_TEMP_INVALID_RTH (ERR_TEMP | 0x1) // resistance value is invalid/impossible
#define ERR_TEMP_INVALID_TMP (ERR_TEMP | 0x2) // temperature value is invalid/impossible
#define ERR_TEMP_NAN (ERR_TEMP | ERR_NAN_VALUE) // nan encountered (0x7c0)
#define ERR_TEMP_INF (ERR_TEMP | ERR_INF_VALUE) // inf encountered (0x780)

// -------------------------------------------------
// stat.h error codes
#define ERR_STAT_NAN (ERR_STAT | ERR_NAN_VALUE) // nan encountered (0x8c0)
#define ERR_STAT_INF (ERR_STAT | ERR_INF_VALUE) // inf encountered (0x880)

// -------------------------------------------------
// setup error codes (result to be placed in int setuperr before finishing)
#define ERR_SETUP_SD (ERR_SETUP | (ERR_SD >> 8)) // error encountered in setup while initializing SD card
#define ERR_SETUP_CAL (ERR_SETUP | (ERR_CAL >> 8)) // error encountered in setup while obtaining the calibration
#define ERR_SETUP_RTC (ERR_SETUP | (ERR_RTC >> 8)) // error encountered in setup while initializing the RTC clock module
#define ERR_SETUP_RH (ERR_SETUP | (ERR_RH >> 8)) // error encountered in setup while initializing the RH sensor module
#define ERR_SETUP_PRS (ERR_SETUP | (ERR_PRS >> 8)) // error encountered in setup while initializing the pressure sensor module
#define ERR_SETUP_STAT (ERR_SETUP | (ERR_STAT >> 8)) // error encountered in setup while initializing the statistics storage arrays

// -------------------------------------------------
// loop error codes (to communicate with blinkey)
#define ERR_LOOP_NONE (ERR_LOOP | 0x0) // no error
#define ERR_LOOP_FATAL (ERR_LOOP | 0x1) // fatal error, no reason to proceed
#define ERR_LOOP_SD (ERR_LOOP_FATAL) // cannot write to SD (considered fatal)
#define ERR_LOOP_TMP (ERR_LOOP | 0x2) // error with temperature measurements 
#define ERR_LOOP_RH (ERR_LOOP | 0x4) // error with RH measurement
#define ERR_LOOP_PRS (ERR_LOOP | 0x8) // error with pressure measurement
#define ERR_LOOP_RTC (ERR_LOOP | 0x10) // error with RTC (clock module)
#define ERR_LOOP_CAL (ERR_LOOP | 0x20) // no calibration provided



#endif
