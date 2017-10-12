#ifndef SDwrite_h
#define SDwrite_h

#include <SD.h>
#include "common.h"



/**
 * writeDataToSDFile
 */
int writeDataToSDFile(char dataString[]) {
  // write your code here
  message("writeDataToSDFile");
  message(dataString);
  return 1;
}

/**
 * checkSD
 */
int checkSD() {
  // write your code here
  message("checkSD");
  return 1;
}

/**
 * getSDFileName
 */
int getSDFileName(char filename[], int fnLength){
  // write your code here
  message("getSDFileName");
  message(fnLength);
  return 1;
}


/**
 * initSDCard
 */
int initSDCard() {
  // write your code here
  message("initSDCard");
  return 1;
}



#endif
