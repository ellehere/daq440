//******************************************************************************
//  Log Si7021 Relative Humidity Sensor, BMP180 Pressure Sensor, and 
//    Thermistor to SD Card - 5 October 2017.
//******************************************************************************
#define nreadings 10  // Number of thermistor/battery voltage readings to average.
#define thermistor A1 // Thermistor ADC channel.
#define R 20000.0     // Fixed resistor value.
#define battery A0    // Battery voltage ADC channel.
#define LED 7         // LED pin number.

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"
#include "Adafruit_Si7021.h"
#include "SFE_BMP180.h"

const int chipSelectSD = 4;                   // Chip select for the SD card is connected to pin 4.
const char file[] = "log.csv";                // Data file name.
Adafruit_Si7021 RHsensor = Adafruit_Si7021(); // A data object to that helps us talk to the RH sensor.
RTC_DS3231 Clock;                             // A data object that helps us talk to the clock chip.
DateTime now;                                 // A structure to hold the current date and time.
SFE_BMP180 pressure;                          // Create an SFE_BMP180 object to talk to the pressure sensor.

// Data acquisition timing (emulates Oklahoma Mesonet).
unsigned long previousMillis1 = 0;
const unsigned int interval1 = 3000;      // 3 seconds (thermistor and RH readings).
unsigned long previousMillis2 = 0;
const unsigned int interval2 = 12000;     // 12 seconds (barometric pressure reading).
unsigned long previousMillis3 = 0;
const unsigned long interval3 = 300000;   // 300 seconds (for 5 minute averages).
unsigned long previousMillis4 = 0;
const unsigned long blinkInterval = 5000; // Blink LED every 5 seconds.
const unsigned int onTime = 100;

// Parameters for beta model of thermistor - from my calibration of 9/14/17.
//  Not necessarily correct for this particular thermistor, but close enough for now.
float R25 = 10058.82, beta = 3462.04;

// Variables for keeping track of 5 minute averages.
float RHavg = 0.0, Tavg = 0.0, RthAvg = 0.0;
float Pavg = 0.0, TPavg = 0.0;
unsigned int nValues1 = 0, nValues2 = 0;

//*****************************************************************************
//                 The Setup Function.
//*****************************************************************************
void setup() {
  // Initialize the serial port.
  Serial.begin(115200);
  // Initialize the LED pin.
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  // Initialize the SD card.  Print an error message and halt w/ rapidly blinking LED if initialization fails.
  if (!SD.begin(chipSelectSD)) {
    Serial.println("Could not initialize SD card");
    errorBlink();
  }
  // Initialize the relative humidity sensor.
  if (RHsensor.begin())
    Serial.println("Si7021 init success");
  else {
    Serial.println("Si7021 init failure\n\n");
    errorBlink();
  }
  // Initialize the I2C interface to talk to clock chip.
  Wire.begin();
  // Initialize the barometric pressure sensor (it is important to get calibration values stored on the device).
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    Serial.println("BMP180 init failure\n\n");
    errorBlink();
  }
  //  Initialize counters for timing data acquisition .
  previousMillis1 = millis();
  previousMillis2 = previousMillis1;
  previousMillis3 = previousMillis1;
  previousMillis4 = previousMillis1;
}

