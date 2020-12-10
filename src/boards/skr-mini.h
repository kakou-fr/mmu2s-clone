// https://github.com/bigtreetech/BIGTREETECH-SKR-MINI-V1.1/blob/master/hardware/SKR-mini-V1.1-PIN.pdf
// added this pin as a debug pin (lights a green LED so I can see the 'C0' command in action
// Y_MIN_PIN
#define greenLED PC1

// modified code on 10.2.18 to accomodate RAMPS 1.6 board mapping
//

#define SOFTWARE_RESET


#ifdef MMU2S
//PIN X
#define colorSelectorStepPin PC6
#define colorSelectorDirPin  PC7 //color selector stepper motor (driven by trapezoidal screw)
#define colorSelectorEnablePin PB15
#endif

// PIN Y
#define idlerStepPin PB13
#define idlerDirPin  PB14
#define idlerEnablePin PB12


// PIN E
#define extruderStepPin  PC5 
#define extruderDirPin  PB0 
#define extruderEnablePin PC4


//BROWN = +5V
//BLUE = GND
//BLACK = SIGNAL
// X_MIN_PIN
#define findaPin  PC2

// Z_MIN_PIN
#ifdef MMU2S
#define colorSelectorEnstop PC0
#endif

// Z_MAX_PIN
#define filamentSwitch PC3

//SKR MINI
//TFT PIN
// RST RX0 TX0 GND +5V

//SKRs
// P.015 and P.16 (UART1)

#define SerialPRINTER Serial1
/*
#include <SoftwareSerial.h>
SoftwareSerial Serials(PB7,PC13); // RX, TX 
#define SerialPRINTER Serials
*/
