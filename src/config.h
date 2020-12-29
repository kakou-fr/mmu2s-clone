#ifndef CONFIG_H
#define CONFIG_H

          
#define SERIAL_INTERACTIVE  // allow to control the MMU from USB interface
#define DEBUG               // message debug on usb interface

//*************************************************************************************
//* General Settings (Don't touch)
//*************************************************************************************

#define S1_TRY_NUMBER   10         // Number of try to send start message each second (mmu<->printer) 

//STEPPER
#define ENABLE LOW                 // stepper motor enable is active low
#define DISABLE HIGH               // stepper motor disable is active high
#define PINHIGH 10                 // how long to hold stepper motor pin high in microseconds
#define PINLOW  10                 // how long to hold stepper motor pin low in microseconds
#define STEPSPERMM  144u           // these are the number of steps required to travel 1 mm using the extruder motor
#define FULL_STEP      1u
#define HALF_STEP      2u
#define QUARTER_STEP   4u
#define EIGTH_STEP     8u
#define SIXTEENTH_STEP 16u

//STEPPER MSTEP / REVOLUTION
#define STEPSIZE SIXTEENTH_STEP    // setup for each of the three stepper motors (set jumper or uart step)
#define STEPSPERREVOLUTION 200     // 200 steps per revolution  - 1.8 degree motors are being used

#define TIMEOUT_LOAD_UNLOAD 20000

//*************************************************************************************
//* Firmware version
//*************************************************************************************

//VERSION
#define MMU2_VERSION "6.0  16/12/21"
#define FW_VERSION 150             // config.h  (MM-control-01 firmware)
#define FW_BUILDNR 168             // config.h  (MM-control-01 firmware)

//*************************************************************************************
//* MMU version
//*************************************************************************************
// classic MMU2S    (idler, selector, extruder)
//#define MMU2S
// splitter version (without color selector, and need splitter)
#define MMU2_1S

//*************************************************************************************************
//  SENSORS
//*************************************************************************************************
#ifdef MMU2S
#define PindaON HIGH // pin state
#endif

//#define IR_ON_MMU // define if IR is connected on the MMU board, comment if IR is on printer board (last Marlin 2.0 bugfix)
#ifdef  IR_ON_MMU
#define filamentSwitchON LOW  // pin state
//#define FILAMENTSWITCH_BEFORE_EXTRUDER // turn on if the filament switch is before the extruder, turn off for the mk3s-mmu filament switch
#define FILAMENTSWITCH_ON_EXTRUDER       // turn on if the filament switch on is the extruder, turn on for the mk3s-mmu filament switch
#endif

//*************************************************************************************
//* LOADING PARAMETERS
//*************************************************************************************
#ifdef IR_ON_MMU
#define LOAD_DURATION 1000                 // duration of 'C' command during the load process (in milliseconds)
#define LOAD_SPEED 30                      // load speed (in mm/second) during the 'C' command (determined by Slic3r setting)
#define INSTRUCTION_DELAY 25               // delay (in microseconds) of the loop
#endif

#ifdef FILAMENTSWITCH_ON_EXTRUDER
#define FILAMENT_TO_MK3_C0_WAIT_TIME 2000  // time to wait between two C0
#endif

//*************************************************************************************
//* BOWDEN SIZE : customize it !!!
//*************************************************************************************
#ifdef MMU2S
#define DIST_MMU_EXTRUDER 690   // distance from PINDA to extruder gear (IR)
#endif

#ifdef MMU2_1S
#define DIST_MMU_EXTRUDER 120   // distance from tom of splitter to extruder gear
//#define FILAMENTSWITCH_BEFORE_EXTRUDER
#endif

#ifdef FILAMENTSWITCH_BEFORE_EXTRUDER
#define DIST_EXTRUDER_BTGEAR 50 // distance from IR to extruder gear
#endif


//*************************************************************************************
//* IDLER settings
//*************************************************************************************
#define IDLERSTEPSIZE 25         // steps to each roller bearing
#define IDLERMOTORDELAY  540     // 540 useconds     
#define MAXROLLERTRAVEL 125      // number of steps that the roller bearing stepper motor can travel


#ifdef MMU2S
//*************************************************************************************
//* SELECTOR settings
//*************************************************************************************
// this resets the selector stepper motor after the selected number of tool changes
#define TOOLSYNC 5                          // number of tool change (T) commands before a selector resync is performed
#define MAXSELECTOR_STEPS   1800            // maximum number of selector stepper motor (used to move all the way to the right or left
#define CSSTEPS 357                         // extruder steps
#define CS_RIGHT_FORCE 100                  // move more on left when homing
#define CS_RIGHT_FORCE_SELECTOR_0 5         // move more on left to touch the wall
#define COLORSELECTORMOTORDELAY 60          // 60 useconds    (selector motor)
#define UNLOAD_LENGTH_BACK_COLORSELECTOR 30 // Distance to restract the filament into the MMU 
#endif

//*************************************************************************************************
//  EXTRUDER settings
//*************************************************************************************************
#define EXTRUDERMOTORDELAY 120               // 120 useconds, controls filament feed speed to the printer

//*************************************************************************************************
//  TMC settings for TMC2209
//*************************************************************************************************
#define USE_TMC
#ifdef USE_TMC
#define HOLD_MULTIPLIER 0.5
#define TMC_BAUD_RATE 19200       // Reduce baud rate to improve software serial reliability
#define TMC_STEALTH_MODE true     // Stealh mode (true) or Spread mode (false)

#define USE_TMC_SENSORLESS
#define TMC_SG_THR_IDL     55     //12V value, tun it to your setup
#define TMC_SG_THR_SEL     115    //12V value, tun it to your setup
#endif

//*************************************************************************************************
//  Software RESET (only for STM board)
//*************************************************************************************************
// #define SOFTWARE_RESET

//*************************************************************************************************
//  BOARD
//*************************************************************************************************
// select the board used for the MMU
//  #include "boards/gt2560.h"
//  #include "boards/melzi.h"
//  #include "boards/skr-mini.h"
//  #include "boards/skr-mini-e3-1_2.h"
//  #include "boards/skr-mini-e3-2_0.h"
#include "boards/skr-mini-e3-dip-1_1.h"
//  #include "boards/skr-1.3.h"
//  #include "boards/skr-1.4.h"
//  #include "boards/skr-1.4-turbo.h"



//*************************************************************************************************
//  SERIAL <-> PRINTER  (Don't touch)
//*************************************************************************************************
#ifdef CDC_SERIAL
#include <CDCSerial.h>
#include <WString.h>
#define ConsoleSerial UsbSerial
#endif
#ifdef USB_SERIAL
  extern USBSerial SerialUSB;
  #define ConsoleSerial SerialUSB
#endif
#if !defined(CDC_SERIAL) && !defined(USB_SERIAL)
// AVR and other
#define ConsoleSerial Serial
#endif

//*************************************************************************************************

#endif
