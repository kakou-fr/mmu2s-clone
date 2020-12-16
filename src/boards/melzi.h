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
#define colorSelectorEndstop 20 // Z Stop
#endif

#ifdef MMU2S
//BROWN = +5V
//BLUE = GND
//BLACK = SIGNAL
// Z_MIN_PIN
#define findaPin 18 X stop
#endif

#ifdef  IR_ON_MMU
// Z_MAX_PIN
#define filamentSwitch 6 // B-MOT (TEMP_BED_PIN)
#endif

#define SerialPRINTER Serial1
