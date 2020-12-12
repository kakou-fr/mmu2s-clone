// https://github.com/bigtreetech/BIGTREETECH-SKR-MINI-V1.1/blob/master/hardware/SKR-mini-V1.1-PIN.pdf

#define USE_TMC
#define SOFTWARE_RESET


#define HOLD_MULTIPLIER 0.5
#define TMC_BAUD_RATE 19200 // Reduce baud rate to improve software serial reliability

#define USE_TMC_SENSORLESS
#define TMC_SG_THR_IDL     20  //TMC2209 set to about 20, TMC2130 Set to about 19
#define TMC_SG_THR_SEL     20  //TMC2209 set to about 20, TMC2130 Set to about 19

//
// Software serial
//
#define X_SERIAL_TX_PIN PC12
#define X_SERIAL_RX_PIN PC12

#define Y_SERIAL_TX_PIN PB7
#define Y_SERIAL_RX_PIN PB7

#define E0_SERIAL_TX_PIN PC14
#define E0_SERIAL_RX_PIN PC14

//
// Steppers
//
#define X_ENABLE_PIN PB15
#define X_STEP_PIN PC6
#define X_DIR_PIN PC7
#define X_RSENSE 0.11
#define X_MICROSTEPS 16

#define Y_ENABLE_PIN PB12
#define Y_STEP_PIN PB13
#define Y_DIR_PIN PB14
#define Y_RSENSE 0.11
#define Y_MICROSTEPS 16

#define E0_ENABLE_PIN PC4
#define E0_STEP_PIN PC5
#define E0_DIR_PIN PB0
#define E0_RSENSE 0.11
#define E0_MICROSTEPS 16


//
// Limit Switches
//
#define X_STOP_PIN PC2       // "X-STOP" -
#define Y_STOP_PIN PC1       // "Y-STOP" -
#define Z_STOP_PIN PC0        // "Z-STOP" -
#define X_MAX_STOP_PIN PA2       // "X-STOP" +
#define Y_MAX_STOP_PIN PA1       // "Y-STOP" +
#define Z_MAX_STOP_PIN PC3        // "Z-STOP" +

#ifdef MMU2S
// Color selector stepper motor (driven by trapezoidal screw)
#define colorSelectorStepPin X_STEP_PIN
#define colorSelectorDirPin X_DIR_PIN
#define colorSelectorEnablePin X_ENABLE_PIN
#define colorSelectorRMSCurrent 750
#define colorSelectorSerialRXPin X_SERIAL_RX_PIN
#define colorSelectorSerialTXPin X_SERIAL_TX_PIN
#define colorSelectorRSense X_RSENSE
#define colorSelectorMicrosteps X_MICROSTEPS
#define colorSelectorEndstop X_STOP_PIN
#endif

// Roller selector stepper motor
#define idlerStepPin Y_STEP_PIN
#define idlerDirPin Y_DIR_PIN
#define idlerEnablePin Y_ENABLE_PIN
#define idlerRMSCurrent 750
#define idlerSerialRXPin Y_SERIAL_RX_PIN
#define idlerSerialTXPin Y_SERIAL_TX_PIN
#define idlerRSense Y_RSENSE
#define idlerMicrosteps Y_MICROSTEPS
#define idlerEndstop Y_STOP_PIN

// Extruder stepper motor
#define extruderStepPin E0_STEP_PIN
#define extruderDirPin E0_DIR_PIN
#define extruderEnablePin E0_ENABLE_PIN
#define extruderRMSCurrent 750
#define extruderSerialRXPin E0_SERIAL_RX_PIN
#define extruderSerialTXPin E0_SERIAL_TX_PIN
#define extruderRSense E0_RSENSE
#define extruderMicrosteps E0_MICROSTEPS

#ifdef MMU2S
//BROWN = +5V
//BLUE = GND
//BLACK = SIGNAL
// Z_MIN_PIN
#define findaPin Z_STOP_PIN
#endif

#ifdef  IR_ON_MMU
// Z_MAX_PIN
#define filamentSwitch Z_MAX_STOP_PIN
#endif

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
