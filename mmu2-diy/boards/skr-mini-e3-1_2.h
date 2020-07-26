// https://github.com/bigtreetech/BIGTREETECH-SKR-MINI-V1.1/blob/master/hardware/SKR-mini-V1.1-PIN.pdf
// added this pin as a debug pin (lights a green LED so I can see the 'C0' command in action
// Y-STOP
#define greenLED PC1

// modified code on 10.2.18 to accomodate RAMPS 1.6 board mapping
//


#ifdef MMU2S
// X Motor
#define colorSelectorStepPin PB13
#define colorSelectorDirPin  PB12 //color selector stepper motor (driven by trapezoidal screw)
#define colorSelectorEnablePin PB14
#endif

// Y Motor
#define idlerStepPin PB10
#define idlerDirPin  PB2
#define idlerEnablePin PB11

// E Motor
#define extruderStepPin  PB3 
#define extruderDirPin  PB4
#define extruderEnablePin PD2

// X-STOP
#define findaPin  PC0

// Z-STOP
#ifdef MMU2S
#define colorSelectorEnstop PC2
#endif

// E0-STOP
#define filamentSwitch PC3

//SKR MINI E3
//TFT PIN

//SCH https://raw.githubusercontent.com/bigtreetech/BIGTREETECH-SKR-MINI-V1.1/master/hardware/SKR-mini-V1.1sch.pdf
// RX2 TX2 

//PIN https://github.com/bigtreetech/BIGTREETECH-SKR-MINI-V1.1/blob/master/hardware/SKR-mini-V1.1-PIN.pdf
// RST RX0 TX0 GND +5V

#define SerialPRINTER Serial2
/*
#include <SoftwareSerial.h>
SoftwareSerial Serials(PB7,PC13); // RX, TX 
#define SerialPRINTER Serials
*/