// https://github.com/bigtreetech/BIGTREETECH-SKR-MINI-V1.1/blob/master/hardware/SKR-mini-V1.1-PIN.pdf
// added this pin as a debug pin (lights a green LED so I can see the 'C0' command in action
// Y_MIN_PIN
#define greenLED P1_27

// modified code on 10.2.18 to accomodate RAMPS 1.6 board mapping
//


#ifdef MMU2S
//PIN X
#define colorSelectorStepPin P2_2
#define colorSelectorDirPin  P2_6 //color selector stepper motor (driven by trapezoidal screw)
#define colorSelectorEnablePin P2_1
#endif

// PIN Y
#define idlerStepPin P0_19
#define idlerDirPin  P0_20
#define idlerEnablePin P2_8


// PIN Z
#define extruderStepPin  P0_22 
#define extruderDirPin  P2_11
#define extruderEnablePin P0_21


//BROWN = +5V
//BLUE = GND
//BLACK = SIGNAL
// X_MIN_PIN
#define findaPin  P1_29

// Z_MIN_PIN
#define colorSelectorEnstop P1_25

// Z_MAX_PIN
#define filamentSwitch P1_24

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