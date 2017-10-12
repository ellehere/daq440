/**************************************************************************/
/*!
    @file     Adafruit_Si7021.cpp
    @author   Limor Fried (Adafruit Industries)
    @license  BSD (see license.txt)

    This is a library for the Adafruit Si7021 breakout board
    ----> https://www.adafruit.com/products/3251

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!

    @section  HISTORY

    v1.0  - First release
*/
/**************************************************************************/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <stdio.h>
#include <math.h>
#include <Wire.h>
#include "Adafruit_Si7021.h"


/**************************************************************************/

Adafruit_Si7021::Adafruit_Si7021(void) {
  _i2caddr = SI7021_DEFAULT_ADDRESS;
  sernum_a = sernum_b = 0;
}

bool Adafruit_Si7021::begin(void) {
  Wire.begin();

  reset();
  if (readRegister8(SI7021_READRHT_REG_CMD) != 0x3A) return false;

  readSerialNumber();

  //Serial.println(sernum_a, HEX);
  //Serial.println(sernum_b, HEX);

  return true;
}

float Adafruit_Si7021::readHumidity(void) {
  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)SI7021_MEASRH_NOHOLD_CMD);
  Wire.endTransmission(false);
  delay(25);

  Wire.requestFrom(_i2caddr, 3);
  uint16_t hum = Wire.read();
  hum <<= 8;
  hum |= Wire.read();
  uint8_t chxsum = Wire.read();

  float humidity = hum;
  humidity *= 125;
  humidity /= 65536;
  humidity -= 6;

  return humidity;
}

float Adafruit_Si7021::readTemperature(void) {
  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)SI7021_MEASTEMP_NOHOLD_CMD);
  Wire.endTransmission(false);
  delay(25);

  Wire.requestFrom(_i2caddr, 3);
  uint16_t temp = Wire.read();
  temp <<= 8;
  temp |= Wire.read();
  uint8_t chxsum = Wire.read();

  float temperature = temp;
  temperature *= 175.72;
  temperature /= 65536;
  temperature -= 46.85;

  return temperature;
}

void Adafruit_Si7021::reset(void) {
  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)SI7021_RESET_CMD);
  Wire.endTransmission();
  delay(50);
}

void Adafruit_Si7021::readSerialNumber(void) {
  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)SI7021_ID1_CMD>>8);
  Wire.write((uint8_t)SI7021_ID1_CMD&0xFF);
  Wire.endTransmission();

  Wire.requestFrom(_i2caddr, 8);
  sernum_a = Wire.read();
  Wire.read();
  sernum_a <<= 8;
  sernum_a |= Wire.read();
  Wire.read();
  sernum_a <<= 8;
  sernum_a |= Wire.read();
  Wire.read();
  sernum_a <<= 8;
  sernum_a |= Wire.read();
  Wire.read();

  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)SI7021_ID2_CMD>>8);
  Wire.write((uint8_t)SI7021_ID2_CMD&0xFF);
  Wire.endTransmission();

  Wire.requestFrom(_i2caddr, 8);
  sernum_b = Wire.read();
  Wire.read();
  sernum_b <<= 8;
  sernum_b |= Wire.read();
  Wire.read();
  sernum_b <<= 8;
  sernum_b |= Wire.read();
  Wire.read();
  sernum_b <<= 8;
  sernum_b |= Wire.read();
  Wire.read();
}

/*******************************************************************/

void Adafruit_Si7021::writeRegister8(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)reg);
  Wire.write((uint8_t)value);
  Wire.endTransmission();

  //Serial.print("Wrote $"); Serial.print(reg, HEX); Serial.print(": 0x"); Serial.println(value, HEX);
}

uint8_t Adafruit_Si7021::readRegister8(uint8_t reg) {
  uint8_t value;
  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)reg);
  Wire.endTransmission(false);

  Wire.requestFrom(_i2caddr, 1);
  value = Wire.read();

  //Serial.print("Read $"); Serial.print(reg, HEX); Serial.print(": 0x"); Serial.println(value, HEX);
  return value;
}

uint16_t Adafruit_Si7021::readRegister16(uint8_t reg) {
  uint16_t value;
  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)reg);
  Wire.endTransmission();

  Wire.requestFrom(_i2caddr, 2);
  value = Wire.read();
  value <<= 8;
  value |= Wire.read();

  //Serial.print("Read $"); Serial.print(reg, HEX); Serial.print(": 0x"); Serial.println(value, HEX);
  return value;
}



/*******************************************************************************
* LowPower Library
* Version: 1.60
* Date: 01-04-2016
* Author: Lim Phang Moh
* Company: Rocket Scream Electronics
* Website: www.rocketscream.com
*
* This is a lightweight low power library for Arduino.
*
* This library is licensed under Creative Commons Attribution-ShareAlike 3.0 
* Unported License.
*
* Revision  Description
* ========  ===========
* 1.60      Added support for ATmega256RFR2. Contributed by Rodmg. 
* 1.50      Fixed compiler optimization (Arduino IDE 1.6.x branch) on BOD enable
*           function that causes the function to be over optimized.
* 1.40		Added support for ATSAMD21G18A.
* 			Library format compliant with Arduino IDE 1.5.x.
* 1.30		Added support for ATMega168, ATMega2560, ATMega1280 & ATMega32U4.
*			Tested to work with Arduino IDE 1.0.1 - 1.0.4.
* 1.20		Remove typo error in idle method for checking whether Timer 0 was 
*			turned off.
*			Remove dependecy on WProgram.h which is not required.
*			Tested to work with Arduino IDE 1.0.
* 1.10		Added #ifndef for sleep_bod_disable() for compatibility with future
*			Arduino IDE release.
* 1.00      Initial public release.
*******************************************************************************/
#if defined (__AVR__)
	#include <avr/sleep.h>
	#include <avr/wdt.h>
	#include <avr/power.h>
	#include <avr/interrupt.h>
#elif defined (__arm__)

#else
	#error "Processor architecture is not supported."
#endif

#include "LowPower.h"

#if defined (__AVR__)
// Only Pico Power devices can change BOD settings through software
#if defined __AVR_ATmega328P__
#ifndef sleep_bod_disable
#define sleep_bod_disable() 										\
do { 																\
  unsigned char tempreg; 													\
  __asm__ __volatile__("in %[tempreg], %[mcucr]" "\n\t" 			\
                       "ori %[tempreg], %[bods_bodse]" "\n\t" 		\
                       "out %[mcucr], %[tempreg]" "\n\t" 			\
                       "andi %[tempreg], %[not_bodse]" "\n\t" 		\
                       "out %[mcucr], %[tempreg]" 					\
                       : [tempreg] "=&d" (tempreg) 					\
                       : [mcucr] "I" _SFR_IO_ADDR(MCUCR), 			\
                         [bods_bodse] "i" (_BV(BODS) | _BV(BODSE)), \
                         [not_bodse] "i" (~_BV(BODSE))); 			\
} while (0)
#endif
#endif

#define	lowPowerBodOn(mode)	\
do { 						\
      set_sleep_mode(mode); \
      cli();				\
      sleep_enable();		\
      sei();				\
      sleep_cpu();			\
      sleep_disable();		\
      sei();				\
} while (0);

// Only Pico Power devices can change BOD settings through software
#if defined __AVR_ATmega328P__
#define	lowPowerBodOff(mode)\
do { 						\
      set_sleep_mode(mode); \
      cli();				\
      sleep_enable();		\
			sleep_bod_disable(); \
      sei();				\
      sleep_cpu();			\
      sleep_disable();		\
      sei();				\
} while (0);
#endif

// Some macros is still missing from AVR GCC distribution for ATmega32U4
#if defined __AVR_ATmega32U4__
	// Timer 4 PRR bit is currently not defined in iom32u4.h 
	#ifndef PRTIM4
		#define PRTIM4 4
	#endif

	// Timer 4 power reduction macro is not defined currently in power.h
	#ifndef power_timer4_disable
		#define power_timer4_disable()	(PRR1 |= (uint8_t)(1 << PRTIM4)) 									
	#endif

	#ifndef power_timer4_enable
		#define power_timer4_enable()		(PRR1 &= (uint8_t)~(1 << PRTIM4))							
	#endif
#endif
  
