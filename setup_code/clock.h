#ifndef CLOCK_h
#define CLOCK_h

#include "RTClib.h"
#include "common.h"

//*****************************************************************************
// Global variables.
//*****************************************************************************

// real-time clock object
RTC_DS3231 RTC;

// Error codes for clock.h functions
#define ERR_RTC_INVALID_HOUR 0x1
#define ERR_RTC_INVALID_MIN 0x2
#define ERR_RTC_INVALID_SEC 0x4
#define ERR_RTC_INVALID_YEAR 0x8
#define ERR_RTC_INVALID_MONTH 0x10
#define ERR_RTC_INVALID_DAY 0x20
#define ERR_RTC_LOST_POWER 0x40 // the clock lost power, time is probably incorrect
#define ERR_RTC_NO_CONNECTION 0x81 // cannot connect to the clock or clock is not updating time

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
 * initClock
 * initialize the RTC and check the clock status
 */
int initClock() {
  RTC.begin();
  return checkClock();
}

/*
 * getTimeString
 * timeStr must be a character array of length 9
 * char timeStr[9] = "00:00:00"
 * the return value is an integer with values defined by the error flags
 * above
 */
int getTimeString(char timeStr[9]) {
  int err = 0;
  DateTime now = RTC.now(); // retrieve the time
  
  int hr = now.hour(), mins = now.minute(), sec = now.second();
  // clear the time string
  clearString(timeStr, 4);

  // check the time response and update err
  if (hr < 0 || hr > 23) err |= ERR_RTC_INVALID_HOUR;
  if (mins < 0 || mins > 59) err |= ERR_RTC_INVALID_MIN;
  if (sec < 0 || sec > 59) err |= ERR_RTC_INVALID_SEC;
  
  // convert the numerical time to string
  if (err & ERR_RTC_INVALID_HOUR) {
    memset(timeStr,'*',2);    
    message("invalid hour",hr);
  } else {
    itoaLeadingZero(hr, &(timeStr[0]), 2);
  }
  timeStr[2] = ':';
  if (err & ERR_RTC_INVALID_MIN) {
    memset(&(timeStr[3]),'*',2);
    message("invalid minutes",mins);
  } else {
    itoaLeadingZero(mins, &(timeStr[3]), 2);
  }
  timeStr[5] = ':';
  if (err & ERR_RTC_INVALID_SEC) {
    memset(&(timeStr[6]),'*',2);
    message("invalid seconds",sec);
  } else {
    itoaLeadingZero(sec, &(timeStr[6]), 2);
  }
    
  timeStr[8] = '\0';

  // return the error flag value
  return err;
}

/*
 * getDateString
 * dateStr should have the format "11/20/12", and should be 9 
 * characters long:
 *   char dateStr[9];
 */
int getDateString(char dateStr[9]) {
  int err = 0;
  DateTime now = RTC.now(); // retrieve the current time
  byte year = now.year() - 2000, month = now.month(), day = now.day();
  // check that the year, month, and day make sense
  if ((year < 0) || (year > 50)) err |= ERR_RTC_INVALID_YEAR;
  if ((month < 1) || (month > 12)) err |= ERR_RTC_INVALID_MONTH;
  switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
      if ((day < 1) || (day > 31)) err |= ERR_RTC_INVALID_DAY;
      break;
    case 4: case 6: case 9: case 11:
      if ((day < 1) || (day > 30)) err |= ERR_RTC_INVALID_DAY;
      break;
    case 2:
      if (isLeapYear(year)) {
        if ((day < 1) || (day > 29)) err |= ERR_RTC_INVALID_DAY;
      }
      else {
        if ((day < 1) || (day > 28)) err |= ERR_RTC_INVALID_DAY;
      }
  }

  // clear the string before writing the date
  clearString(dateStr, 9);

  if (err & ERR_RTC_INVALID_MONTH) {
    memset(dateStr,'*',2);    
    message("invalid month",month);
  } else {
    itoaLeadingZero(month, &(dateStr[0]), 2);
  }
  dateStr[2] = '/';
  if (err & ERR_RTC_INVALID_DAY) {
    memset((dateStr+3),'*',2);    
    message("invalid month",day);
  } else {
    itoaLeadingZero(day, &(dateStr[3]), 2);
  }
  dateStr[5] = '/';
  if (err & ERR_RTC_INVALID_YEAR) {
    memset(dateStr+6,'*',2);    
    message("invalid year",year);
  } else {
    itoaLeadingZero(year, &(dateStr[6]), 2);
  }
  dateStr[8] = '\0';

  return err;
}

/*
 * checkClock
 * Check that the clock is working and has not lost power.
 * If the RTC has lost power, the time is probably incorrect.
 * Returns 0 if clock is working, ERR_RTC_LOST_POWER if
 * clock has lost power, and ERR_RTC_NO_CONNECTION if the
 * connection has been lost.
 */
int checkClock() {
  int err = 0;
  DateTime now = RTC.now();
  int sec = now.second();
  delay(1000);
  if (RTC.lostPower()) {
    err |= ERR_RTC_LOST_POWER;
  }
  now = RTC.now();
  if (now.second() == sec) {
    err |= ERR_RTC_NO_CONNECTION;
  }
  
  RTC.writeSqwPinMode(DS3231_OFF);
  return err;
}

/*
 * setRTCTime(RTC_DS3231 RTC)
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
