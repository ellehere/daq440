#ifndef STATS_h
#define STATS_h

/**
 * initStats
 */
void initStats(float storageArray[]) {
  // write your code here
  message("initStats");
  message(storageArray[0]);
}

/**
 * updateStats
 */
void updateStats(float x, float storageArray[]) {
  // write your code here
  message("updateStats");
  message(x);
}

/**
 * calcMean
 */
float calcMean(float storageArray[]) {
    // write your code here
  message("calcMean");
  message(storageArray[1]);
  return 1.0;
}

/**
 * calcStd
 */
float calcStd(float storageArray[]) {
// write your code here
  message("calcStd");
  message(storageArray[2]);
  return 1.0;
}

/**
 * calcSkewness
 */
float calcSkewness(float storageArray[]) {
  // write your code here
  message("calcSkewness");
  message(storageArray[3]);
  return 1.0;
}

/**
 * calcKurtosis
 */
float calcKurtosis(float storageArray[]) {
  // write your code here
  message("calcKurtosis");
  message(storageArray[4]);
  return 1.0;
}


#endif