/*******************************************************************************
* Name: idle
* Description: Putting ATmega328P/168 into idle state. Please make sure you 
*			         understand the implication and result of disabling module.
*
* Argument  	Description
* =========  	===========
* 1. period   Duration of low power mode. Use SLEEP_FOREVER to use other wake
*				up resource:
*				(a) SLEEP_15MS - 15 ms sleep
*				(b) SLEEP_30MS - 30 ms sleep
*				(c) SLEEP_60MS - 60 ms sleep
*				(d) SLEEP_120MS - 120 ms sleep
*				(e) SLEEP_250MS - 250 ms sleep
*				(f) SLEEP_500MS - 500 ms sleep
*				(g) SLEEP_1S - 1 s sleep
*				(h) SLEEP_2S - 2 s sleep
*				(i) SLEEP_4S - 4 s sleep
*				(j) SLEEP_8S - 8 s sleep
*				(k) SLEEP_FOREVER - Sleep without waking up through WDT
*
* 2. adc		ADC module disable control:
*				(a) ADC_OFF - Turn off ADC module
*				(b) ADC_ON - Leave ADC module in its default state
*
* 3. timer2		Timer 2 module disable control:
*				(a) TIMER2_OFF - Turn off Timer 2 module
*				(b) TIMER2_ON - Leave Timer 2 module in its default state
*
* 4. timer1		Timer 1 module disable control:
*				(a) TIMER1_OFF - Turn off Timer 1 module
*				(b) TIMER1_ON - Leave Timer 1 module in its default state
*
* 5. timer0		Timer 0 module disable control:
*				(a) TIMER0_OFF - Turn off Timer 0 module
*				(b) TIMER0_ON - Leave Timer 0 module in its default state
*
* 6. spi		SPI module disable control:
*				(a) SPI_OFF - Turn off SPI module
*				(b) SPI_ON - Leave SPI module in its default state
*
* 7. usart0		USART0 module disable control:
*				(a) USART0_OFF - Turn off USART0  module
*				(b) USART0_ON - Leave USART0 module in its default state
*
* 8. twi		TWI module disable control:
*				(a) TWI_OFF - Turn off TWI module
*				(b) TWI_ON - Leave TWI module in its default state
*
*******************************************************************************/
#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega168__)
void	LowPowerClass::idle(period_t period, adc_t adc, timer2_t timer2, 
							timer1_t timer1, timer0_t timer0,
							spi_t spi, usart0_t usart0,	twi_t twi)
{
	// Temporary clock source variable 
	unsigned char clockSource = 0;
	
	if (timer2 == TIMER2_OFF)
	{
		if (TCCR2B & CS22) clockSource |= (1 << CS22);
		if (TCCR2B & CS21) clockSource |= (1 << CS21);
		if (TCCR2B & CS20) clockSource |= (1 << CS20);
	
		// Remove the clock source to shutdown Timer2
		TCCR2B &= ~(1 << CS22);
		TCCR2B &= ~(1 << CS21);
		TCCR2B &= ~(1 << CS20);
		
		power_timer2_disable();
	}
	
	if (adc == ADC_OFF)	
	{
		ADCSRA &= ~(1 << ADEN);
		power_adc_disable();
	}
	
	if (timer1 == TIMER1_OFF)	power_timer1_disable();	
	if (timer0 == TIMER0_OFF)	power_timer0_disable();	
	if (spi == SPI_OFF)			power_spi_disable();
	if (usart0 == USART0_OFF)	power_usart0_disable();
	if (twi == TWI_OFF)			power_twi_disable();
	
	if (period != SLEEP_FOREVER)
	{
		wdt_enable(period);
		WDTCSR |= (1 << WDIE);	
	}
	
	lowPowerBodOn(SLEEP_MODE_IDLE);
	
	if (adc == ADC_OFF)
	{
		power_adc_enable();
		ADCSRA |= (1 << ADEN);
	}
	
	if (timer2 == TIMER2_OFF)
	{
		if (clockSource & CS22) TCCR2B |= (1 << CS22);
		if (clockSource & CS21) TCCR2B |= (1 << CS21);
		if (clockSource & CS20) TCCR2B |= (1 << CS20);
		
		power_timer2_enable();
	}
	
	if (timer1 == TIMER1_OFF)	power_timer1_enable();	
	if (timer0 == TIMER0_OFF)	power_timer0_enable();	
	if (spi == SPI_OFF)			power_spi_enable();
	if (usart0 == USART0_OFF)	power_usart0_enable();
	if (twi == TWI_OFF)			power_twi_enable();
}
#endif

/*******************************************************************************
* Name: idle
* Description: Putting ATmega32U4 into idle state. Please make sure you 
*			   understand the implication and result of disabling module.
*			   Take note that Timer 2 is not available and USART0 is replaced 
* 			   with USART1 on ATmega32U4.
*
* Argument  	Description
* =========  	===========
* 1. period     Duration of low power mode. Use SLEEP_FOREVER to use other wake
*				up resource:
*				(a) SLEEP_15MS - 15 ms sleep
*				(b) SLEEP_30MS - 30 ms sleep
*				(c) SLEEP_60MS - 60 ms sleep
*				(d) SLEEP_120MS - 120 ms sleep
*				(e) SLEEP_250MS - 250 ms sleep
*				(f) SLEEP_500MS - 500 ms sleep
*				(g) SLEEP_1S - 1 s sleep
*				(h) SLEEP_2S - 2 s sleep
*				(i) SLEEP_4S - 4 s sleep
*				(j) SLEEP_8S - 8 s sleep
*				(k) SLEEP_FOREVER - Sleep without waking up through WDT
*
* 2. adc		ADC module disable control:
*				(a) ADC_OFF - Turn off ADC module
*				(b) ADC_ON - Leave ADC module in its default state
*
* 3. timer4		Timer 4 module disable control:
*				(a) TIMER4_OFF - Turn off Timer 4 module
*				(b) TIMER4_ON - Leave Timer 4 module in its default state
*
* 4. timer3		Timer 3 module disable control:
*				(a) TIMER3_OFF - Turn off Timer 3 module
*				(b) TIMER3_ON - Leave Timer 3 module in its default state
*
* 5. timer1		Timer 1 module disable control:
*				(a) TIMER1_OFF - Turn off Timer 1 module
*				(b) TIMER1_ON - Leave Timer 1 module in its default state
*
* 6. timer0		Timer 0 module disable control:
*				(a) TIMER0_OFF - Turn off Timer 0 module
*				(b) TIMER0_ON - Leave Timer 0 module in its default state
*
* 7. spi		SPI module disable control:
*				(a) SPI_OFF - Turn off SPI module
*				(b) SPI_ON - Leave SPI module in its default state
*
* 8. usart1		USART1 module disable control:
*				(a) USART1_OFF - Turn off USART1  module
*				(b) USART1_ON - Leave USART1 module in its default state
*
* 9. twi		TWI module disable control:
*				(a) TWI_OFF - Turn off TWI module
*				(b) TWI_ON - Leave TWI module in its default state
*
* 10.usb		USB module disable control:
*				(a) USB_OFF - Turn off USB module
*				(b) USB_ON - Leave USB module in its default state
*******************************************************************************/
#if defined __AVR_ATmega32U4__
void	LowPowerClass::idle(period_t period, adc_t adc, 
							timer4_t timer4, timer3_t timer3, 
							timer1_t timer1, timer0_t timer0,
							spi_t spi, usart1_t usart1,	twi_t twi, usb_t usb)
{
	if (adc == ADC_OFF)	
	{
		ADCSRA &= ~(1 << ADEN);
		power_adc_disable();
	}

	if (timer4 == TIMER4_OFF)	power_timer4_disable();	
	if (timer3 == TIMER3_OFF)	power_timer3_disable();		
	if (timer1 == TIMER1_OFF)	power_timer1_disable();	
	if (timer0 == TIMER0_OFF)	power_timer0_disable();	
	if (spi == SPI_OFF)			power_spi_disable();
	if (usart1 == USART1_OFF)	power_usart1_disable();
	if (twi == TWI_OFF)			power_twi_disable();
	if (usb == USB_OFF)			power_usb_disable();
	
	if (period != SLEEP_FOREVER)
	{
		wdt_enable(period);
		WDTCSR |= (1 << WDIE);	
	}
	
	lowPowerBodOn(SLEEP_MODE_IDLE);
	
	if (adc == ADC_OFF)
	{
		power_adc_enable();
		ADCSRA |= (1 << ADEN);
	}

	if (timer4 == TIMER4_OFF)	power_timer4_enable();	
	if (timer3 == TIMER3_OFF)	power_timer3_enable();	
	if (timer1 == TIMER1_OFF)	power_timer1_enable();	
	if (timer0 == TIMER0_OFF)	power_timer0_enable();	
	if (spi == SPI_OFF)			power_spi_enable();
	if (usart1 == USART1_OFF)	power_usart1_enable();
	if (twi == TWI_OFF)			power_twi_enable();
	if (usb == USB_OFF)			power_usb_enable();
}
#endif

