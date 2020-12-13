#define USE_TMC
#define SOFTWARE_RESET

#ifdef USE_TMC
#define HOLD_MULTIPLIER    0.5
#define TMC_BAUD_RATE 19200 // Reduce baud rate to improve software serial reliability
#define TMC_STEALTH_MODE true

#define USE_TMC_SENSORLESS
#define TMC_SG_THR_IDL     20  //TMC2209 set to about 20, TMC2130 Set to about 19
#define TMC_SG_THR_SEL     50

//
// Software serial
//
#define SERIAL_TX_PIN                  PC10
#define SERIAL_RX_PIN                  PC11
#define X_SERIAL_ADDRESS                 0
#define Y_SERIAL_ADDRESS                 2
#define Z_SERIAL_ADDRESS                 1
#define E0_SERIAL_ADDRESS                3
#endif

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
#define colorSelectorStepPin Z_STEP_PIN
#define colorSelectorDirPin  Z_DIR_PIN
#define colorSelectorEnablePin Z_ENABLE_PIN
#define colorSelectorRMSCurrent 750
#define colorSelectorSerialRXPin SERIAL_RX_PIN
#define colorSelectorSerialTXPin SERIAL_TX_PIN
#define colorSelectorRSense Z_RSENSE
#define colorSelectorMicrosteps Z_MICROSTEPS
#define colorAddress Z_SERIAL_ADDRESS
#define colorSelectorEndstop Z_STOP_PIN
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
#define idlerEndstop Y_STOP_PIN

// Extruder stepper motor
#define extruderStepPin  X_STEP_PIN 
#define extruderDirPin  X_DIR_PIN
#define extruderEnablePin X_ENABLE_PIN
#define extruderRMSCurrent 750
#define extruderSerialRXPin SERIAL_RX_PIN
#define extruderSerialTXPin SERIAL_TX_PIN
#define extruderRSense X_RSENSE
#define extruderMicrosteps X_MICROSTEPS
#define extruderAddress X_SERIAL_ADDRESS


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

//#define USB_SERIAL

#define SerialPRINTER  Serial2

// #include <SoftwareSerial.h>
// #define SF_SERIAL
// #define SerialPRINTER Serials
// #define SSERIAL_RX PA3
// #define SSERIAL_TX PA2


#define USB_CONNECT_PIN                     PA14
#define USB_CONNECT_STATUS                  LOW