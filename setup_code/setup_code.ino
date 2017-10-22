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
 * In this file, write the main setup code to initialize the Arduino Uno
 * before it begins data acquisition
 * 
 * Refer to *.h files to determine what must be initialized and in what order.
 */

// setup error codes (result to be placed in int setuperr before finishing)
#define ERR_SETUP 0x900
#define ERR_SETUP_SD (ERR_SETUP | (ERR_SD >> 8)) // error encountered in setup while initializing SD card
#define ERR_SETUP_CAL (ERR_SETUP | (ERR_CAL >> 8)) // error encountered in setup while obtaining the calibration
#define ERR_SETUP_RTC (ERR_SETUP | (ERR_RTC >> 8)) // error encountered in setup while initializing the RTC clock module
#define ERR_SETUP_RH (ERR_SETUP | (ERR_RH >> 8)) // error encountered in setup while initializing the RH sensor module
#define ERR_SETUP_PRS (ERR_SETUP | (ERR_PRS >> 8)) // error encountered in setup while initializing the pressure sensor module
#define ERR_SETUP_STAT (ERR_SETUP | (ERR_STAT >> 8)) // error encountered in setup while initializing the statistics storage arrays

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