/*******************************************************************************
* Name: idle
* Description: Putting ATmega2560 & ATmega1280 into idle state. Please make sure 
*			   you understand the implication and result of disabling module.
*			   Take note that extra Timer 5, 4, 3 compared to an ATmega328P/168.
*			   Also take note that extra USART 3, 2, 1 compared to an 
*			   ATmega328P/168.
*
* Argument  	Description
* =========  	===========
* 1. period     Duration of low power mode. Use SLEEP_FOREVER to use other wake
*				up resource:
*				(a) SLEEP_15MS - 15 ms sleep
*				(b) SLEEP_30MS - 30 ms sleep
*				(c) SLEEP_60MS - 60 ms sleep
*				(d) SLEEP_120MS - 120 ms sleep
*				(e) SLEEP_250MS - 250 ms sleep
*				(f) SLEEP_500MS - 500 ms sleep
*				(g) SLEEP_1S - 1 s sleep
*				(h) SLEEP_2S - 2 s sleep
*				(i) SLEEP_4S - 4 s sleep
*				(j) SLEEP_8S - 8 s sleep
*				(k) SLEEP_FOREVER - Sleep without waking up through WDT
*
* 2. adc		ADC module disable control:
*				(a) ADC_OFF - Turn off ADC module
*				(b) ADC_ON - Leave ADC module in its default state
*
* 3. timer5		Timer 5 module disable control:
*				(a) TIMER5_OFF - Turn off Timer 5 module
*				(b) TIMER5_ON - Leave Timer 5 module in its default state
*
* 4. timer4		Timer 4 module disable control:
*				(a) TIMER4_OFF - Turn off Timer 4 module
*				(b) TIMER4_ON - Leave Timer 4 module in its default state
*
* 5. timer3		Timer 3 module disable control:
*				(a) TIMER3_OFF - Turn off Timer 3 module
*				(b) TIMER3_ON - Leave Timer 3 module in its default state
*
* 6. timer2		Timer 2 module disable control:
*				(a) TIMER2_OFF - Turn off Timer 2 module
*				(b) TIMER2_ON - Leave Timer 2 module in its default state
*
* 7. timer1		Timer 1 module disable control:
*				(a) TIMER1_OFF - Turn off Timer 1 module
*				(b) TIMER1_ON - Leave Timer 1 module in its default state
*
* 8. timer0		Timer 0 module disable control:
*				(a) TIMER0_OFF - Turn off Timer 0 module
*				(b) TIMER0_ON - Leave Timer 0 module in its default state
*
* 9. spi		SPI module disable control:
*				(a) SPI_OFF - Turn off SPI module
*				(b) SPI_ON - Leave SPI module in its default state
*
* 10.usart3		USART3 module disable control:
*				(a) USART3_OFF - Turn off USART3  module
*				(b) USART3_ON - Leave USART3 module in its default state
*
* 11.usart2		USART2 module disable control:
*				(a) USART2_OFF - Turn off USART2  module
*				(b) USART2_ON - Leave USART2 module in its default state
*
* 12.usart1		USART1 module disable control:
*				(a) USART1_OFF - Turn off USART1  module
*				(b) USART1_ON - Leave USART1 module in its default state
*
* 13.usart0		USART0 module disable control:
*				(a) USART0_OFF - Turn off USART0  module
*				(b) USART0_ON - Leave USART0 module in its default state
*
* 14.twi		TWI module disable control:
*				(a) TWI_OFF - Turn off TWI module
*				(b) TWI_ON - Leave TWI module in its default state
*
*******************************************************************************/
#if defined (__AVR_ATmega2560__) || defined (__AVR_ATmega1280__)
void	LowPowerClass::idle(period_t period, adc_t adc, timer5_t timer5, 
					        timer4_t timer4, timer3_t timer3, timer2_t timer2, 
							timer1_t timer1, timer0_t timer0, spi_t spi, 
							usart3_t usart3, usart2_t usart2, usart1_t usart1, 
			                usart0_t usart0, twi_t twi)
{
	// Temporary clock source variable 
	unsigned char clockSource = 0;
	
	if (timer2 == TIMER2_OFF)
	{
		if (TCCR2B & CS22) clockSource |= (1 << CS22);
		if (TCCR2B & CS21) clockSource |= (1 << CS21);
		if (TCCR2B & CS20) clockSource |= (1 << CS20);
	
		// Remove the clock source to shutdown Timer2
		TCCR2B &= ~(1 << CS22);
		TCCR2B &= ~(1 << CS21);
		TCCR2B &= ~(1 << CS20);
		
		power_timer2_disable();
	}
	
	if (adc == ADC_OFF)	
	{
		ADCSRA &= ~(1 << ADEN);
		power_adc_disable();
	}
	
	if (timer5 == TIMER5_OFF)	power_timer5_disable();	
	if (timer4 == TIMER4_OFF)	power_timer4_disable();	
	if (timer3 == TIMER3_OFF)	power_timer3_disable();	
	if (timer1 == TIMER1_OFF)	power_timer1_disable();	
	if (timer0 == TIMER0_OFF)	power_timer0_disable();	
	if (spi == SPI_OFF)		    power_spi_disable();
	if (usart3 == USART3_OFF)	power_usart3_disable();
	if (usart2 == USART2_OFF)	power_usart2_disable();
	if (usart1 == USART1_OFF)	power_usart1_disable();
	if (usart0 == USART0_OFF)	power_usart0_disable();
	if (twi == TWI_OFF)			power_twi_disable();
	
	if (period != SLEEP_FOREVER)
	{
		wdt_enable(period);
		WDTCSR |= (1 << WDIE);	
	}
	
	lowPowerBodOn(SLEEP_MODE_IDLE);
	
	if (adc == ADC_OFF)
	{
		power_adc_enable();
		ADCSRA |= (1 << ADEN);
	}
	
	if (timer2 == TIMER2_OFF)
	{
		if (clockSource & CS22) TCCR2B |= (1 << CS22);
		if (clockSource & CS21) TCCR2B |= (1 << CS21);
		if (clockSource & CS20) TCCR2B |= (1 << CS20);
		
		power_timer2_enable();
	}

	if (timer5 == TIMER5_OFF)	power_timer5_enable();	
	if (timer4 == TIMER4_OFF)	power_timer4_enable();		
	if (timer3 == TIMER3_OFF)	power_timer3_enable();	
	if (timer1 == TIMER1_OFF)	power_timer1_enable();	
	if (timer0 == TIMER0_OFF)	power_timer0_enable();	
	if (spi == SPI_OFF)			power_spi_enable();
	if (usart3 == USART3_OFF)	power_usart3_enable();
	if (usart2 == USART2_OFF)	power_usart2_enable();
	if (usart1 == USART1_OFF)	power_usart1_enable();
	if (usart0 == USART0_OFF)	power_usart0_enable();
	if (twi == TWI_OFF)			power_twi_enable();
}
#endif

/*******************************************************************************
* Name: idle
* Description: Putting ATmega256RFR2 into idle state. Please make sure 
*			   you understand the implication and result of disabling module.
*			   Take note that extra Timer 5, 4, 3 compared to an ATmega328P/168.
*			   Also take note that extra USART 1 compared to an 
*			   ATmega328P/168.
*
* Argument  	Description
* =========  	===========
* 1. period     Duration of low power mode. Use SLEEP_FOREVER to use other wake
*				up resource:
*				(a) SLEEP_15MS - 15 ms sleep
*				(b) SLEEP_30MS - 30 ms sleep
*				(c) SLEEP_60MS - 60 ms sleep
*				(d) SLEEP_120MS - 120 ms sleep
*				(e) SLEEP_250MS - 250 ms sleep
*				(f) SLEEP_500MS - 500 ms sleep
*				(g) SLEEP_1S - 1 s sleep
*				(h) SLEEP_2S - 2 s sleep
*				(i) SLEEP_4S - 4 s sleep
*				(j) SLEEP_8S - 8 s sleep
*				(k) SLEEP_FOREVER - Sleep without waking up through WDT
*
* 2. adc		ADC module disable control:
*				(a) ADC_OFF - Turn off ADC module
*				(b) ADC_ON - Leave ADC module in its default state
*
* 3. timer5		Timer 5 module disable control:
*				(a) TIMER5_OFF - Turn off Timer 5 module
*				(b) TIMER5_ON - Leave Timer 5 module in its default state
*
* 4. timer4		Timer 4 module disable control:
*				(a) TIMER4_OFF - Turn off Timer 4 module
*				(b) TIMER4_ON - Leave Timer 4 module in its default state
*
* 5. timer3		Timer 3 module disable control:
*				(a) TIMER3_OFF - Turn off Timer 3 module
*				(b) TIMER3_ON - Leave Timer 3 module in its default state
*
* 6. timer2		Timer 2 module disable control:
*				(a) TIMER2_OFF - Turn off Timer 2 module
*				(b) TIMER2_ON - Leave Timer 2 module in its default state
*
* 7. timer1		Timer 1 module disable control:
*				(a) TIMER1_OFF - Turn off Timer 1 module
*				(b) TIMER1_ON - Leave Timer 1 module in its default state
*
* 8. timer0		Timer 0 module disable control:
*				(a) TIMER0_OFF - Turn off Timer 0 module
*				(b) TIMER0_ON - Leave Timer 0 module in its default state
*
* 9. spi		SPI module disable control:
*				(a) SPI_OFF - Turn off SPI module
*				(b) SPI_ON - Leave SPI module in its default state
*
* 10.usart1		USART1 module disable control:
*				(a) USART1_OFF - Turn off USART1  module
*				(b) USART1_ON - Leave USART1 module in its default state
*
* 11.usart0		USART0 module disable control:
*				(a) USART0_OFF - Turn off USART0  module
*				(b) USART0_ON - Leave USART0 module in its default state
*
* 12.twi		TWI module disable control:
*				(a) TWI_OFF - Turn off TWI module
*				(b) TWI_ON - Leave TWI module in its default state
*
*******************************************************************************/
#if defined (__AVR_ATmega256RFR2__)
void	LowPowerClass::idle(period_t period, adc_t adc, timer5_t timer5, 
					                timer4_t timer4, timer3_t timer3, timer2_t timer2, 
													timer1_t timer1, timer0_t timer0, spi_t spi, 
													usart1_t usart1, 
			                    usart0_t usart0, twi_t twi)
{
	// Temporary clock source variable 
	unsigned char clockSource = 0;
	
	if (timer2 == TIMER2_OFF)
	{
		if (TCCR2B & CS22) clockSource |= (1 << CS22);
		if (TCCR2B & CS21) clockSource |= (1 << CS21);
		if (TCCR2B & CS20) clockSource |= (1 << CS20);
	
		// Remove the clock source to shutdown Timer2
		TCCR2B &= ~(1 << CS22);
		TCCR2B &= ~(1 << CS21);
		TCCR2B &= ~(1 << CS20);
		
		power_timer2_disable();
	}
	
	if (adc == ADC_OFF)	
	{
		ADCSRA &= ~(1 << ADEN);
		power_adc_disable();
	}
	
	if (timer5 == TIMER5_OFF)	power_timer5_disable();	
	if (timer4 == TIMER4_OFF)	power_timer4_disable();	
	if (timer3 == TIMER3_OFF)	power_timer3_disable();	
	if (timer1 == TIMER1_OFF)	power_timer1_disable();	
	if (timer0 == TIMER0_OFF)	power_timer0_disable();	
	if (spi == SPI_OFF)			  power_spi_disable();
	if (usart1 == USART1_OFF)	power_usart1_disable();
	if (usart0 == USART0_OFF)	power_usart0_disable();
	if (twi == TWI_OFF)			  power_twi_disable();
	
	if (period != SLEEP_FOREVER)
	{
		wdt_enable(period);
		WDTCSR |= (1 << WDIE);	
	}
	
	lowPowerBodOn(SLEEP_MODE_IDLE);
	
	if (adc == ADC_OFF)
	{
		power_adc_enable();
		ADCSRA |= (1 << ADEN);
	}
	
	if (timer2 == TIMER2_OFF)
	{
		if (clockSource & CS22) TCCR2B |= (1 << CS22);
		if (clockSource & CS21) TCCR2B |= (1 << CS21);
		if (clockSource & CS20) TCCR2B |= (1 << CS20);
		
		power_timer2_enable();
	}

	if (timer5 == TIMER5_OFF)	power_timer5_enable();	
	if (timer4 == TIMER4_OFF)	power_timer4_enable();		
	if (timer3 == TIMER3_OFF)	power_timer3_enable();	
	if (timer1 == TIMER1_OFF)	power_timer1_enable();	
	if (timer0 == TIMER0_OFF)	power_timer0_enable();	
	if (spi == SPI_OFF)			  power_spi_enable();
	if (usart1 == USART1_OFF)	power_usart1_enable();
	if (usart0 == USART0_OFF)	power_usart0_enable();
	if (twi == TWI_OFF)			  power_twi_enable();
}
#endif


