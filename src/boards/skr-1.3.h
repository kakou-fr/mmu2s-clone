#include <lpc17xx.h>
#define CDC_SERIAL

//
// Software serial
//
#ifdef USE_TMC
#define X_SERIAL_TX_PIN P4_29
#define X_SERIAL_RX_PIN P1_17

#define Y_SERIAL_TX_PIN P1_16
#define Y_SERIAL_RX_PIN P1_15

#define Z_SERIAL_TX_PIN P1_14
#define Z_SERIAL_RX_PIN P1_10

#define E0_SERIAL_TX_PIN P1_09
#define E0_SERIAL_RX_PIN P1_08
#endif

//
// Steppers
//
#define X_STEP_PIN P2_02
#define X_DIR_PIN P2_06
#define X_ENABLE_PIN P2_01
#ifdef USE_TMC
#define X_RSENSE 0.11
#define X_MICROSTEPS 16
#endif

#define Y_STEP_PIN P0_19
#define Y_DIR_PIN P0_20
#define Y_ENABLE_PIN P2_08
#ifdef USE_TMC
#define Y_RSENSE 0.11
#define Y_MICROSTEPS 16
#endif

#define Z_STEP_PIN P0_22
#define Z_DIR_PIN P2_11
#define Z_ENABLE_PIN P0_21
#ifdef USE_TMC
#define Z_RSENSE 0.11
#define Z_MICROSTEPS 16
#endif

#define E0_STEP_PIN P2_13
#define E0_DIR_PIN P0_11
#define E0_ENABLE_PIN P2_12
#ifdef USE_TMC
#define E0_RSENSE 0.11
#define E0_MICROSTEPS 16
#endif

//
// Limit Switches
//
#define X_MIN_PIN P1_29 // X-
#define X_MAX_PIN P1_28 // X+
#define Y_MIN_PIN P1_27 // Y-
#define Y_MAX_PIN P1_26 // Y+
#define Z_MIN_PIN P1_25 // Z-
#define Z_MAX_PIN P1_24 // Z+
#define FIL_RUNOUT_PIN P1_28
/***************/


#ifdef MMU2S
// Color selector stepper motor (driven by trapezoidal screw)
#define colorSelectorStepPin X_STEP_PIN
#define colorSelectorDirPin X_DIR_PIN
#define colorSelectorEnablePin X_ENABLE_PIN
#ifdef USE_TMC
#define colorSelectorRMSCurrent 750
#define colorSelectorSerialRXPin X_SERIAL_RX_PIN
#define colorSelectorSerialTXPin X_SERIAL_TX_PIN
#define colorSelectorRSense X_RSENSE
#define colorSelectorMicrosteps X_MICROSTEPS
#endif
#define colorSelectorEndstop X_STOP_PIN
#endif

// Roller selector stepper motor
#define idlerStepPin Y_STEP_PIN
#define idlerDirPin Y_DIR_PIN
#define idlerEnablePin Y_ENABLE_PIN
#ifdef USE_TMC
#define idlerRMSCurrent 750
#define idlerSerialRXPin Y_SERIAL_RX_PIN
#define idlerSerialTXPin Y_SERIAL_TX_PIN
#define idlerRSense Y_RSENSE
#define idlerMicrosteps Y_MICROSTEPS
#endif
#define idlerEndstop Y_MIN_PIN

// Extruder stepper motor
#define extruderStepPin E0_STEP_PIN
#define extruderDirPin E0_DIR_PIN
#define extruderEnablePin E0_ENABLE_PIN
#ifdef USE_TMC
#define extruderRMSCurrent 750
#define extruderSerialRXPin E0_SERIAL_RX_PIN
#define extruderSerialTXPin E0_SERIAL_TX_PIN
#define extruderRSense E0_RSENSE
#define extruderMicrosteps E0_MICROSTEPS
#endif


#ifdef MMU2S
//BROWN = +5V
//BLUE = GND
//BLACK = SIGNAL
// Z_MIN_PIN
#define findaPin Z_MIN_PIN
#endif

#ifdef  IR_ON_MMU
// Z_MAX_PIN
#define filamentSwitch FIL_RUNOUT_PIN
#endif

#define SerialPRINTER Serial  // TFT  pins
/*
#include <SoftwareSerial.h>
SoftwareSerial Serials(PB7,PC13); // RX, TX 
#define SerialPRINTER Serials
*/