#ifndef COMMON_h
#define COMMON_h
#include <SD.h>
#include <errno.h>
#include <stdint.h>

/*
 * common.h
 * Common functions and variables used by multiple tasks.
 * This file is for global variables or constants and for basic
 * utility-type functions.
 *
 * Written by LEH, 10/2017
*/


//*****************************************************************************
// Global variables.
//*****************************************************************************

// thermistor pin
#define THERMISTOR_PIN A0

// thermistor calibration constants
float TEMPERATURE_CAL_A; float TEMPERATURE_CAL_A_UNC;
float TEMPERATURE_CAL_B; float TEMPERATURE_CAL_B_UNC;
float TEMPERATURE_CAL_C; float TEMPERATURE_CAL_C_UNC;

// elevation of the Arduino Uno, used for equivalent-SLP calculation
float UNO_ELEVATION;

// error values for nan and inf/-inf
#define ERR_NAN_VALUE 0xa0 // 0b1010 0000
#define ERR_INF_VALUE 0xc0 // 0b1100 0000

// message function control
#define MESSAGE_TO_SERIAL 0x0 // send messages to the serial terminal
#define MESSAGE_TO_FILE 0x1 // send messages to the file "MSGLOG00.LOG"
int MESSAGE_DESTINATION = MESSAGE_TO_SERIAL;


//*****************************************************************************
// Global functions
//*****************************************************************************

//
// Functions to print messages to serial output (to the computer).
//
 
/*
 * message([args])
 * This function takes one or more arguments and prints it out to the 
 * serial monitor, preceded by the time (in milliseconds) since the 
 * arduino was last reset.
 * Each message is formatted as {time in ms}: {msg}, for example:
 *    314123: Reading file from SD card.
 * The function message returns nothing.
 * The function can be called with one or more arguments, for example:
      message("This is a message"); // prints "{time}> This is a message"
      char example[] = "An example message";
      message(example," in two parts"); // prints "{time}> An example message in two parts"
      message(123); // prints "{time}> 123"
      int a = 123;
      message(a,HEX); // prints "{time}> 7b"
      message("An integer ",a); // prints "{time}> An integer 123"
      message("An integer 0x",a,HEX); // prints "{time}> An integer 0x7b"
      message("An integer 0b",a,BIN); // prints "{time}> An integer 0b1111011"
      message(12.313154); // prints "{time}> 12.313"
      float b = 12.313154;
      message(b); // prints "{time}> 12.313"
      message("A float ",b); // prints "{time}> A float 12.313"
      message("A float ",b,5); // prints "{time}> A float 12.31315" 
  */
void message(const char msg1[], const char msg2[] = "");

void message(long msg, const long base = 10);
void message(int msg, const int base = 10);

void message(double val, const int digits = 3);
void message(float val, const int digits = 3);

void message(const char msg1[], const char msg);

void message(const char msg1[], const double val, const int digits = 3);
void message(const char msg1[], const float val, const int digits = 3);

void message(const char msg1[], const long val, const long base = 10);
void message(const char msg1[], const int val, const int base = 10);

//
// Functions to read numbers off of an SD card.
//
 
/*
 * err = readFloatSD(file, x);
 * Reads the next float from an open file on an SD card, and puts the 
 * value in the variable x.
 * 
 * The variable err is an integer (ie. int err;).
 * The variable file is type File (ie. File file = SD.open("filename.csv");).
 * The variable x is a float (ie. float x;)
*/
int readFloatSD(File file, float & x);
int readIntSD(File file, int & x); // like readFloatSD but for integers.
int readLongSD(File file, long & x); // Like readFloatSD but for long integers.

/*
 * nchars = readLineSD(file, str, nstr);
 * reads a line of a file from the SD card.
 * readLineSD reads until the end of the line OR a maximum of nstr characters.
 * The string/character array str[] is expected to be at least nstr long.
 * 
 * The variable nchars is an integer (ie. int nchars;) and is set to the number
 * of characters that were read in put into the string str.
 * The variable file is type File (ie. File file = SD.open("filename.csv");).
 * The variable char is a character array (ie. char str[123];).
 * The variable nstr is an integer giving the length of str (ie. const int nstr = 123;).
*/
int readLineSD(File file, char str[], int nstr); 

//
// Functions to convert a numbers to text
//