/*******************************************************************************
* Name: adcNoiseReduction
* Description: Putting microcontroller into ADC noise reduction state. This is
*			   a very useful state when using the ADC to achieve best and low 
*              noise signal.
*
* Argument  	Description
* =========  	===========
* 1. period     Duration of low power mode. Use SLEEP_FOREVER to use other wake
*				up resource:
*				(a) SLEEP_15MS - 15 ms sleep
*				(b) SLEEP_30MS - 30 ms sleep
*				(c) SLEEP_60MS - 60 ms sleep
*				(d) SLEEP_120MS - 120 ms sleep
*				(e) SLEEP_250MS - 250 ms sleep
*				(f) SLEEP_500MS - 500 ms sleep
*				(g) SLEEP_1S - 1 s sleep
*				(h) SLEEP_2S - 2 s sleep
*				(i) SLEEP_4S - 4 s sleep
*				(j) SLEEP_8S - 8 s sleep
*				(k) SLEEP_FOREVER - Sleep without waking up through WDT
*
* 2. adc		ADC module disable control. Turning off the ADC module is
*				basically removing the purpose of this low power mode.
*				(a) ADC_OFF - Turn off ADC module
*				(b) ADC_ON - Leave ADC module in its default state
*
* 3. timer2		Timer 2 module disable control:
*				(a) TIMER2_OFF - Turn off Timer 2 module
*				(b) TIMER2_ON - Leave Timer 2 module in its default state
*
*******************************************************************************/
void	LowPowerClass::adcNoiseReduction(period_t period, adc_t adc, 
										 timer2_t timer2)
{
	// Temporary clock source variable 
	unsigned char clockSource = 0;
	
	#if !defined(__AVR_ATmega32U4__)
	if (timer2 == TIMER2_OFF)
	{
		if (TCCR2B & CS22) clockSource |= (1 << CS22);
		if (TCCR2B & CS21) clockSource |= (1 << CS21);
		if (TCCR2B & CS20) clockSource |= (1 << CS20);
	
		// Remove the clock source to shutdown Timer2
		TCCR2B &= ~(1 << CS22);
		TCCR2B &= ~(1 << CS21);
		TCCR2B &= ~(1 << CS20);
	}
	#endif
	
	if (adc == ADC_OFF)	ADCSRA &= ~(1 << ADEN);
	
	if (period != SLEEP_FOREVER)
	{
		wdt_enable(period);
		WDTCSR |= (1 << WDIE);	
	}
	
	lowPowerBodOn(SLEEP_MODE_ADC);
	
	if (adc == ADC_OFF) ADCSRA |= (1 << ADEN);
	
	#if !defined(__AVR_ATmega32U4__)
	if (timer2 == TIMER2_OFF)
	{
		if (clockSource & CS22) TCCR2B |= (1 << CS22);
		if (clockSource & CS21) TCCR2B |= (1 << CS21);
		if (clockSource & CS20) TCCR2B |= (1 << CS20);
		
	}
	#endif
}

/*******************************************************************************
* Name: powerDown
* Description: Putting microcontroller into power down state. This is
*			   the lowest current consumption state. Use this together with 
*			   external pin interrupt to wake up through external event 
*			   triggering (example: RTC clockout pin, SD card detect pin).
*
* Argument  	Description
* =========  	===========
* 1. period     Duration of low power mode. Use SLEEP_FOREVER to use other wake
*				up resource:
*				(a) SLEEP_15MS - 15 ms sleep
*				(b) SLEEP_30MS - 30 ms sleep
*				(c) SLEEP_60MS - 60 ms sleep
*				(d) SLEEP_120MS - 120 ms sleep
*				(e) SLEEP_250MS - 250 ms sleep
*				(f) SLEEP_500MS - 500 ms sleep
*				(g) SLEEP_1S - 1 s sleep
*				(h) SLEEP_2S - 2 s sleep
*				(i) SLEEP_4S - 4 s sleep
*				(j) SLEEP_8S - 8 s sleep
*				(k) SLEEP_FOREVER - Sleep without waking up through WDT
*
* 2. adc		ADC module disable control. Turning off the ADC module is
*				basically removing the purpose of this low power mode.
*				(a) ADC_OFF - Turn off ADC module
*				(b) ADC_ON - Leave ADC module in its default state
*
* 3. bod		Brown Out Detector (BOD) module disable control:
*				(a) BOD_OFF - Turn off BOD module
*				(b) BOD_ON - Leave BOD module in its default state
*
*******************************************************************************/
void	LowPowerClass::powerDown(period_t period, adc_t adc, bod_t bod)
{
	if (adc == ADC_OFF)	ADCSRA &= ~(1 << ADEN);
	
	if (period != SLEEP_FOREVER)
	{
		wdt_enable(period);
		WDTCSR |= (1 << WDIE);	
	}
	if (bod == BOD_OFF)	
	{
		#if defined __AVR_ATmega328P__
			lowPowerBodOff(SLEEP_MODE_PWR_DOWN);
		#else
			lowPowerBodOn(SLEEP_MODE_PWR_DOWN);
		#endif
	}
	else	
	{
		lowPowerBodOn(SLEEP_MODE_PWR_DOWN);
	}
	
	if (adc == ADC_OFF) ADCSRA |= (1 << ADEN);
}

/*******************************************************************************
* Name: powerSave
* Description: Putting microcontroller into power save state. This is
*			   the lowest current consumption state after power down. 
*			   Use this state together with an external 32.768 kHz crystal (but
*			   8/16 MHz crystal/resonator need to be removed) to provide an
*			   asynchronous clock source to Timer 2. Please take note that 
*			   Timer 2 is also used by the Arduino core for PWM operation. 
*			   Please refer to wiring.c for explanation. Removal of the external
*			   8/16 MHz crystal/resonator requires the microcontroller to run
*			   on its internal RC oscillator which is not so accurate for time
*			   critical operation.
*
* Argument  	Description
* =========  	===========
* 1. period   Duration of low power mode. Use SLEEP_FOREVER to use other wake
*				up resource:
*				(a) SLEEP_15MS - 15 ms sleep
*				(b) SLEEP_30MS - 30 ms sleep
*				(c) SLEEP_60MS - 60 ms sleep
*				(d) SLEEP_120MS - 120 ms sleep
*				(e) SLEEP_250MS - 250 ms sleep
*				(f) SLEEP_500MS - 500 ms sleep
*				(g) SLEEP_1S - 1 s sleep
*				(h) SLEEP_2S - 2 s sleep
*				(i) SLEEP_4S - 4 s sleep
*				(j) SLEEP_8S - 8 s sleep
*				(k) SLEEP_FOREVER - Sleep without waking up through WDT
*
* 2. adc		ADC module disable control. Turning off the ADC module is
*				basically removing the purpose of this low power mode.
*				(a) ADC_OFF - Turn off ADC module
*				(b) ADC_ON - Leave ADC module in its default state
*
* 3. bod		Brown Out Detector (BOD) module disable control:
*				(a) BOD_OFF - Turn off BOD module
*				(b) BOD_ON - Leave BOD module in its default state
*
* 4. timer2		Timer 2 module disable control:
*				(a) TIMER2_OFF - Turn off Timer 2 module
*				(b) TIMER2_ON - Leave Timer 2 module in its default state
*
*******************************************************************************/
void	LowPowerClass::powerSave(period_t period, adc_t adc, bod_t bod, 
							     timer2_t timer2)
{
	// Temporary clock source variable 
	unsigned char clockSource = 0;

	#if !defined(__AVR_ATmega32U4__)
	if (timer2 == TIMER2_OFF)
	{
		if (TCCR2B & CS22) clockSource |= (1 << CS22);
		if (TCCR2B & CS21) clockSource |= (1 << CS21);
		if (TCCR2B & CS20) clockSource |= (1 << CS20);
	
		// Remove the clock source to shutdown Timer2
		TCCR2B &= ~(1 << CS22);
		TCCR2B &= ~(1 << CS21);
		TCCR2B &= ~(1 << CS20);
	}
	#endif
	
	if (adc == ADC_OFF)	ADCSRA &= ~(1 << ADEN);
	
	if (period != SLEEP_FOREVER)
	{
		wdt_enable(period);
		WDTCSR |= (1 << WDIE);	
	}
	
	if (bod == BOD_OFF)	
	{
		#if defined __AVR_ATmega328P__
			lowPowerBodOff(SLEEP_MODE_PWR_SAVE);
		#else
			lowPowerBodOn(SLEEP_MODE_PWR_SAVE);
		#endif
	}
	else
	{
		lowPowerBodOn(SLEEP_MODE_PWR_SAVE);
	}
	
	if (adc == ADC_OFF) ADCSRA |= (1 << ADEN);
	
	#if !defined(__AVR_ATmega32U4__)
	if (timer2 == TIMER2_OFF)
	{
		if (clockSource & CS22) TCCR2B |= (1 << CS22);
		if (clockSource & CS21) TCCR2B |= (1 << CS21);
		if (clockSource & CS20) TCCR2B |= (1 << CS20);
	}
	#endif
}

