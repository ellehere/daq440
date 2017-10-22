#include "common.h"
// all of the other codes
#include "calibration.h"
#include "clock.h"
#include "formatting.h"
#include "humidity.h"
#include "pressure.h"
#include "stats.h"
#include "temperature.h"

/**
 * In this file, write the main loop code to control timing and control the
 * data acquisition.
 * 
 * Refer to *.h files for function signatures and variable/constant names.
 * 
 */

// setup error codes (result to be placed in int setuperr before finishing)
#define ERR_SETUP 0x900
#define ERR_SETUP_SD (ERR_SETUP | (ERR_SD >> 8)) // error encountered in setup while initializing SD card
#define ERR_SETUP_CAL (ERR_SETUP | (ERR_CAL >> 8)) // error encountered in setup while obtaining the calibration
#define ERR_SETUP_RTC (ERR_SETUP | (ERR_RTC >> 8)) // error encountered in setup while initializing the RTC clock module
#define ERR_SETUP_RH (ERR_SETUP | (ERR_RH >> 8)) // error encountered in setup while initializing the RH sensor module
#define ERR_SETUP_PRS (ERR_SETUP | (ERR_PRS >> 8)) // error encountered in setup while initializing the pressure sensor module
#define ERR_SETUP_STAT (ERR_SETUP | (ERR_STAT >> 8)) // error encountered in setup while initializing the statistics storage arrays

#define ERR_LOOP 0xa00
// loop error codes (to communicate with blinkey)
#define ERR_LOOP_FATAL (ERR_LOOP | 0x1) // fatal error, no reason to proceed
#define ERR_LOOP_SD (ERR_LOOP_FATAL) // cannot write to SD (considered fatal)
#define ERR_LOOP_TMP (ERR_LOOP | 0x2) // error with temperature measurements 
#define ERR_LOOP_RH (ERR_LOOP | 0x4) // error with RH measurement
#define ERR_LOOP_PRS (ERR_LOOP | 0x8) // error with pressure measurement
#define ERR_LOOP_RTC (ERR_LOOP | 0x10) // error with RTC (clock module)
#define ERR_LOOP_CAL (ERR_LOOP | 0x20) // no calibration provided

int setuperr = 0;

//*****************************************************************************
//                 The Setup Function.
//*****************************************************************************
void setup() {
  // Initialize the serial port.
  Serial.begin(115200);
}



//*****************************************************************************
//                  The Loop Function.
//*****************************************************************************
void loop() {
  
}



