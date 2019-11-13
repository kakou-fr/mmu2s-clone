#ifndef CONFIG_H
#define CONFIG_H


//#define DEBUG
#define DEBUGMODE


#define SERIAL1ENABLED    1
#define ENABLE LOW                // 8825 stepper motor enable is active low
#define DISABLE HIGH              // 8825 stepper motor disable is active high

#define MMU2_VERSION "5.0  10/11/19"

#define STEPSPERMM  144ul           // these are the number of steps required to travel 1 mm using the extruder motor

#define S1_WAIT_TIME 10  //wait time for serial 1 (mmu<->printer)

#define FW_VERSION 90             // config.h  (MM-control-01 firmware)
#define FW_BUILDNR 168             // config.h  (MM-control-01 firmware)

#define TIMEOUT_LOAD_UNLOAD 20000

// changed from 125 to 115 (10.13.18)
#define MAXROLLERTRAVEL 125         // number of steps that the roller bearing stepper motor can travel

#define FULL_STEP  1u
#define HALF_STEP  2u
#define QUARTER_STEP 4u
#define EIGTH_STEP 8u
#define SIXTEENTH_STEP 16u

//#define DIST_MMU_EXTRUDER 890
#define DIST_MMU_EXTRUDER 690
#define DIST_EXTRUDER_BTGEAR 30


#define STEPSIZE SIXTEENTH_STEP    // setup for each of the three stepper motors (jumper settings for M0,M1,M2) on the RAMPS 1.x board

#define STEPSPERREVOLUTION 200     // 200 steps per revolution  - 1.8 degree motors are being used


#define MMU2TOEXTRUDERSTEPS STEPSIZE*STEPSPERREVOLUTION*19   // for the 'T' command
                        // quick parked


//************************************************************************************
//* this resets the selector stepper motor after the selected number of tool changes
//*************************************************************************************
#define TOOLSYNC 5                         // number of tool change (T) commands before a selector resync is performed



#define PINHIGH 10                    // how long to hold stepper motor pin high in microseconds
#define PINLOW  10                    // how long to hold stepper motor pin low in microseconds



// the MMU2 currently runs at 21mm/sec (set by Slic3r) for 2 seconds (good stuff to know)
//
// the load duration was chagned from 1 second to 1.1 seconds on 10.8.18 (as an experiment)
// increased from 1.1 to 1.5 seconds on 10.13.18 (another experiment)
//1600
#define LOAD_DURATION 1000                 // duration of 'C' command during the load process (in milliseconds)
// changed from 21 mm/sec to 30 mm/sec on 10.13.18
#define LOAD_SPEED 30                   // load speed (in mm/second) during the 'C' command (determined by Slic3r setting)
#define INSTRUCTION_DELAY 25          // delay (in microseconds) of the loop
#define FILAMENT_TO_MK3_C0_WAIT_TIME 2000

// Distance to restract the filament into the MMU 
#define UNLOAD_LENGTH_BACK_COLORSELECTOR 30
//
int IDLEROFFSET[5] = {0,0,0,0,0};
#define IDLERSTEPSIZE 25         // steps to each roller bearing



// changed position #2 to 372  (still tuning this little sucker)

#define MAXSELECTOR_STEPS   1800//1890   // maximum number of selector stepper motor (used to move all the way to the right or left
int CSOFFSET[5] = {30,30,0,-15,-30};
#define CSSTEPS 357
#define CS_RIGHT_FORCE 20
#define CS_RIGHT_FORCE_SELECTOR_0 5

//*************************************************************************************************
//  Delay values for each stepper motor
//*************************************************************************************************
#define IDLERMOTORDELAY  540     //540 useconds      (idler motor)  was at '500' on 10.13.18
#define EXTRUDERMOTORDELAY 60//50     // 150 useconds    (controls filament feed speed to the printer)
#define COLORSELECTORMOTORDELAY 60 // 60 useconds    (selector motor)

#define SKRMINI
//#define GT2560


#define filamentSwitchON 0
//#define FILAMENTSWITCH_BEFORE_EXTRUDER // turn on if the filament switch is before the extruder, turn off for the mk3s-mmu filament switch
#define FILAMENTSWITCH_ON_EXTRUDER // turn on if the filament switch on is the extruder, turn on for the mk3s-mmu filament switch

#ifdef GT2560
// added this pin as a debug pin (lights a green LED so I can see the 'C0' command in action
//Y_MIN_PIN
#define greenLED 26

// modified code on 10.2.18 to accomodate RAMPS 1.6 board mapping
//

// PIN Y
#define idlerDirPin  33
#define idlerStepPin 31
#define idlerEnablePin 29


// PIN Z
#define extruderDirPin  39 //  pin 48 for extruder motor direction pin
#define extruderStepPin  37 //  pin 48 for extruder motor stepper motor pin
#define extruderEnablePin 35 //  pin A8 for extruder motor rst/sleep motor pin

//PIN X
#define colorSelectorDirPin  23 //color selector stepper motor (driven by trapezoidal screw)
#define colorSelectorStepPin 25
#define colorSelectorEnablePin 27


//BROWN = +5V
//BLUE = GND
//BLACK = SIGNAL
//SERVo PIN GT2560
#define findaPin  11

// Z_MIN_PIN
#define colorSelectorEnstop 30

// Z_MAX_PIN
#define filamentSwitch 32


// https://www.lesimprimantes3d.fr/forum/uploads/monthly_2018_10/Epson_29102018163351.jpg.9b3dec82b6691ac5af5c7ea2451e41b4.jpg
//Hardware Serial1 : 19 (RX) and 18 (TX)
// https://reprap.org/mediawiki/images/f/ff/MKS_MINI12864_LCD_controller_pin_out_-_signal_names.jpg
//https://www.geeetech.com/forum/download/file.php?id=3997&sid=b5aaf40b7a0b35fb5403798518f426b9
// 0 1 2 3 4
// 5 6 7 8 9
//
// https://reprap.org/mediawiki/images/5/51/RRD_FULL_GRAPHIC_SMART_CONTROLER_SCHEMATIC.pdf
//
// 19 : BTN_ENC -> EXP1 pin 0
// 18 : BEEPER_PIN -> EXP1 pin 5
//
//SoftwareSerial Serial1(10,11); // RX, TX (communicates with the MK3 controller boards


//SKR
// P.015 and P.16 (UART1)
#endif

#ifdef SKRMINI
// https://github.com/bigtreetech/BIGTREETECH-SKR-MINI-V1.1/blob/master/hardware/SKR-mini-V1.1-PIN.pdf
// added this pin as a debug pin (lights a green LED so I can see the 'C0' command in action
// Y_MIN_PIN
#define greenLED PC1

// modified code on 10.2.18 to accomodate RAMPS 1.6 board mapping
//


//PIN X
#define colorSelectorStepPin PC6
#define colorSelectorDirPin  PC7 //color selector stepper motor (driven by trapezoidal screw)
#define colorSelectorEnablePin PB15

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
#define colorSelectorEnstop PC0

// Z_MAX_PIN
#define filamentSwitch PC3
#endif

//SKR MINI
//TFT PIN
// RST RX0 TX0 GND +5V

//SKR
// P.015 and P.16 (UART1)

#endif // CONFIG_H