// function to convert a floating point number to a string
/*
 * int parseFloatStr(char str[], float & x)
 * reads the float in string str.
 * returns 0 if successful and -1 if not
 *
 * str is a character array (ie. char str[50] = "15.231e-1";)
 * the value of the float read from the string is assigned to x
*/
int parseFloatStr(char str[], float & x);

// Function to convert an integer to a string with leading zeros
/*
 * err = itoaLeadingZero(val, str, spaces);
 * Converts the integer val to text, with enough leading zeros to fill 
 * the character spaces given by the variable spaces.
 * The return value err is set to zero if successful, and -1 if not 
 * successful. If the number of spaces is too small, the spaces are filled
 * with '*'.
 * 
 * The variable str is a character array (ie. char str[50] = "15.231e-1";) 
 * that starts with a floating point number.
 * The variable val is an integer or long that is set to the number read 
 * from the * string (ie. long x;).
 * 
 * Examples:
 *   char str[6];
 *   int err = itoaLeadingZero(441,str,4); // returns "0441"
 *   int err = itoaLeadingZero(4413,str,4); // returns "4413"
 *   int err = itoaLeadingZero(-4413,str,4); // returns "****"
 *   int err = itoaLeadingZero(-441,str,5); // returns "-0441"
 */
int itoaLeadingZero(long val, char * str, long spaces);

//
// Function to clear a string before it is used.
//

/*
 * clearString(char str[], int strSize)
 * The function clearString fills the string str with null 
 * characters (string terminators).
 * 
 * 
 * The string length is given by the integer strSize (ie. int strSize = 12;)
 * The string is passed to and from the function as the character array 
 * variable str (ie. char str[strSize];)
 */
void clearString(char str[], int strSize) {
  memset(str,'\0',strSize);
}

//
// Function to test if a float is nan or inf
//

/*
 * err = cleanNanInf(x);
 * Checks for nan, inf in the floating point number passed as variable x.
 * If x is nan, x is changed to -7777.0 and the int err is set to ERR_NAN_VALUE. 
 * If x is inf, x is changed to -8888.0 and the int err is set to ERR_INF_VALUE.
 * If the variable x is not nan or inf, err is set to 0.
 */
int cleanNanInf(float & x);



//*****************************************************************************
// Function code (the full source for all functions defined above).
//*****************************************************************************

/*
 * message(void * msg)
 * This function takes an argument and prints it out to the serial
 * monitor, preceded by the current time since the arduino was last
 * reset (in milliseconds).
 * The argument can be a string (character array), float, or int.
 * See documentation above for examples.
*/
// message a comment with two strings
void _messageSD(const char msg1[], const char msg2[] = "");
void message(const char msg1[], const char msg2[] = "") {
  if (MESSAGE_DESTINATION == MESSAGE_TO_SERIAL) {
    Serial.print(millis());
    Serial.print("> ");
    Serial.print(msg1);
    Serial.println(msg2);
  } else if (MESSAGE_DESTINATION == MESSAGE_TO_FILE) {
    _messageSD(msg1,msg2);
  }
}

// write message to SD card instead of serial output
// to be called by message
void _messageSD(const char msg1[], const char msg2[] = "") {
  const char messageFileName[] = "MSGLOG00.LOG";
  File msgFile = SD.open(messageFileName,FILE_WRITE);
  long ms = millis();
  // calculate the length of the string for millis
  int mslen = (ms == 0 ? 1 : 
              ((int)(log10(fabs(ms))+1) + (ms < 0 ? 1 : 0)));
  mslen = mslen + 3; // add space for "> "
  // allocate memory for string
  char * msgbuf = calloc(mslen,sizeof(char));
  if (msgbuf == ((void*) NULL)) return; // give up if malloc fails
  memset(msgbuf, '\0', mslen); // make sure string is all '\0'
  ltoa((long) ms, msgbuf, 10); // convert time to char array
  msgbuf[mslen-3] = '>'; msgbuf[mslen-2] = ' '; // Add "> "
  msgFile.write(msgbuf,mslen); // write the time tag to the file
  free(msgbuf); // free allocated memory
  // write the message strings
  msgFile.write(msg1,strlen(msg1));
  msgFile.write(msg2,strlen(msg2));
  msgFile.write('\n');
  msgFile.close();
}

// message a comment with a character
void message(const char msg1[], const char msg) {
  char ch_msg[2] = {msg, '\0'};
  message(msg1, ch_msg);
}

// message a comment with a int, and specify the base (default base 10)
void message(const char msg1[], const int val, const int base = 10) {
  char ch_msg[20];
  ltoa(val, ch_msg, base);
  message(msg1, ch_msg);
}

