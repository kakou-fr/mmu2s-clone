
//
// Software serial
//
#ifdef USE_TMC
#define X_SERIAL_TX_PIN                  PB15
#define X_SERIAL_RX_PIN                  PB15

#define Y_SERIAL_TX_PIN                  PC6
#define Y_SERIAL_RX_PIN                  PC6

#define Z_SERIAL_TX_PIN                  PC10
#define Z_SERIAL_RX_PIN                  PC10

#define E0_SERIAL_TX_PIN                 PC11
#define E0_SERIAL_RX_PIN                 PC11
#endif

//
// Steppers
//
#define X_ENABLE_PIN                        PB14
#define X_STEP_PIN                          PB13
#define X_DIR_PIN                           PB12
#ifdef USE_TMC
#define X_RSENSE                            0.11
#define X_MICROSTEPS                        16
#endif

#define Y_ENABLE_PIN                        PB11
#define Y_STEP_PIN                          PB10
#define Y_DIR_PIN                           PB2
#ifdef USE_TMC
#define Y_RSENSE                            0.11
#define Y_MICROSTEPS                        16
#endif

#define Z_ENABLE_PIN                        PB1
#define Z_STEP_PIN                          PB0
#define Z_DIR_PIN                           PC5
#ifdef USE_TMC
#define Z_RSENSE                            0.11
#define Z_MICROSTEPS                        16
#endif

#define E0_ENABLE_PIN                       PD2
#define E0_STEP_PIN                         PB3
#define E0_DIR_PIN                          PB4
#ifdef USE_TMC
#define E0_RSENSE                            0.11
#define E0_MICROSTEPS                        16
#endif

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
#ifdef USE_TMC
#define colorSelectorRMSCurrent 750
#define colorSelectorSerialRXPin X_SERIAL_RX_PIN
#define colorSelectorSerialTXPin X_SERIAL_TX_PIN
#define colorSelectorRSense X_RSENSE
#define colorSelectorMicrosteps X_MICROSTEPS
#define colorSelectorEndstop X_STOP_PIN
#endif
#define colorSelectorEndstop X_STOP_PIN
#endif

// Roller selector stepper motor
#define idlerStepPin Y_STEP_PIN
#define idlerDirPin  Y_DIR_PIN
#define idlerEnablePin Y_ENABLE_PIN
#ifdef USE_TMC
#define idlerRMSCurrent 750
#define idlerSerialRXPin Y_SERIAL_RX_PIN
#define idlerSerialTXPin Y_SERIAL_TX_PIN
#define idlerRSense Y_RSENSE
#define idlerMicrosteps Y_MICROSTEPS
#define idlerEndstop Y_STOP_PIN
#endif
#define idlerEndstop Y_STOP_PIN

// Extruder stepper motor
#define extruderStepPin  E0_STEP_PIN 
#define extruderDirPin  E0_DIR_PIN
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
#define findaPin Z_STOP_PIN
#endif

#ifdef  IR_ON_MMU
// Z_MAX_PIN
#define filamentSwitch FIL_RUNOUT_PIN
#endif

#define SerialPRINTER Serial2  //TFT PIN

#define USB_CONNECT_PIN                     PC13
#define USB_CONNECT_STATUS                  LOW