//*****************************************************************************
//                  The Loop Function.
//*****************************************************************************
void loop() {
  //
  unsigned long currentMillis = millis();
  //  Time to read the RH sensor and thermistor?
  if ((currentMillis - previousMillis1) >= interval1)   {
      updateAverages1();
      previousMillis1 = currentMillis;
  }
  //  Time to read the barometric pressure sensor?
  if ((currentMillis - previousMillis2) >= interval2) {
      updateAverages2();
      previousMillis2 = currentMillis;
  }
  //  Time to store/print 5 minute averages?
  if ((currentMillis - previousMillis3) >= interval3) {
      // Get the current date & time.
      now = Clock.now();
      String d = getDate(), t = getTime();  // Convert them to strings for printing.
      // Read the battery pack voltage.
      float volts = getVoltage();
      // Calculate temperature from the 5 minute average thermistor resistance.
      float Tth = betaModel(RthAvg);
      // Calculate the dew point using 5 min average of RH & T from thermistor.
      float Tdew = dewPt2(Tth,RHavg);
      // Print 5 minute averages to the serial port.
      Serial.print(d); Serial.print(", "); Serial.print(t); Serial.print(", ");
      Serial.print(RHavg, 2); Serial.print(", "); Serial.print(Tavg, 2); Serial.print(", ");
      Serial.print(Tdew, 2); Serial.print(", ");
      Serial.print(Pavg, 2); Serial.print(", "); Serial.print(TPavg, 2); Serial.print(", "); Serial.print(RthAvg, 2);
      Serial.print(", "); Serial.print(Tth, 2);
      Serial.print(", "); Serial.println(volts, 2);
      // Save the data to the SD card.
      File dataFile = SD.open(file, FILE_WRITE);
      if (dataFile) {
        dataFile.print(d); dataFile.print(", "); dataFile.print(t); dataFile.print(", ");
        dataFile.print(RHavg, 2); dataFile.print(", "); dataFile.print(Tavg, 2); dataFile.print(", ");
        dataFile.print(Tdew, 2); dataFile.print(", ");
        dataFile.print(Pavg, 2); dataFile.print(", "); dataFile.print(TPavg, 2); dataFile.print(", "); dataFile.print(RthAvg, 2);
        dataFile.print(", "); dataFile.print(Tth, 2);
        dataFile.print(", "); dataFile.println(volts, 2);
        dataFile.close();
      } else {
        Serial.print("Error opening output file - "); Serial.println(file);
        errorBlink();
      }
      // Reset the averages.
      resetAverages();
      previousMillis3 = currentMillis;
  }
  //  Time to blink the LED?
  if ((currentMillis - previousMillis4) >= blinkInterval) {
    digitalWrite(LED, HIGH);
    delay(onTime);
    digitalWrite(LED, LOW);
    previousMillis4 = currentMillis;
  }
  // Check for any serial input.
  if (Serial.available()) {
    char input = Serial.read();
    switch (input) {
      case 'S' :
        if (!setTime()) {
          Serial.println("Failed to set clock!");
          while (1);
        }
        Serial.flush();
        break;
      default :
        Serial.println("Unknown command");
    }
  }
}

// Returns the date read from the clock chip.
String getDate() {
  String date = "";
  byte year = now.year() - 2000, month = now.month(), day = now.day();
  date = (month < 10 ? "0" + String(month) : String(month)) + "/";
  date += (day < 10 ? "0" + String(day) : String(day)) + "/";
  date += (year < 10 ? "0"+String(year) : String(year));
  return date;
}

// Returns the time read from the clock chip.
String getTime() {
  String tyme = "";
  byte hr = now.hour(), mins = now.minute(), sec = now.second();
  tyme = (hr < 10 ? "0" + String(hr) : String(hr)) + ":";
  tyme += (mins < 10 ? "0" + String(mins) : String(mins)) + ":";
  tyme += (sec < 10 ? "0" + String(sec) : String(sec));
  return tyme;
}

// Validates input string & sets the RTC chip.
//  Input format: SYYYYMMDDHHMMSS
boolean setTime() {
  Serial.setTimeout(100);
  String input = Serial.readString();
  // Is the string the right length?
  if (input.length() != 14)
    return false;
  // Parse the input string.
  String yr = input.substring(0, 4), mo = input.substring(4, 6), day = input.substring(6, 8);
  String hr = input.substring(8, 10), mins = input.substring(10, 12), sec = input.substring(12);
  // Make sure the string contains only digits.
  for (int i = 0; i < yr.length(); i++)
    if ((yr.charAt(i) < '0') || (yr.charAt(i) > '9')) return false;
  for (int i = 0; i < mo.length(); i++)
    if ((mo.charAt(i) < '0') || (mo.charAt(i) > '9')) return false;
  for (int i = 0; i < day.length(); i++)
    if ((day.charAt(i) < '0') || (day.charAt(i) > '9')) return false;
  for (int i = 0; i < hr.length(); i++)
    if ((hr.charAt(i) < '0') || (hr.charAt(i) > '9')) return false;
  for (int i = 0; i < mins.length(); i++)
    if ((mins.charAt(i) < '0') || (mins.charAt(i) > '9')) return false;
  for (int i = 0; i < sec.length(); i++)
    if ((sec.charAt(i) < '0') || (sec.charAt(i) > '9')) return false;
  // Convert the strings to integers.
  int nYr = yr.toInt(), nMo = mo.toInt(), nDay = day.toInt();
  int nHr = hr.toInt(), nMins = mins.toInt(), nSec = sec.toInt();
  // Make sure the numbers are sensible.
  if ((nYr < 2000) || (nYr > 2050)) return false;
  if ((nMo < 1) || (nMo > 12)) return false;
  switch (nMo) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
      if ((nDay < 1) || (nDay > 31)) return false;
      break;
    case 4: case 6: case 9: case 11:
      if ((nDay < 1) || (nDay > 30)) return false;
      break;
    case 2:
      if (isLeapYear(nYr)) {
        if ((nDay < 1) || (nDay > 29)) return false;
      }
      else {
        if ((nDay < 1) || (nDay > 28)) return false;
      }
  }
  if ((nHr < 0) || (nHr > 23)) return false;
  if ((nMins < 0) || (nMins > 59)) return false;
  if ((nSec < 0) || (nSec > 59)) return false;
  // Everything's OK, so set the clock.
  Serial.println("Setting clock!");
  Clock.adjust(DateTime(nYr, nMo, nDay, nHr, nMins, nSec));
  return true;
}