// message a comment with a long, and specify the base (default base 10)
void message(const char msg1[], const long val, const long base = 10) {
  char ch_msg[20];
  ltoa(val, ch_msg, base);
  message(msg1, ch_msg);
}

// message a comment with a floating point number, and specify precision
void message(const char msg1[], const float val, const int digits = 3) {
  char ch_msg[20];
  if (abs(val) > 1e5 | abs(val) < 0.1) {
    dtostre(val, ch_msg, digits, 1);
  } else {
    dtostrf(val, digits + 3, digits, ch_msg);
  }
  message(msg1, ch_msg);
}

// message a comment with a floating point number, and specify precision
void message(const char msg1[], const double val, const int digits = 3) {
  char ch_msg[20];
  if (abs(val) > 1e5 | abs(val) < 0.1) {
    dtostre(val, ch_msg, digits, 1);
  } else {
    dtostrf(val, digits + 3, digits, ch_msg);
  }
  message(msg1, ch_msg);
}

// message a floating point number, and specify precision
void message(float val, const int digits = 3) {
  char ch_msg[20];
  if (abs(val) > 1e5 | abs(val) < 0.1) {
    dtostre(val, ch_msg, digits, 1);
  } else {
    dtostrf(val, digits + 3, digits, ch_msg);
  }
  message(ch_msg);
}

// message a floating point number, and specify precision
void message(double val, const int digits = 3) {
  char ch_msg[20];
  if (abs(val) > 1e5 | abs(val) < 0.1) {
    dtostre(val, ch_msg, digits, 1);
  } else {
    dtostrf(val, digits + 3, digits, ch_msg);
  }
  message(ch_msg);
}

// message an integer or long
void message(int msg, const int base = 10) {
  char ch_msg[20];
  ltoa(msg, ch_msg, base);
  message(ch_msg);
}

// message an integer, and specify the base (default base 10)
void message(long msg, const long base = 10) {
  char ch_msg[20] = "";
  ultoa(msg, ch_msg, base);
  message(ch_msg);
}

/*
 * err = readIntSD(file, x);
 * reads the next int from an open file on an SD card.
 * returns 0 if successful and -1 if not.
 *
 * err is an integer; file is type File (ie. File file = SD.open("filename.csv");)
 * x is the int that was read from the file
*/
int readIntSD(File file, int & x) {
  if (file.available()) {
    long l = file.parseInt();
    if (l >= (1 << 15) && l <= ~(1 << 15)) {
      x = (int)l;
      return 0;
    }
    return -1;
  } else {
    x = 0.0;
    return -1;
  }
}

/*
 * err = readLongSD(file, x);
 * reads the next long from an open file on an SD card.
 * returns 0 if successful and -1 if not.
 *
 * err is an integer; file is type File (ie. File file = SD.open("filename.csv");)
 * x is the long that was read from the file
*/
int readLongSD(File file, long & x) {
  if (file.available()) {
    x = file.parseInt();
    return 0;
  } else {
    x = 0.0;
    return -1;
  }
}


// yn = isEOL(c);
// returns true (1) if the character c is a line terminator
bool isEOL(char c) {
  return c == '\n' | c == '\r';
}

// yn = isfloatchar(c);
// returns true (1) if the character c is allowed in floating-point numbers
bool isfloatchar(char c) {
  return isdigit(c) | c == '-' | c == '+' | c == '.' | c == 'e' | c == 'E';
}

/*
 * err = cleanNanInf(x);
 * Checks for nan, inf in the floating point number passed as variable x.
 * If x is nan, x is changed to -7777.0 and the int err is set to ERR_NAN_VALUE. 
 * If x is inf, x is changed to -8888.0 and the int err is set to ERR_INF_VALUE.
 * If the variable x is not nan or inf, err is set to 0.
 */
int cleanNanInf(float & x) {
  if (isinf(x)) {
    x = -7777.0;
    return ERR_NAN_VALUE;
  }
  if (isnan(x)) {
    x = -8888.0;
    return ERR_INF_VALUE;
  }
  return 0;
}

/*
 * err = readFloatSD(file, x);
 * reads the next float from an open file on an SD card.
 * returns 0 if successful and -1 if not.
 *
 * err is an integer; file is type File (ie. File file = SD.open("filename.csv");)
 * x is the float that was read from the file
 */
