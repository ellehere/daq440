#ifndef CLOCK_h
#define CLOCK_h

#include "RTClib.h"
#include "common.h"

//*****************************************************************************
// Global variables.
//*****************************************************************************

// real-time clock object
RTC_DS3231 RTC;

// clock.h error codes
#define ERR_RTC 0x300
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


//*****************************************************************************
// Global functions
//*****************************************************************************

/*
 * initClock
 * initialize the RTC and check the clock status
 * returns the status of checkClock()
 */
int initClock();
/*
 * getTimeString
 * timeStr must be a character array of length 9
 * char timeStr[9] = "00:00:00"
 */
int getTimeString(char timeStr[9]);
/*
 * getDateString
 * dateStr must be a character array of length 9
 * char timeStr[9] = "dd/MM/yy"
 */
int getDateString(char dateStr[9]);
/*
 * setRTCTime
 * sets the time on the RTC DS3231
 * Reads a string from serial.
 * String must be formatted as follows:
 *   "yyyyMMddhhmmss"
 */
int setRTCTime();
/*
 * checkClock
 * Check that the clock is working and has not lost power.
 * If the RTC has lost power, the time is probably incorrect.
 * Returns 0 if clock is working, ERR_RTC_LOST_POWER if
 * clock has lost power, and ERR_RTC_NO_CONNECTION if the
 * connection has been lost.
 */
int checkClock();
/*
 * isLeapYear
 * test for leap year
 */
boolean isLeapYear(int yr);


/*
 * err = initClock();
 * initialize the RTC and check the clock status
 * This function is already written
 */
int initClock() {
  RTC.begin();
  return checkClock();
}

/*
 * err = getTimeString(timeStr);
 * The function getTimeString checks the clock using the global RTC 
 * object. The time retrieved from the clock is used to construct a
 * time string, timeStr, with the format "14:20:03". This string should
 * should be 9 characters long with a string terminator at the end 
 * (ie. timeStr[8] = '\0';). If any of the values received for hour, 
 * minute, or second are unreasonable, the function should return the 
 * appropriate * error code to reflect which values are incorrect. 
 * For example:
 *   err = ERR_RTC_INVALID_MIN | ERR_RTC_INVALID_SEC;
 *   return err;
 * this would indicate that the minute and second are both unreasonable,
 * but that the hour is reasonable. If all three values are reasonable, 
 * getDateString should return 0;
 * The spaces in timeStr corresponding to an incorrect value should be
 * filled with '*'. For example, "14:**:**" for the error value given
 * above.
 * See the common.h function itoaLeadingZero() to convert numbers to
 * characters while keeping the leading zero.
 */
int getTimeString(char timeStr[9]) {
  message("getTimeString");
  return -1;
}

/*
 * err = getDateString(dateStr);
 * The function getDateString checks the clock using the global RTC 
 * object. The date retrieved from the clock is used to construct a
 * date string, dateStr, with the format "11/20/12". This string should
 * should be 9 characters long with a string terminator at the end 
 * (ie. dateStr[8] = '\0';). If any of the values received for day, 
 * month, or year are unreasonable, the function should return the 
 * appropriate error code to reflect which values are incorrect. 
 * For example:
 *   err = ERR_RTC_INVALID_DAY | ERR_RTC_INVALID_YEAR;
 *   return err;
 * this would indicate that the date and year are both unreasonable, but
 * that the month is reasonable. If all three values are reasonable, 
 * getDateString should return 0;
 * The spaces in dateStr corresponding to an incorrect value should be
 * filled with '*'. For example, "** /10/**" for the error value given
 * above.
 * See the common.h function itoaLeadingZero() to convert numbers to
 * characters while keeping the leading zero.
 */
int getDateString(char dateStr[9]) {
  message("getDateString");
  return -1;
}

/*
 * err = checkClock();
 * Check that the clock is working and has not lost power.
 * If the RTC has lost power, the time is probably incorrect.
 * Use the function RTC.lostPower(), and also check the time
 * twice, separated by a 1000 ms delay. If the seconds do not 
 * change, return ERR_RTC_NO_CONNECTION.
 * 
 * Returns 0 if clock is working, ERR_RTC_LOST_POWER if
 * clock has lost power (RTC.lostPower()), and 
 * ERR_RTC_NO_CONNECTION if the connection has been lost (seconds
 * do not change).
 */