// Test for leap year.
boolean isLeapYear(int yr) {
  if (((yr % 4 == 0) && (yr % 100 != 0)) || (yr % 400 == 0))
    return true;
  else
    return false;
}

// Two functions to calculate the dew point temperature.
//  Based on "Calculating the dew point" from https://en.wikipedia.org/wiki/Dew_point
float dewPt(float T, float RH) {
  const float a = 6.112, b = 18.678, c = 257.14, d = 234.5;

  float esat = a*exp((b-(T/d))*(T/(c+T)));
  float gamma = log((RH/100.0)*exp((b-(T/d))*(T/(c+T))));
  return (c * gamma)/(b - gamma);
}
//
float dewPt2(float T, float RH) {
  const float a[] = {6.1121, 6.1121};
  const float b[] = {17.368, 17.966};
  const float c[] = {238.88, 247.15};
  int range = 0;

  if (T < 0.0) range = 1;
  float esat = a[range] * exp((b[range] * T)/(c[range] + T));
  float e = (RH/100.0)*esat;
  return (c[range]*log(e/a[range]))/(b[range] - log(e/a[range]));
}

// Returns the resistance of the thermistor.
float readThermistor() {
  long sum = 0;
  for (int i = 0; i < nreadings; i++) {
    sum = sum + analogRead(thermistor);
  }
  float reading = sum/float(nreadings);
  return R * reading/(1023.0 - reading);
}

// Returns the battery voltage reading.
float getVoltage() {
  long sum = 0;
  for (int i = 0; i < nreadings; i++) {
    sum = sum + analogRead(battery);
  }
  float reading = sum/float(nreadings);
  return (reading/1023.0)*10.0;
}

// Catch errors - blink LED rapidly & halt.
void errorBlink() {
  while (1) {
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
  }
}

// Update 5 minute averages for the sensors that are read every 3 seconds.
void updateAverages1() {
  // Read the relative humidity sensor.
  float RH = RHsensor.readHumidity();
  float T = RHsensor.readTemperature();
  // Read the thermistor.
  float Rth = readThermistor();
  nValues1++;
  //
  if (nValues1 == 1) {
    RHavg = RH;
    Tavg = T;
    RthAvg = Rth;
  } else {
    float w1 = float(nValues1 - 1)/float(nValues1), w2 = 1.0/float(nValues1);
    RHavg = w1 * RHavg + w2 * RH;
    Tavg = w1 * Tavg + w2 * T;
    RthAvg = w1 * RthAvg + w2 * Rth;
  }
}

// Update 5 minute averages for the barometric pressure sensor.
void updateAverages2() {
  //  Variables to hold atmospheric pressure and temperature from the BMP180.
  double P, TP;
  // Read the barometric pressure sensor.
  char status = pressure.startTemperature();  // Have to do a temperature measurement first.
  delay(status);                              // Wait until the measurement is complete.
  status = pressure.getTemperature(TP);       // Read the temperature.
  status = pressure.startPressure(3);         // Start a pressure measurement.
  delay(status);                              // Wait.
  status = pressure.getPressure(P,TP);        // Read atmospheric pressure.
  nValues2++;
  //
  if (nValues2 == 1) {
    Pavg = P;
    TPavg = TP;
  } else {
    float w1 = float(nValues2 - 1)/float(nValues2), w2 = 1.0/float(nValues2);
    Pavg = w1 * Pavg + w2 * P;
    TPavg = w1 * TPavg + w2 * TP;
  }
}

// Reset variables for 5 minute averages.
void resetAverages() {
  RHavg = 0.0; Tavg = 0.0; Pavg = 0.0; TPavg = 0.0; RthAvg = 0.0; nValues1 = 0; nValues2 = 0;
}

// Solve beta model of thermistor for temperature.
float betaModel(float RR) {
  return (1.0/((1.0/298.15) + (1.0/beta)*log(RR/R25))) - 273.15;
}

