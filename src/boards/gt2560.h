// added this pin as a debug pin (lights a green LED so I can see the 'C0' command in action
//Y_MIN_PIN
#define greenLED 26

// modified code on 10.2.18 to accomodate RAMPS 1.6 board mapping
//

// PIN Y
#define idlerDirPin  33
#define idlerStepPin 31
#define idlerEnablePin 29


// PIN Z
#define extruderDirPin  39 //  pin 48 for extruder motor direction pin
#define extruderStepPin  37 //  pin 48 for extruder motor stepper motor pin
#define extruderEnablePin 35 //  pin A8 for extruder motor rst/sleep motor pin

//PIN X
#define colorSelectorDirPin  23 //color selector stepper motor (driven by trapezoidal screw)
#define colorSelectorStepPin 25
#define colorSelectorEnablePin 27


//BROWN = +5V
//BLUE = GND
//BLACK = SIGNAL
//SERVo PIN GT2560
#define findaPin  11

// Z_MIN_PIN
#define colorSelectorEnstop 30

// Z_MAX_PIN
#define filamentSwitch 32


// https://www.lesimprimantes3d.fr/forum/uploads/monthly_2018_10/Epson_29102018163351.jpg.9b3dec82b6691ac5af5c7ea2451e41b4.jpg
//Hardware Serial1 : 19 (RX) and 18 (TX)
// https://reprap.org/mediawiki/images/f/ff/MKS_MINI12864_LCD_controller_pin_out_-_signal_names.jpg
//https://www.geeetech.com/forum/download/file.php?id=3997&sid=b5aaf40b7a0b35fb5403798518f426b9
// 0 1 2 3 4
// 5 6 7 8 9
//
// https://reprap.org/mediawiki/images/5/51/RRD_FULL_GRAPHIC_SMART_CONTROLER_SCHEMATIC.pdf
//
// 19 : BTN_ENC -> EXP1 pin 0
// 18 : BEEPER_PIN -> EXP1 pin 5
//
//SoftwareSerial Serial1(10,11); // RX, TX (communicates with the MK3 controller boards


//SKR
// P.015 and P.16 (UART1)
#define SerialPRINTER Serial1
