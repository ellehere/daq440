#ifndef SDwrite_h
#define SDwrite_h

#include <SD.h>
#include "common.h"
#include "clock.h" // clock.h has global variable RTC_DS3231 RTC;

//*****************************************************************************
// Global variables.
//*****************************************************************************

// SD card is on pin 4
#define chipSelectSD 4

// SDwrite.h error codes
#define ERR_SD 0x100
#define ERR_SD_INIT_FAIL (ERR_SD | 0x1) // could not initialize the SD card
#define ERR_SD_FILENAME_ERROR (ERR_SD | 0x2) // error getting the filename (probably a clock error)
#define ERR_SD_FILE_OPEN (ERR_SD | 0x4) // cannot open the file
#define ERR_SD_WRITE_LENGTH (ERR_SD | 0x8) // the wrong number of bytes were written to the file
#define ERR_SD_NAN (ERR_SD | ERR_NAN_VALUE) // nan encountered (0x180)
#define ERR_SD_INF (ERR_SD | ERR_INF_VALUE) // inf encountered (0x1c0)


//*****************************************************************************
// Global functions
//*****************************************************************************

// function signatures
int initSDCard();
int checkSD();
int writeDataToSDFile(char dataString[], int dataStrLength);
int getSDFileName(char filename[13]);

//
// Function source
//

/**
 * err = writeDataToSDFile(dataString, dataStrLength);
 * This function takes a data string and the length of the string
 * and writes the string to the SD card file given by getSDFileName()
 * preceded by the current date and time.
 * This function assumes that the RTC clock RTC_DS3231 is connected
 * and set with the correct time. This function can call the clock 
 * functions getTimeString(str) and getDateString(str) to get the 
 * time and date.
 * The date, time, and data strings should be separated with ", " as
 * in the proper csv file format.
 * 
 * The variable dataString is a character array of length dataStrLength
 * holding the string of data to be written to the SD card. For example:
 *   int dataStrLength = 123;
 *   char dataString[dataStrLength];
 *   ... {fill dataString with data} ...
 *   err = writeDataToSDFile(dataString, dataStrLength)
 *   
 * If the write is successful, the function should return 0.
 * If the getSDFileName function fails to return a filename, 
 * writeDataToSDFile shall return ERR_SD_FILENAME_ERROR.
 * If the function cannot open the file on the SD card, it shall
 * return ERR_SD_FILE_OPEN.
 * If the number of bytes written is not as expected, the function
 * shall return ERR_SD_WRITE_LENGTH.
 */
int writeDataToSDFile(char dataString[], int dataStrLength) {
  // write your code here
  message("writeDataToSDFile");
  message("dataString: ", dataString);
  message("dataStrLength: ", dataStrLength);
  return -1;
}

/**
 * err checkSD()
 * returns ERR_SD_FILE_OPEN if it cannot open a file and 
 * returns ERR_SD_WRITE_LENGTH if writing a file did not work
 */
int checkSD() {
  // write your code here
  message("checkSD");
  return -1;
}

/**
 * int getSDFileName(filename)
 * Constructs char filename[13] based on the current date
 * filename format "yyyyMMdd.csv". Get the date from the clock.h
 * function getDateString() and copy it in to the filename string.
 * 
 * Returns 0 if successful.
 * Returns ERR_SD_FILENAME_ERROR if filename cannot be
 * constructed (probably because there is a clock error).
 */
int getSDFileName(char filename[13]) {
  // write your code here
  message("getSDFileName");
  message("filename: ", filename);
  return -1;
}



/**
 * err = initSDCard()
 * Initializes the SD card with SD.begin(chipSelectSD).
 * Returns 0 on success and ERR_SD_INIT_FAIL if not successful
 */
int initSDCard() {
  // write your code here
  message("initSDCard");
  return -1;
}



#endif
