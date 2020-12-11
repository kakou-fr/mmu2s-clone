#define USE_TMC
#define SOFTWARE_RESET

#define HOLD_MULTIPLIER 0.5
#define TMC_BAUD_RATE 19200 // Reduce baud rate to improve software serial reliability

#define USE_TMC_SENSORLESS
#define TMC_SG_THR_IDL     20  //TMC2209 set to about 20, TMC2130 Set to about 19


//
// Software serial
//
#define X_SERIAL_TX_PIN PC10
#define X_SERIAL_RX_PIN PC10

#define Y_SERIAL_TX_PIN PC11
#define Y_SERIAL_RX_PIN PC11

#define Z_SERIAL_TX_PIN PC12
#define Z_SERIAL_RX_PIN PC12

#define E0_SERIAL_TX_PIN PD2
#define E0_SERIAL_RX_PIN PD2

//
// Steppers
//
#define X_ENABLE_PIN PC7
#define X_STEP_PIN PC6
#define X_DIR_PIN PB15
#define X_RSENSE 0.11
#define X_MICROSTEPS 16

#define Y_ENABLE_PIN PB14
#define Y_STEP_PIN PB13
#define Y_DIR_PIN PB12
#define Y_RSENSE 0.11
#define Y_MICROSTEPS 16

#define Z_ENABLE_PIN PB11
#define Z_STEP_PIN PB10
#define Z_DIR_PIN PB2
#define Z_RSENSE 0.11
#define Z_MICROSTEPS 16

#define E0_ENABLE_PIN PB1
#define E0_STEP_PIN PB0
#define E0_DIR_PIN PC5
#define E0_RSENSE 0.11
#define E0_MICROSTEPS 16

//
// Limit Switches
//
#define X_STOP_PIN PC1       // "X-STOP"
#define Y_STOP_PIN PC0       // "Y-STOP"
#define Z_STOP_PIN PC15      // "Z-STOP"
#define Z_MIN_PROBE_PIN PC14 // "PROBE"
#define FIL_RUNOUT_PIN PC2   // "E0-STOP"

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
#define findaPin X_STOP_PIN
#define colorSelectorEnstop Z_STOP_PIN
#endif

#ifdef  IR_ON_MMU
#define filamentSwitch FIL_RUNOUT_PIN
#endif

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

#define USB_CONNECT_PIN PC13
#define USB_CONNECT_INVERTING false