/*******************************************************************************
* Name: powerStandby
* Description: Putting microcontroller into power standby state. 
*
* Argument  	Description
* =========  	===========
* 1. period     Duration of low power mode. Use SLEEP_FOREVER to use other wake
*				up resource:
*				(a) SLEEP_15MS - 15 ms sleep
*				(b) SLEEP_30MS - 30 ms sleep
*				(c) SLEEP_60MS - 60 ms sleep
*				(d) SLEEP_120MS - 120 ms sleep
*				(e) SLEEP_250MS - 250 ms sleep
*				(f) SLEEP_500MS - 500 ms sleep
*				(g) SLEEP_1S - 1 s sleep
*				(h) SLEEP_2S - 2 s sleep
*				(i) SLEEP_4S - 4 s sleep
*				(j) SLEEP_8S - 8 s sleep
*				(k) SLEEP_FOREVER - Sleep without waking up through WDT
*
* 2. adc		ADC module disable control. Turning off the ADC module is
*				basically removing the purpose of this low power mode.
*				(a) ADC_OFF - Turn off ADC module
*				(b) ADC_ON - Leave ADC module in its default state
*
* 3. bod		Brown Out Detector (BOD) module disable control:
*				(a) BOD_OFF - Turn off BOD module
*				(b) BOD_ON - Leave BOD module in its default state
*
*******************************************************************************/
void	LowPowerClass::powerStandby(period_t period, adc_t adc, bod_t bod)
{
	if (adc == ADC_OFF)	ADCSRA &= ~(1 << ADEN);
	
	if (period != SLEEP_FOREVER)
	{
		wdt_enable(period);
		WDTCSR |= (1 << WDIE);	
	}
	
	if (bod == BOD_OFF)	
	{
		#if defined __AVR_ATmega328P__
			lowPowerBodOff(SLEEP_MODE_STANDBY);
		#else
			lowPowerBodOn(SLEEP_MODE_STANDBY);
		#endif
	}
	else
	{
		lowPowerBodOn(SLEEP_MODE_STANDBY);
	}
	
	if (adc == ADC_OFF) ADCSRA |= (1 << ADEN);
}

/*******************************************************************************
* Name: powerExtStandby
* Description: Putting microcontroller into power extended standby state. This 
*			   is different from the power standby state as it has the 
*			   capability to run Timer 2 asynchronously.
*
* Argument  	Description
* =========  	===========
* 1. period     Duration of low power mode. Use SLEEP_FOREVER to use other wake
*				up resource:
*				(a) SLEEP_15MS - 15 ms sleep
*				(b) SLEEP_30MS - 30 ms sleep
*				(c) SLEEP_60MS - 60 ms sleep
*				(d) SLEEP_120MS - 120 ms sleep
*				(e) SLEEP_250MS - 250 ms sleep
*				(f) SLEEP_500MS - 500 ms sleep
*				(g) SLEEP_1S - 1 s sleep
*				(h) SLEEP_2S - 2 s sleep
*				(i) SLEEP_4S - 4 s sleep
*				(j) SLEEP_8S - 8 s sleep
*				(k) SLEEP_FOREVER - Sleep without waking up through WDT
*
* 2. adc		ADC module disable control.
*				(a) ADC_OFF - Turn off ADC module
*				(b) ADC_ON - Leave ADC module in its default state
*
* 3. bod		Brown Out Detector (BOD) module disable control:
*				(a) BOD_OFF - Turn off BOD module
*				(b) BOD_ON - Leave BOD module in its default state
*
* 4. timer2		Timer 2 module disable control:
*				(a) TIMER2_OFF - Turn off Timer 2 module
*				(b) TIMER2_ON - Leave Timer 2 module in its default state
*
*******************************************************************************/
void	LowPowerClass::powerExtStandby(period_t period, adc_t adc, bod_t bod, 
									   timer2_t timer2)
{
	// Temporary clock source variable 
	unsigned char clockSource = 0;
	
	#if !defined(__AVR_ATmega32U4__)
	if (timer2 == TIMER2_OFF)
	{
		if (TCCR2B & CS22) clockSource |= (1 << CS22);
		if (TCCR2B & CS21) clockSource |= (1 << CS21);
		if (TCCR2B & CS20) clockSource |= (1 << CS20);
	
		// Remove the clock source to shutdown Timer2
		TCCR2B &= ~(1 << CS22);
		TCCR2B &= ~(1 << CS21);
		TCCR2B &= ~(1 << CS20);
	}
	#endif
	
	if (adc == ADC_OFF)	ADCSRA &= ~(1 << ADEN);
	
	if (period != SLEEP_FOREVER)
	{
		wdt_enable(period);
		WDTCSR |= (1 << WDIE);	
	}
	if (bod == BOD_OFF)	
	{
		#if defined __AVR_ATmega328P__
			lowPowerBodOff(SLEEP_MODE_EXT_STANDBY);
		#else
			lowPowerBodOn(SLEEP_MODE_EXT_STANDBY);
		#endif
	}
	else	
	{
		lowPowerBodOn(SLEEP_MODE_EXT_STANDBY);
	}
		
	if (adc == ADC_OFF) ADCSRA |= (1 << ADEN);
	
	#if !defined(__AVR_ATmega32U4__)
	if (timer2 == TIMER2_OFF)
	{
		if (clockSource & CS22) TCCR2B |= (1 << CS22);
		if (clockSource & CS21) TCCR2B |= (1 << CS21);
		if (clockSource & CS20) TCCR2B |= (1 << CS20);	
	}
	#endif
}

/*******************************************************************************
* Name: ISR (WDT_vect)
* Description: Watchdog Timer interrupt service routine. This routine is 
*		       required to allow automatic WDIF and WDIE bit clearance in 
*			   hardware.
*
*******************************************************************************/
ISR (WDT_vect)
{
	// WDIE & WDIF is cleared in hardware upon entering this ISR
	wdt_disable();
}

#elif defined (__arm__)
#if defined (__SAMD21G18A__)
/*******************************************************************************
* Name: standby
* Description: Putting SAMD21G18A into idle mode. This is the lowest current 
*              consumption mode. Requires separate handling of clock and 
* 			   peripheral management (disabling and shutting down) to achieve 
* 			   the desired current consumption.
*
* Argument  	Description
* =========  	===========
* 1. idleMode   Idle mode level (0, 1, 2) where IDLE_2 level provide lowest 
* 				current consumption in this mode.
* 
*******************************************************************************/
void	LowPowerClass::idle(idle_t idleMode)
{
	SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
	PM->SLEEP.reg = idleMode;
	__DSB();
	__WFI();
}

/*******************************************************************************
* Name: standby
* Description: Putting SAMD21G18A into standby mode. This is the lowest current 
*              consumption mode. Use this together with the built-in RTC (use 
*              RTCZero library) or external pin interrupt to wake up through 
*              external event triggering.
*
* Argument  	Description
* =========  	===========
* 1. NIL
* 
*******************************************************************************/
void	LowPowerClass::standby()
{
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	__DSB();
	__WFI();
}

#else
	#error "Please ensure chosen MCU is ATSAMD21G18A."
#endif
#else
	#error "Processor architecture is not supported."
#endif

LowPowerClass LowPower;



// Code by JeeLabs http://news.jeelabs.org/code/
// Released to the public domain! Enjoy!

#include "RTClib.h"
#ifdef __AVR__
 #include <avr/pgmspace.h>
#elif defined(ESP8266)
 #include <pgmspace.h>
#elif defined(ARDUINO_ARCH_SAMD)
// nothing special needed
#elif defined(ARDUINO_SAM_DUE)
 #define PROGMEM
 #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
 #define Wire Wire1
#endif



#if (ARDUINO >= 100)
 #include <Arduino.h> // capital A so it is error prone on case-sensitive filesystems
 // Macro to deal with the difference in I2C write functions from old and new Arduino versions.
 #define _I2C_WRITE write
 #define _I2C_READ  read
#else
 #include <WProgram.h>
 #define _I2C_WRITE send
 #define _I2C_READ  receive
#endif


static uint8_t read_i2c_register(uint8_t addr, uint8_t reg) {
  Wire.beginTransmission(addr);
  Wire._I2C_WRITE((byte)reg);
  Wire.endTransmission();

  Wire.requestFrom(addr, (byte)1);
  return Wire._I2C_READ();
}

static void write_i2c_register(uint8_t addr, uint8_t reg, uint8_t val) {
  Wire.beginTransmission(addr);
  Wire._I2C_WRITE((byte)reg);
  Wire._I2C_WRITE((byte)val);
  Wire.endTransmission();
}


