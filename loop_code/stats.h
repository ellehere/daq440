#ifndef STATS_h
#define STATS_h

#include "common.h"

/*
 * stats.h
 * realtime statistics routines based on the white paper "Implementing
 * Algorithms to Measure Common Statistics" by S. McCrary (Berkeley 
 * Research Group, 2015)
 * url: https://www.thinkbrg.com/media/publication/720_McCrary_ImplementingAlgorithms_Whitepaper_20151119_WEB.pdf
 */

// stat.h error codes
#define ERR_STAT 0x800
#define ERR_STAT_NAN (ERR_STAT | ERR_NAN_VALUE) // nan encountered (0x8c0)
#define ERR_STAT_INF (ERR_STAT | ERR_INF_VALUE) // inf encountered (0x880)

//*****************************************************************************
// Global functions provided by stats.h
//*****************************************************************************


/**
 * initStats(storageArray);
 * This function accepts an array of five float (ie. float storageArray[5];), 
 * and sets the value of each element to zero.
 * This function must be called before calculating statistics.
 * Each quantity (temperature, RH, etc...) must have its own dedicated 
 * storageArray to keep track of the moments.
 */
void initStats(float storageArray[5]) {
  // write your code here
  message("initStats");
  message("storageArray[0]", storageArray[0]);
}

/**
 * updateStats(x, storageArray);
 * This function takes a new value, x, and adds it to the information kept
 * in storageArray. The array storageArray[5] contains the number of 
 * observations, n, the mean, and the second through fourth central moments.
 * Each time updateStats is called, it updates these values to reflect the
 * additional sample, x. The storageArray is to be used later by the calcMean, 
 * calcStd, (etc.) functions to calculate statistics regarding a specific set
 * of observations.
 * The algorithm for calculating online moments is given in McCrary (2015) in
 * addition to other sources (eg., Pebay et al. (2016)).
 * Each quantity (temperature, RH, etc...) must have its own dedicated 
 * storageArray to keep track of the moments.
 */
void updateStats(float x, float storageArray[5]) {
  // write your code here
  message("updateStats");
  message("x", x);
  message("storageArray[0]", storageArray[0]);
}

/**
 * mean = calcMean(storageArray);
 * This function returns the mean value calculated by
 * the function updateStats.
 */
float calcMean(float storageArray[5]) {
  // write your code here
  message("calcMean");
  message("storageArray[1]", storageArray[1]);
  return storageArray[1];
}

/**
 * variance = calcVariance(storageArray);
 * This function calculates and returns the unbiased sample variance
 * from the moments provided in storageArray.
 */
float calcVariance(float storageArray[]) {
  // write your code here
  message("calcVariance");
  message("storageArray[2]", storageArray[2]);
  return 0.0;
}

/**
 * skew = calcSkewness(storageArray);
 * This function calculates the unbiased sample skewness from the
 * moments provided in storageArray.
 */
float calcSkewness(float storageArray[]) {
  // write your code here
  message("calcSkewness");
  message("storageArray[3]", storageArray[3]);
  return 0.0;
}

/**
 * kurt = calcKurtosis(storageArray);
 * This function calculates and returns the unbiased sample kurtosis
 * using the moments provided in storageArray.
 */
float calcKurtosis(float storageArray[]) {
  // write your code here
  message("calcKurtosis");
  message("storageArray[4]", storageArray[4]);
  return 0.0;
}

int printStats(float storageArray[]) {
  Serial.print(calcMean(storageArray),5); Serial.print(", ");
  Serial.print(calcVariance(storageArray),5); Serial.print(", ");
  Serial.print(calcSkewness(storageArray),5); Serial.print(", ");
  Serial.println(calcKurtosis(storageArray),5);
  return 0;
}

int printMoments(float storageArray[]) {
  Serial.print(storageArray[0],5); Serial.print(", ");
  Serial.print(storageArray[1],5); Serial.print(", ");
  Serial.print(storageArray[2],5); Serial.print(", ");
  Serial.print(storageArray[3],5); Serial.print(", ");
  Serial.println(storageArray[4],5);
  return 0;
}

#endif
