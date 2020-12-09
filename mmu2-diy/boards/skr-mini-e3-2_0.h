#define USE_TMC

#define HOLD_MULTIPLIER    0.5
#define TMC_BAUD_RATE 19200 // Reduce baud rate to improve software serial reliability

#define SERIAL_TX_PIN                  PC10
#define SERIAL_RX_PIN                  PC11
#define X_SERIAL_ADDRESS                 0
#define Y_SERIAL_ADDRESS                 2
#define Z_SERIAL_ADDRESS                 1
#define E0_SERIAL_ADDRESS                3

//
// Steppers
//
#define X_ENABLE_PIN                        PB14
#define X_STEP_PIN                          PB13
#define X_DIR_PIN                           PB12
#define X_RSENSE                            0.11
#define X_MICROSTEPS                        16

#define Y_ENABLE_PIN                        PB11
#define Y_STEP_PIN                          PB10
#define Y_DIR_PIN                           PB2
#define Y_RSENSE                            0.11
#define Y_MICROSTEPS                        16

#define Z_ENABLE_PIN                        PB1
#define Z_STEP_PIN                          PB0
#define Z_DIR_PIN                           PC5
#define Z_RSENSE                            0.11
#define Z_MICROSTEPS                        16

#define E0_ENABLE_PIN                       PD2
#define E0_STEP_PIN                         PB3
#define E0_DIR_PIN                          PB4
#define E0_RSENSE                            0.11
#define E0_MICROSTEPS                        16

//
// Limit Switches
//
#define X_STOP_PIN                          PC0   // "X-STOP"
#define Y_STOP_PIN                          PC1   // "Y-STOP"
#define Z_STOP_PIN                          PC2   // "Z-STOP"
#define FIL_RUNOUT_PIN                      PC15  // "E0-STOP"

#ifdef MMU2S
// Color selector stepper motor (driven by trapezoidal screw)
#define colorSelectorStepPin X_STEP_PIN
#define colorSelectorDirPin  X_DIR_PIN
#define colorSelectorEnablePin X_ENABLE_PIN
#define colorSelectorRMSCurrent 750
#define colorSelectorSerialRXPin SERIAL_RX_PIN
#define colorSelectorSerialTXPin SERIAL_TX_PIN
#define colorSelectorRSense X_RSENSE
#define colorSelectorMicrosteps X_MICROSTEPS
#define colorAddress X_SERIAL_ADDRESS
#endif

// Roller selector stepper motor
#define idlerStepPin Y_STEP_PIN
#define idlerDirPin  Y_DIR_PIN
#define idlerEnablePin Y_ENABLE_PIN
#define idlerRMSCurrent 750
#define idlerSerialRXPin SERIAL_RX_PIN
#define idlerSerialTXPin SERIAL_TX_PIN
#define idlerRSense Y_RSENSE
#define idlerMicrosteps Y_MICROSTEPS
#define idlerAddress Y_SERIAL_ADDRESS

// Extruder stepper motor
#define extruderStepPin  E0_STEP_PIN 
#define extruderDirPin  E0_DIR_PIN
#define extruderEnablePin E0_ENABLE_PIN
#define extruderRMSCurrent 750
#define extruderSerialRXPin SERIAL_RX_PIN
#define extruderSerialTXPin SERIAL_TX_PIN
#define extruderRSense E0_RSENSE
#define extruderMicrosteps E0_MICROSTEPS
#define extruderAddress E0_SERIAL_ADDRESS


#define findaPin  X_STOP_PIN
#define greenLED Y_STOP_PIN // added this pin as a debug pin (lights a green LED so I can see the 'C0' command in action

#ifdef MMU2S
#define colorSelectorEnstop Z_STOP_PIN
#endif

#define filamentSwitch FIL_RUNOUT_PIN

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

#define USB_CONNECT_PIN                     PC13
#define USB_CONNECT_INVERTING false