int checkClock() {
  message("checkClock");
  return -1;
}

/*
 * err = setRTCTime(RTC_DS3231 RTC);
 * sets the time on the RTC DS3231
 * Reads a string from serial.
 * String must be formatted as follows:
 *   "yyyyMMddhhmmss"
 */
int setRTCTime() {
  int err;
  char input[15] = "";
  Serial.setTimeout(100);
  int nbytes = Serial.readBytes(input,14);
  message("received input: ",input);
  
  // Is the string the right length?
  if (nbytes != 14)
    return err = 0xFF;
    
  // Parse the input string.
  char yr[5],mo[3],day[3],hr[3],mins[3],sec[3];
  memccpy(yr,input,'\0',4); yr[4] = '\0';
  memccpy(mo,input+4,'\0',2); mo[2] = '\0';
  memccpy(day,input+6,'\0',2); day[2] = '\0';
  memccpy(hr,input+8,'\0',2); hr[2] = '\0';
  memccpy(mins,input+10,'\0',2); mins[2] = '\0';
  memccpy(sec,input+12,'\0',2); sec[2] = '\0';
  
  // Make sure the string contains only digits.
  for (int i = 0; i < 4; i++)
    if ((yr[i] < '0') || (yr[i] > '9')) err |= ERR_RTC_INVALID_YEAR;
  for (int i = 0; i < 2; i++)
    if ((mo[i] < '0') || (mo[i] > '9')) err |= ERR_RTC_INVALID_MONTH;
  for (int i = 0; i < 2; i++)
    if ((day[i] < '0') || (day[i] > '9')) err |= ERR_RTC_INVALID_DAY;
  for (int i = 0; i < 2; i++)
    if ((hr[i] < '0') || (hr[i] > '9')) err |= ERR_RTC_INVALID_HOUR;
  for (int i = 0; i < 2; i++)
    if ((mins[i] < '0') || (mins[i] > '9')) err |= ERR_RTC_INVALID_MIN;
  for (int i = 0; i < 2; i++)
    if ((sec[i] < '0') || (sec[i] > '9')) err |= ERR_RTC_INVALID_SEC;
    
  // Convert the strings to integers.
  int nYr = atoi(yr), nMo = atoi(mo), nDay = atoi(day);
  int nHr = atoi(hr), nMins = atoi(mins), nSec = atoi(sec);
  
  // Make sure the numbers are sensible.
  if ((nYr < 2000) || (nYr > 2050)) err |= ERR_RTC_INVALID_YEAR;
  if ((nMo < 1) || (nMo > 12)) err |= ERR_RTC_INVALID_MONTH;
  switch (nMo) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
      if ((nDay < 1) || (nDay > 31)) err |= ERR_RTC_INVALID_DAY;
      break;
    case 4: case 6: case 9: case 11:
      if ((nDay < 1) || (nDay > 30)) err |= ERR_RTC_INVALID_DAY;
      break;
    case 2:
      if (isLeapYear(nYr)) {
        if ((nDay < 1) || (nDay > 29)) err |= ERR_RTC_INVALID_DAY;
      }
      else {
        if ((nDay < 1) || (nDay > 28)) err |= ERR_RTC_INVALID_DAY;
      }
  }
  if ((nHr < 0) || (nHr > 23)) err |= ERR_RTC_INVALID_HOUR;
  if ((nMins < 0) || (nMins > 59)) err |= ERR_RTC_INVALID_MIN;
  if ((nSec < 0) || (nSec > 59)) err |= ERR_RTC_INVALID_SEC;

  if (err) return err;
  // Everything's OK, so set the clock.
  message("Setting RTC time:");
  RTC.adjust(DateTime(nYr, nMo, nDay, nHr, nMins, nSec));
  message("RTC status: ",RTC.lostPower());
  return 0;
}


// Test for leap year.
boolean isLeapYear(int yr) {
  if (((yr % 4 == 0) && (yr % 100 != 0)) || (yr % 400 == 0))
    return true;
  else
    return false;
}


#endif