////////////////////////////////////////////////////////////////////////////////
// utility code, some of this could be exposed in the DateTime API if needed

const uint8_t daysInMonth [] PROGMEM = { 31,28,31,30,31,30,31,31,30,31,30,31 };

// number of days since 2000/01/01, valid for 2001..2099
static uint16_t date2days(uint16_t y, uint8_t m, uint8_t d) {
    if (y >= 2000)
        y -= 2000;
    uint16_t days = d;
    for (uint8_t i = 1; i < m; ++i)
        days += pgm_read_byte(daysInMonth + i - 1);
    if (m > 2 && y % 4 == 0)
        ++days;
    return days + 365 * y + (y + 3) / 4 - 1;
}

static long time2long(uint16_t days, uint8_t h, uint8_t m, uint8_t s) {
    return ((days * 24L + h) * 60 + m) * 60 + s;
}

////////////////////////////////////////////////////////////////////////////////
// DateTime implementation - ignores time zones and DST changes
// NOTE: also ignores leap seconds, see http://en.wikipedia.org/wiki/Leap_second

DateTime::DateTime (uint32_t t) {
  t -= SECONDS_FROM_1970_TO_2000;    // bring to 2000 timestamp from 1970

    ss = t % 60;
    t /= 60;
    mm = t % 60;
    t /= 60;
    hh = t % 24;
    uint16_t days = t / 24;
    uint8_t leap;
    for (yOff = 0; ; ++yOff) {
        leap = yOff % 4 == 0;
        if (days < 365 + leap)
            break;
        days -= 365 + leap;
    }
    for (m = 1; ; ++m) {
        uint8_t daysPerMonth = pgm_read_byte(daysInMonth + m - 1);
        if (leap && m == 2)
            ++daysPerMonth;
        if (days < daysPerMonth)
            break;
        days -= daysPerMonth;
    }
    d = days + 1;
}

DateTime::DateTime (uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) {
    if (year >= 2000)
        year -= 2000;
    yOff = year;
    m = month;
    d = day;
    hh = hour;
    mm = min;
    ss = sec;
}

DateTime::DateTime (const DateTime& copy):
  yOff(copy.yOff),
  m(copy.m),
  d(copy.d),
  hh(copy.hh),
  mm(copy.mm),
  ss(copy.ss)
{}

static uint8_t conv2d(const char* p) {
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9')
        v = *p - '0';
    return 10 * v + *++p - '0';
}

// A convenient constructor for using "the compiler's time":
//   DateTime now (__DATE__, __TIME__);
// NOTE: using F() would further reduce the RAM footprint, see below.
DateTime::DateTime (const char* date, const char* time) {
    // sample input: date = "Dec 26 2009", time = "12:34:56"
    yOff = conv2d(date + 9);
    // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec 
    switch (date[0]) {
        case 'J': m = (date[1] == 'a') ? 1 : ((date[2] == 'n') ? 6 : 7); break;
        case 'F': m = 2; break;
        case 'A': m = date[2] == 'r' ? 4 : 8; break;
        case 'M': m = date[2] == 'r' ? 3 : 5; break;
        case 'S': m = 9; break;
        case 'O': m = 10; break;
        case 'N': m = 11; break;
        case 'D': m = 12; break;
    }
    d = conv2d(date + 4);
    hh = conv2d(time);
    mm = conv2d(time + 3);
    ss = conv2d(time + 6);
}

// A convenient constructor for using "the compiler's time":
// This version will save RAM by using PROGMEM to store it by using the F macro.
//   DateTime now (F(__DATE__), F(__TIME__));
DateTime::DateTime (const __FlashStringHelper* date, const __FlashStringHelper* time) {
    // sample input: date = "Dec 26 2009", time = "12:34:56"
    char buff[11];
    memcpy_P(buff, date, 11);
    yOff = conv2d(buff + 9);
    // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
    switch (buff[0]) {
        case 'J': m = (buff[1] == 'a') ? 1 : ((buff[2] == 'n') ? 6 : 7); break;
        case 'F': m = 2; break;
        case 'A': m = buff[2] == 'r' ? 4 : 8; break;
        case 'M': m = buff[2] == 'r' ? 3 : 5; break;
        case 'S': m = 9; break;
        case 'O': m = 10; break;
        case 'N': m = 11; break;
        case 'D': m = 12; break;
    }
    d = conv2d(buff + 4);
    memcpy_P(buff, time, 8);
    hh = conv2d(buff);
    mm = conv2d(buff + 3);
    ss = conv2d(buff + 6);
}

uint8_t DateTime::dayOfTheWeek() const {    
    uint16_t day = date2days(yOff, m, d);
    return (day + 6) % 7; // Jan 1, 2000 is a Saturday, i.e. returns 6
}

uint32_t DateTime::unixtime(void) const {
  uint32_t t;
  uint16_t days = date2days(yOff, m, d);
  t = time2long(days, hh, mm, ss);
  t += SECONDS_FROM_1970_TO_2000;  // seconds from 1970 to 2000

  return t;
}

long DateTime::secondstime(void) const {
  long t;
  uint16_t days = date2days(yOff, m, d);
  t = time2long(days, hh, mm, ss);
  return t;
}

DateTime DateTime::operator+(const TimeSpan& span) {
  return DateTime(unixtime()+span.totalseconds());
}

DateTime DateTime::operator-(const TimeSpan& span) {
  return DateTime(unixtime()-span.totalseconds());
}

TimeSpan DateTime::operator-(const DateTime& right) {
  return TimeSpan(unixtime()-right.unixtime());
}

////////////////////////////////////////////////////////////////////////////////
// TimeSpan implementation

TimeSpan::TimeSpan (int32_t seconds):
  _seconds(seconds)
{}

TimeSpan::TimeSpan (int16_t days, int8_t hours, int8_t minutes, int8_t seconds):
  _seconds((int32_t)days*86400L + (int32_t)hours*3600 + (int32_t)minutes*60 + seconds)
{}

TimeSpan::TimeSpan (const TimeSpan& copy):
  _seconds(copy._seconds)
{}

TimeSpan TimeSpan::operator+(const TimeSpan& right) {
  return TimeSpan(_seconds+right._seconds);
}

TimeSpan TimeSpan::operator-(const TimeSpan& right) {
  return TimeSpan(_seconds-right._seconds);
}

////////////////////////////////////////////////////////////////////////////////
// RTC_DS1307 implementation

static uint8_t bcd2bin (uint8_t val) { return val - 6 * (val >> 4); }
static uint8_t bin2bcd (uint8_t val) { return val + 6 * (val / 10); }

boolean RTC_DS1307::begin(void) {
  Wire.begin();
  return true;
}

uint8_t RTC_DS1307::isrunning(void) {
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire._I2C_WRITE((byte)0);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 1);
  uint8_t ss = Wire._I2C_READ();
  return !(ss>>7);
}

void RTC_DS1307::adjust(const DateTime& dt) {
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire._I2C_WRITE((byte)0); // start at location 0
  Wire._I2C_WRITE(bin2bcd(dt.second()));
  Wire._I2C_WRITE(bin2bcd(dt.minute()));
  Wire._I2C_WRITE(bin2bcd(dt.hour()));
  Wire._I2C_WRITE(bin2bcd(0));
  Wire._I2C_WRITE(bin2bcd(dt.day()));
  Wire._I2C_WRITE(bin2bcd(dt.month()));
  Wire._I2C_WRITE(bin2bcd(dt.year() - 2000));
  Wire.endTransmission();
}

DateTime RTC_DS1307::now() {
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire._I2C_WRITE((byte)0);	
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);
  uint8_t ss = bcd2bin(Wire._I2C_READ() & 0x7F);
  uint8_t mm = bcd2bin(Wire._I2C_READ());
  uint8_t hh = bcd2bin(Wire._I2C_READ());
  Wire._I2C_READ();
  uint8_t d = bcd2bin(Wire._I2C_READ());
  uint8_t m = bcd2bin(Wire._I2C_READ());
  uint16_t y = bcd2bin(Wire._I2C_READ()) + 2000;
  
  return DateTime (y, m, d, hh, mm, ss);
}

Ds1307SqwPinMode RTC_DS1307::readSqwPinMode() {
  int mode;

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire._I2C_WRITE(DS1307_CONTROL);
  Wire.endTransmission();
  
  Wire.requestFrom((uint8_t)DS1307_ADDRESS, (uint8_t)1);
  mode = Wire._I2C_READ();

  mode &= 0x93;
  return static_cast<Ds1307SqwPinMode>(mode);
}

void RTC_DS1307::writeSqwPinMode(Ds1307SqwPinMode mode) {
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire._I2C_WRITE(DS1307_CONTROL);
  Wire._I2C_WRITE(mode);
  Wire.endTransmission();
}

void RTC_DS1307::readnvram(uint8_t* buf, uint8_t size, uint8_t address) {
  int addrByte = DS1307_NVRAM + address;
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire._I2C_WRITE(addrByte);
  Wire.endTransmission();
  
  Wire.requestFrom((uint8_t) DS1307_ADDRESS, size);
  for (uint8_t pos = 0; pos < size; ++pos) {
    buf[pos] = Wire._I2C_READ();
  }
}

void RTC_DS1307::writenvram(uint8_t address, uint8_t* buf, uint8_t size) {
  int addrByte = DS1307_NVRAM + address;
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire._I2C_WRITE(addrByte);
  for (uint8_t pos = 0; pos < size; ++pos) {
    Wire._I2C_WRITE(buf[pos]);
  }
  Wire.endTransmission();
}

