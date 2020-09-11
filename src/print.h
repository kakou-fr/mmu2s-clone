#ifndef PRINT_H
#define PRINT_H

#include <Arduino.h>
/*************************/
// http://www.geeetech.com/wiki/images/9/90/GT2560_sch.pdf
//
// LCD
//        SV1
// 5V       1 2 GND
// PH3(15)  3 4 PE3(5)
// SCL(43)  5 6 TXD2(13)
// SDA(44)  7 8 RXD2(12)
// RXD1(45) 9 10 TXD1(46)


/**
 *                _____                                             _____
 *            NC | · · | GND                                    5V | · · | GND
 *         RESET | · · | PB9 (SD_DETECT)             (LCD_D7) PC14 | · · | PC15 (LCD_D6)
 *  (MOSI)   PB5 | · · | PB8 (BTN_EN2)               (LCD_D5)  PB7 | · · | PC13 (LCD_D4)
 * (SD_SS)  PA15 | · · | PD2 (BTN_EN1)               (LCD_RS) PC12 | · · | PB6  (LCD_EN)
 *   (SCK)   PB3 | · · | PB4 (MISO)                 (BTN_ENC) PC11 | · · | PC10 (BEEPER)
 *                -----                                             -----
 *                EXP2                                              EXP1
 */

#define SERIAL_DEBUG



void println_log(const char *msg);

void println_log(int msg);

void println_log(unsigned int msg);

void println_log(char msg);

void print_log(const char *msg);

void print_log(char msg);

class IOPrint
{
public:
	IOPrint();

	void setup();
};

#endif // PRINT_H
