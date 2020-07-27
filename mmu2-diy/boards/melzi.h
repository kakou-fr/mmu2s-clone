// added this pin as a debug pin (lights a green LED so I can see the 'C0' command in action
// Y Stop
#define greenLED 19

// Z Motor Pins
#define idlerDirPin 2
#define idlerStepPin 3
#define idlerEnablePin 26

// Extruder Motor Pins
#define extruderDirPin 0
#define extruderStepPin 1
#define extruderEnablePin 14

// Note: Creality Melzi does not have indepedent X or Y enable pins, shared with extruder
#ifdef MMU2S
#define colorSelectorDirPin   //color selector stepper motor (driven by trapezoidal screw)
#define colorSelectorStepPin 
#define colorSelectorEnablePin 
#endif

// X stop
#define findaPin  18

// Z Stop
#define colorSelectorEnstop 20

// B-MOT (TEMP_BED_PIN)
#define filamentSwitch 6

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


#define SerialPRINTER Serial1
#define ConsoleSerial Serial