uint8_t RTC_DS1307::readnvram(uint8_t address) {
  uint8_t data;
  readnvram(&data, 1, address);
  return data;
}

void RTC_DS1307::writenvram(uint8_t address, uint8_t data) {
  writenvram(address, &data, 1);
}

////////////////////////////////////////////////////////////////////////////////
// RTC_Millis implementation

long RTC_Millis::offset = 0;

void RTC_Millis::adjust(const DateTime& dt) {
    offset = dt.unixtime() - millis() / 1000;
}

DateTime RTC_Millis::now() {
  return (uint32_t)(offset + millis() / 1000);
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// RTC_PCF8563 implementation

boolean RTC_PCF8523::begin(void) {
  Wire.begin();
  return true;
}

boolean RTC_PCF8523::initialized(void) {
  Wire.beginTransmission(PCF8523_ADDRESS);
  Wire._I2C_WRITE((byte)PCF8523_CONTROL_3);
  Wire.endTransmission();

  Wire.requestFrom(PCF8523_ADDRESS, 1);
  uint8_t ss = Wire._I2C_READ();
  return ((ss & 0xE0) != 0xE0);
}

void RTC_PCF8523::adjust(const DateTime& dt) {
  Wire.beginTransmission(PCF8523_ADDRESS);
  Wire._I2C_WRITE((byte)3); // start at location 3
  Wire._I2C_WRITE(bin2bcd(dt.second()));
  Wire._I2C_WRITE(bin2bcd(dt.minute()));
  Wire._I2C_WRITE(bin2bcd(dt.hour()));
  Wire._I2C_WRITE(bin2bcd(dt.day()));
  Wire._I2C_WRITE(bin2bcd(0)); // skip weekdays
  Wire._I2C_WRITE(bin2bcd(dt.month()));
  Wire._I2C_WRITE(bin2bcd(dt.year() - 2000));
  Wire.endTransmission();

  // set to battery switchover mode
  Wire.beginTransmission(PCF8523_ADDRESS);
  Wire._I2C_WRITE((byte)PCF8523_CONTROL_3);
  Wire._I2C_WRITE((byte)0x00);
  Wire.endTransmission();
}

DateTime RTC_PCF8523::now() {
  Wire.beginTransmission(PCF8523_ADDRESS);
  Wire._I2C_WRITE((byte)3);	
  Wire.endTransmission();

  Wire.requestFrom(PCF8523_ADDRESS, 7);
  uint8_t ss = bcd2bin(Wire._I2C_READ() & 0x7F);
  uint8_t mm = bcd2bin(Wire._I2C_READ());
  uint8_t hh = bcd2bin(Wire._I2C_READ());
  uint8_t d = bcd2bin(Wire._I2C_READ());
  Wire._I2C_READ();  // skip 'weekdays'
  uint8_t m = bcd2bin(Wire._I2C_READ());
  uint16_t y = bcd2bin(Wire._I2C_READ()) + 2000;
  
  return DateTime (y, m, d, hh, mm, ss);
}

Pcf8523SqwPinMode RTC_PCF8523::readSqwPinMode() {
  int mode;

  Wire.beginTransmission(PCF8523_ADDRESS);
  Wire._I2C_WRITE(PCF8523_CLKOUTCONTROL);
  Wire.endTransmission();
  
  Wire.requestFrom((uint8_t)PCF8523_ADDRESS, (uint8_t)1);
  mode = Wire._I2C_READ();

  mode >>= 3;
  mode &= 0x7;
  return static_cast<Pcf8523SqwPinMode>(mode);
}

void RTC_PCF8523::writeSqwPinMode(Pcf8523SqwPinMode mode) {
  Wire.beginTransmission(PCF8523_ADDRESS);
  Wire._I2C_WRITE(PCF8523_CLKOUTCONTROL);
  Wire._I2C_WRITE(mode << 3);
  Wire.endTransmission();
}




////////////////////////////////////////////////////////////////////////////////
// RTC_DS3231 implementation

boolean RTC_DS3231::begin(void) {
  Wire.begin();
  return true;
}

bool RTC_DS3231::lostPower(void) {
  return (read_i2c_register(DS3231_ADDRESS, DS3231_STATUSREG) >> 7);
}

void RTC_DS3231::adjust(const DateTime& dt) {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire._I2C_WRITE((byte)0); // start at location 0
  Wire._I2C_WRITE(bin2bcd(dt.second()));
  Wire._I2C_WRITE(bin2bcd(dt.minute()));
  Wire._I2C_WRITE(bin2bcd(dt.hour()));
  Wire._I2C_WRITE(bin2bcd(0));
  Wire._I2C_WRITE(bin2bcd(dt.day()));
  Wire._I2C_WRITE(bin2bcd(dt.month()));
  Wire._I2C_WRITE(bin2bcd(dt.year() - 2000));
  Wire.endTransmission();

  uint8_t statreg = read_i2c_register(DS3231_ADDRESS, DS3231_STATUSREG);
  statreg &= ~0x80; // flip OSF bit
  write_i2c_register(DS3231_ADDRESS, DS3231_STATUSREG, statreg);
}

DateTime RTC_DS3231::now() {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire._I2C_WRITE((byte)0);	
  Wire.endTransmission();

  Wire.requestFrom(DS3231_ADDRESS, 7);
  uint8_t ss = bcd2bin(Wire._I2C_READ() & 0x7F);
  uint8_t mm = bcd2bin(Wire._I2C_READ());
  uint8_t hh = bcd2bin(Wire._I2C_READ());
  Wire._I2C_READ();
  uint8_t d = bcd2bin(Wire._I2C_READ());
  uint8_t m = bcd2bin(Wire._I2C_READ());
  uint16_t y = bcd2bin(Wire._I2C_READ()) + 2000;
  
  return DateTime (y, m, d, hh, mm, ss);
}

Ds3231SqwPinMode RTC_DS3231::readSqwPinMode() {
  int mode;

  Wire.beginTransmission(DS3231_ADDRESS);
  Wire._I2C_WRITE(DS3231_CONTROL);
  Wire.endTransmission();
  
  Wire.requestFrom((uint8_t)DS3231_ADDRESS, (uint8_t)1);
  mode = Wire._I2C_READ();

  mode &= 0x93;
  return static_cast<Ds3231SqwPinMode>(mode);
}

void RTC_DS3231::writeSqwPinMode(Ds3231SqwPinMode mode) {
  uint8_t ctrl;
  ctrl = read_i2c_register(DS3231_ADDRESS, DS3231_CONTROL);

  ctrl &= ~0x04; // turn off INTCON
  ctrl &= ~0x18; // set freq bits to 0

  if (mode == DS3231_OFF) {
    ctrl |= 0x04; // turn on INTCN
  } else {
    ctrl |= mode;
  } 
  write_i2c_register(DS3231_ADDRESS, DS3231_CONTROL, ctrl);

  //Serial.println( read_i2c_register(DS3231_ADDRESS, DS3231_CONTROL), HEX);
}


/*
	SFE_BMP180.cpp
	Bosch BMP180 pressure sensor library for the Arduino microcontroller
	Mike Grusin, SparkFun Electronics

	Uses floating-point equations from the Weather Station Data Logger project
	http://wmrx00.sourceforge.net/
	http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf

	Forked from BMP085 library by M.Grusin

	version 1.0 2013/09/20 initial version
	Verison 1.1.2 - Updated for Arduino 1.6.4 5/2015

	Our example code uses the "beerware" license. You can do anything
	you like with this code. No really, anything. If you find it useful,
	buy me a (root) beer someday.
*/

#include "SFE_BMP180.h"


SFE_BMP180::SFE_BMP180()
// Base library type
{
}


char SFE_BMP180::begin()
// Initialize library for subsequent pressure measurements
{
	double c3,c4,b1;
	
	// Start up the Arduino's "wire" (I2C) library:
	
	Wire.begin();

	// The BMP180 includes factory calibration data stored on the device.
	// Each device has different numbers, these must be retrieved and
	// used in the calculations when taking pressure measurements.

	// Retrieve calibration data from device:
	
	if (readInt(0xAA,AC1) &&
		readInt(0xAC,AC2) &&
		readInt(0xAE,AC3) &&
		readUInt(0xB0,AC4) &&
		readUInt(0xB2,AC5) &&
		readUInt(0xB4,AC6) &&
		readInt(0xB6,VB1) &&
		readInt(0xB8,VB2) &&
		readInt(0xBA,MB) &&
		readInt(0xBC,MC) &&
		readInt(0xBE,MD))
	{

		// All reads completed successfully!

		// If you need to check your math using known numbers,
		// you can uncomment one of these examples.
		// (The correct results are commented in the below functions.)

		// Example from Bosch datasheet
		// AC1 = 408; AC2 = -72; AC3 = -14383; AC4 = 32741; AC5 = 32757; AC6 = 23153;
		// B1 = 6190; B2 = 4; MB = -32768; MC = -8711; MD = 2868;

		// Example from http://wmrx00.sourceforge.net/Arduino/BMP180-Calcs.pdf
		// AC1 = 7911; AC2 = -934; AC3 = -14306; AC4 = 31567; AC5 = 25671; AC6 = 18974;
		// VB1 = 5498; VB2 = 46; MB = -32768; MC = -11075; MD = 2432;

		/*
		Serial.print("AC1: "); Serial.println(AC1);
		Serial.print("AC2: "); Serial.println(AC2);
		Serial.print("AC3: "); Serial.println(AC3);
		Serial.print("AC4: "); Serial.println(AC4);
		Serial.print("AC5: "); Serial.println(AC5);
		Serial.print("AC6: "); Serial.println(AC6);
		Serial.print("VB1: "); Serial.println(VB1);
		Serial.print("VB2: "); Serial.println(VB2);
		Serial.print("MB: "); Serial.println(MB);
		Serial.print("MC: "); Serial.println(MC);
		Serial.print("MD: "); Serial.println(MD);
		*/
		
		// Compute floating-point polynominals:

		c3 = 160.0 * pow(2,-15) * AC3;
		c4 = pow(10,-3) * pow(2,-15) * AC4;
		b1 = pow(160,2) * pow(2,-30) * VB1;
		c5 = (pow(2,-15) / 160) * AC5;
		c6 = AC6;
		mc = (pow(2,11) / pow(160,2)) * MC;
		md = MD / 160.0;
		x0 = AC1;
		x1 = 160.0 * pow(2,-13) * AC2;
		x2 = pow(160,2) * pow(2,-25) * VB2;
		y0 = c4 * pow(2,15);
		y1 = c4 * c3;
		y2 = c4 * b1;
		p0 = (3791.0 - 8.0) / 1600.0;
		p1 = 1.0 - 7357.0 * pow(2,-20);
		p2 = 3038.0 * 100.0 * pow(2,-36);

		/*
		Serial.println();
		Serial.print("c3: "); Serial.println(c3);
		Serial.print("c4: "); Serial.println(c4);
		Serial.print("c5: "); Serial.println(c5);
		Serial.print("c6: "); Serial.println(c6);
		Serial.print("b1: "); Serial.println(b1);
		Serial.print("mc: "); Serial.println(mc);
		Serial.print("md: "); Serial.println(md);
		Serial.print("x0: "); Serial.println(x0);
		Serial.print("x1: "); Serial.println(x1);
		Serial.print("x2: "); Serial.println(x2);
		Serial.print("y0: "); Serial.println(y0);
		Serial.print("y1: "); Serial.println(y1);
		Serial.print("y2: "); Serial.println(y2);
		Serial.print("p0: "); Serial.println(p0);
		Serial.print("p1: "); Serial.println(p1);
		Serial.print("p2: "); Serial.println(p2);
		*/
		
		// Success!
		return(1);
	}
	else
	{
		// Error reading calibration data; bad component or connection?
		return(0);
	}
}


char SFE_BMP180::readInt(char address, int16_t &value)
// Read a signed integer (two bytes) from device
// address: register to start reading (plus subsequent register)
// value: external variable to store data (function modifies value)
{
	unsigned char data[2];

	data[0] = address;
	if (readBytes(data,2))
	{
		value = (int16_t)((data[0]<<8)|data[1]);
		//if (*value & 0x8000) *value |= 0xFFFF0000; // sign extend if negative
		return(1);
	}
	value = 0;
	return(0);
}


char SFE_BMP180::readUInt(char address, uint16_t &value)
// Read an unsigned integer (two bytes) from device
// address: register to start reading (plus subsequent register)
// value: external variable to store data (function modifies value)
{
	unsigned char data[2];

	data[0] = address;
	if (readBytes(data,2))
	{
		value = (((uint16_t)data[0]<<8)|(uint16_t)data[1]);
		return(1);
	}
	value = 0;
	return(0);
}


char SFE_BMP180::readBytes(unsigned char *values, char length)
// Read an array of bytes from device
// values: external array to hold data. Put starting register in values[0].
// length: number of bytes to read
{
	uint8_t x;

	Wire.beginTransmission(BMP180_ADDR);
	Wire.write(values[0]);
	_error = Wire.endTransmission();
	if (_error == 0)
	{
		Wire.requestFrom(BMP180_ADDR,length);
		while(Wire.available() != length) ; // wait until bytes are ready
		for(x=0;x<length;x++)
		{
			values[x] = Wire.read();
		}
		return(1);
	}
	return(0);
}


char SFE_BMP180::writeBytes(unsigned char *values, char length)
// Write an array of bytes to device
// values: external array of data to write. Put starting register in values[0].
// length: number of bytes to write
{
	Wire.beginTransmission(BMP180_ADDR);
	Wire.write(values,length);
	_error = Wire.endTransmission();
	if (_error == 0)
		return(1);
	else
		return(0);
}


char SFE_BMP180::startTemperature(void)
// Begin a temperature reading.
// Will return delay in ms to wait, or 0 if I2C error
{
	unsigned char data[2], result;
	
	data[0] = BMP180_REG_CONTROL;
	data[1] = BMP180_COMMAND_TEMPERATURE;
	result = writeBytes(data, 2);
	if (result) // good write?
		return(5); // return the delay in ms (rounded up) to wait before retrieving data
	else
		return(0); // or return 0 if there was a problem communicating with the BMP
}


char SFE_BMP180::getTemperature(double &T)
// Retrieve a previously-started temperature reading.
// Requires begin() to be called once prior to retrieve calibration parameters.
// Requires startTemperature() to have been called prior and sufficient time elapsed.
// T: external variable to hold result.
// Returns 1 if successful, 0 if I2C error.
{
	unsigned char data[2];
	char result;
	double tu, a;
	
	data[0] = BMP180_REG_RESULT;

	result = readBytes(data, 2);
	if (result) // good read, calculate temperature
	{
		tu = (data[0] * 256.0) + data[1];

		//example from Bosch datasheet
		//tu = 27898;

		//example from http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf
		//tu = 0x69EC;
		
		a = c5 * (tu - c6);
		T = a + (mc / (a + md));

		/*		
		Serial.println();
		Serial.print("tu: "); Serial.println(tu);
		Serial.print("a: "); Serial.println(a);
		Serial.print("T: "); Serial.println(*T);
		*/
	}
	return(result);
}


char SFE_BMP180::startPressure(char oversampling)
// Begin a pressure reading.
// Oversampling: 0 to 3, higher numbers are slower, higher-res outputs.
// Will return delay in ms to wait, or 0 if I2C error.
{
	unsigned char data[2], result, delay;
	
	data[0] = BMP180_REG_CONTROL;

	switch (oversampling)
	{
		case 0:
			data[1] = BMP180_COMMAND_PRESSURE0;
			delay = 5;
		break;
		case 1:
			data[1] = BMP180_COMMAND_PRESSURE1;
			delay = 8;
		break;
		case 2:
			data[1] = BMP180_COMMAND_PRESSURE2;
			delay = 14;
		break;
		case 3:
			data[1] = BMP180_COMMAND_PRESSURE3;
			delay = 26;
		break;
		default:
			data[1] = BMP180_COMMAND_PRESSURE0;
			delay = 5;
		break;
	}
	result = writeBytes(data, 2);
	if (result) // good write?
		return(delay); // return the delay in ms (rounded up) to wait before retrieving data
	else
		return(0); // or return 0 if there was a problem communicating with the BMP
}


char SFE_BMP180::getPressure(double &P, double &T)
// Retrieve a previously started pressure reading, calculate abolute pressure in mbars.
// Requires begin() to be called once prior to retrieve calibration parameters.
// Requires startPressure() to have been called prior and sufficient time elapsed.
// Requires recent temperature reading to accurately calculate pressure.

// P: external variable to hold pressure.
// T: previously-calculated temperature.
// Returns 1 for success, 0 for I2C error.

// Note that calculated pressure value is absolute mbars, to compensate for altitude call sealevel().
{
	unsigned char data[3];
	char result;
	double pu,s,x,y,z;
	
	data[0] = BMP180_REG_RESULT;

	result = readBytes(data, 3);
	if (result) // good read, calculate pressure
	{
		pu = (data[0] * 256.0) + data[1] + (data[2]/256.0);

		//example from Bosch datasheet
		//pu = 23843;

		//example from http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf, pu = 0x982FC0;	
		//pu = (0x98 * 256.0) + 0x2F + (0xC0/256.0);
		
		s = T - 25.0;
		x = (x2 * pow(s,2)) + (x1 * s) + x0;
		y = (y2 * pow(s,2)) + (y1 * s) + y0;
		z = (pu - x) / y;
		P = (p2 * pow(z,2)) + (p1 * z) + p0;

		/*
		Serial.println();
		Serial.print("pu: "); Serial.println(pu);
		Serial.print("T: "); Serial.println(*T);
		Serial.print("s: "); Serial.println(s);
		Serial.print("x: "); Serial.println(x);
		Serial.print("y: "); Serial.println(y);
		Serial.print("z: "); Serial.println(z);
		Serial.print("P: "); Serial.println(*P);
		*/
	}
	return(result);
}


double SFE_BMP180::sealevel(double P, double A)
// Given a pressure P (mb) taken at a specific altitude (meters),
// return the equivalent pressure (mb) at sea level.
// This produces pressure readings that can be used for weather measurements.
{
	return(P/pow(1-(A/44330.0),5.255));
}


double SFE_BMP180::altitude(double P, double P0)
// Given a pressure measurement P (mb) and the pressure at a baseline P0 (mb),
// return altitude (meters) above baseline.
{
	return(44330.0*(1-pow(P/P0,1/5.255)));
}


char SFE_BMP180::getError(void)
	// If any library command fails, you can retrieve an extended
	// error code using this command. Errors are from the wire library: 
	// 0 = Success
	// 1 = Data too long to fit in transmit buffer
	// 2 = Received NACK on transmit of address
	// 3 = Received NACK on transmit of data
	// 4 = Other error
{
	return(_error);
}