int readFloatSD(File file, float & x) {
  if (file.available()) {
    long pos = file.position();
    char buf[50] = "";
    char c = file.read();
    int ibp = 0;
    while (!isfloatchar(c)) {
      c = file.read();
    }
    do {
      if (isfloatchar(c)) {
        buf[ibp] = c;
      } else if (c == 'd' | c == 'D') {
        buf[ibp] = 'e';
      } else {
        break;
      }
      c = file.read();
      ibp++;
    } while (ibp < 50);

    file.seek(file.position() - 1);
    return parseFloatStr(buf, x);
  }
  return -1;
}

/*
 * nchars = readLineSD(file, str, nstr);
 * reads a line of a file from the SD card.
 * readLineSD reads until the end of the line OR a maximum of nstr characters.
 * The string/character array str[] is expected to be at least nstr long.
 * 
 * The variable nchars is an integer (ie. int nchars;) and is set to the number
 * of characters that were read in put into the string str.
 * The variable file is type File (ie. File file = SD.open("filename.csv");).
 * The variable char is a character array (ie. char str[123];).
 * The variable nstr is an integer giving the length of str (ie. const int nstr = 123;).
*/
int readLineSD(File file, char str[], int nstr) {
  int ic = 0;
  char c = file.read();

  do {
    str[ic] = c;
    ic = ic + 1;
    c = file.peek();
  } while (!isEOL(c) & ic < nstr);

  return ic;
}


/*
 * err = parseFloatStr(str,x)
 * Reads the float in the character string str and puts the value in x.
 * The return value err is set to 0 if successful.
 *
 * The variable str is a character array (ie. char str[50] = "15.231e-1";) 
 * that starts with a floating point number.
 * The variable x is a float that is set to the number read from the 
 * string (ie. float x;).
*/
int parseFloatStr(char str[], float & x) {
  x = strtod(str, (char **)0);
  return errno;
}

/*
 * err = itoaLeadingZero(val, str, spaces);
 * Converts the integer val to text, with enough leading zeros to fill 
 * the character spaces given by the variable spaces.
 * The return value err is set to zero if successful, and -1 if not 
 * successful. If the number of spaces is too small, the spaces are filled
 * with '*'.
 * 
 * The variable str is a character array (ie. char str[50] = "15.231e-1";) 
 * that starts with a floating point number.
 * The variable val is an integer or long that is set to the number read 
 * from the * string (ie. long x;).
 * 
 * Examples:
 *   char str[6];
 *   int err = itoaLeadingZero(441,str,4); // returns "0441"
 *   int err = itoaLeadingZero(4413,str,4); // returns "4413"
 *   int err = itoaLeadingZero(-4413,str,4); // returns "****"
 *   int err = itoaLeadingZero(-441,str,5); // returns "-0441"
 */
int itoaLeadingZero(int val, char * str, int spaces) 
  {return itoaLeadingZero((long)val,str,(long)spaces); }
int itoaLeadingZero(long val, char * str, long spaces) {
  long vc = val, sp = spaces;
  char * cpt;
  cpt = str;
  
  // if a negative number, it needs an extra space
  if (vc < 0) {
    if (vc > -pow(10,spaces-1)) {
      // it will fit
      *cpt = '-';
      vc = -vc;
      cpt = cpt+1;
    } else {
      // it won't fit
      memset(cpt,'*',spaces);
      return -1;
    }
  }
  
  // if the number is too large, fill spaces with '*'
  if (vc >= pow(10,spaces)) {
    memset(cpt,'*',spaces);
    return -1;
  }
  
  // check if leading 0's are necessary
  while (cpt-str < spaces) {
    if (vc < pow(10,spaces-(cpt-str)-1)) {
      *cpt = '0'; // fill space with a zero
      cpt = cpt+1;
    } else {
      break;
    }
  }
  
  // done filling spaces, now write the number
  itoa(vc, cpt, 10);
  return 0;
}

void testItoaLeadingZero() {
  int ic = 1,is = 1;
  char chy[50] = "";
  //  message(ic); message(is); message(pow(10,3)); message(chy);
  ic = 1;
  while (ic < pow(10,4)) {
    is = 1;
    while (is < 6) {
      message("number",ic);
      message("spaces",is);
      memset(chy,'\0',30);
      itoaLeadingZero(ic, chy, is); // positive number
      message(chy);
      memset(chy,'\0',50);
      itoaLeadingZero(-ic, chy, is); // negative number
      message(chy);
      is++;
    }
  ic = ic*10;
  }
}
#endif
