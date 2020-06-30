/*********************************************************************************************************
* MMU2 Clone Controller Version
**********************************************************************************************************
*
* Actual Code developed by Jeremy Briffaut
* Initial Code developed by Chuck Kozlowski
*/

#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "config.h"
#include "application.h"

/*************** */
char cstr[16];
#include "print.h"
IOPrint ioprint;
/*************** */

int command = 0;

// absolute position of bearing stepper motor
int bearingAbsPos[5] = {0 + IDLEROFFSET[0], IDLERSTEPSIZE + IDLEROFFSET[1], IDLERSTEPSIZE * 2 + IDLEROFFSET[2], IDLERSTEPSIZE * 3 + IDLEROFFSET[3], IDLERSTEPSIZE * 4 + IDLEROFFSET[4]};
#ifdef MMU2S
// absolute position of selector stepper motor
int selectorAbsPos[5] = {0 + CSOFFSET[0], CSSTEPS * 1 + CSOFFSET[1], CSSTEPS * 2 + CSOFFSET[2], CSSTEPS * 3 + CSOFFSET[3], CSSTEPS * 4 + CSOFFSET[4]};
#endif

//stepper direction
#define CW 0
#define CCW 1

// used for 3 states of the idler stepper motor (
#define INACTIVE 0	// parked
#define ACTIVE 1	  // not parked
#define QUICKPARKED 2 // quick parked

#define STOP_AT_EXTRUDER 1
#define IGNORE_STOP_AT_EXTRUDER 0

int trackToolChanges = 0;
int extruderMotorStatus = INACTIVE;

int currentCSPosition = 0; // color selector position
int currentPosition = 0;

int repeatTCmdFlag = INACTIVE; // used by the 'C' command processor to avoid processing multiple 'C' commands

int oldBearingPosition = 0; // this tracks the roller bearing position (top motor on the MMU)
int filamentSelection = 0;  // keep track of filament selection (0,1,2,3,4))
int dummy[100];
char currentExtruder = '0';

int firstTimeFlag = 0;
int earlyCommands = 0; // forcing communications with the mk3 at startup

int toolChangeCount = 0;

char receivedChar;
boolean newData = false;
int idlerStatus = INACTIVE;
int colorSelectorStatus = INACTIVE;

#ifdef MMU2_1S
	int findaStatus = 0;
#endif

/*****************************************************
 *
 * Init the MMU, pin, Serial, ...
 *
 *****************************************************/
void Application::setup()
{
	int waitCount;
	/************/
	ioprint.setup();
	/************/

	println_log(MMU2_VERSION);
	delay(200);

	SerialPRINTER.begin(115200); // Hardware serial interface (mmu<->printer board)
	delay(100);
	println_log(F("Sending START command to mk3 controller board"));
	// ***************************************
	// THIS NEXT COMMAND IS CRITICAL ... IT TELLS THE MK3 controller that an MMU is present
	// ***************************************
	SerialPRINTER.print(F("start\n")); // attempt to tell the mk3 that the mmu is present

	//***************************
	//  check the serial interface to see if it is active
	//***************************
	waitCount = 0;
	while (!SerialPRINTER.available())
	{
		println_log(F("Sending START command to mk3 controller board"));
    	println_log(F("Starting new beta v 1.0"));
		SerialPRINTER.print(F("start\n")); // attempt to tell the mk3 that the mmu is present
		println_log(F("Waiting for message from mk3"));
		delay(1000);
		++waitCount;
		if (waitCount >= S1_WAIT_TIME)
		{
			println_log(F("X seconds have passed, aborting wait for printer board (Marlin) to respond"));
			goto continue_processing;
		}
	}
	println_log(F("inbound message from Marlin"));

continue_processing:

	pinMode(idlerDirPin, OUTPUT);
	pinMode(idlerStepPin, OUTPUT);
	pinMode(idlerEnablePin, OUTPUT);

	pinMode(findaPin, INPUT);					// MMU pinda Filament sensor
	pinMode(filamentSwitch, INPUT);				// extruder Filament sensor
	pinMode(colorSelectorEnstop, INPUT_PULLUP); // enstop switch sensor

	pinMode(extruderEnablePin, OUTPUT);
	pinMode(extruderDirPin, OUTPUT);
	pinMode(extruderStepPin, OUTPUT);

#ifdef MMU2S
	pinMode(colorSelectorEnablePin, OUTPUT);
	pinMode(colorSelectorDirPin, OUTPUT);
	pinMode(colorSelectorStepPin, OUTPUT);
#endif

	pinMode(greenLED, OUTPUT); // green LED used for debug purposes

	println_log(F("finished setting up input and output pins"));

	// Turn OFF all three stepper motors (heat protection)
	digitalWrite(idlerEnablePin, DISABLE);		   // DISABLE the roller bearing motor (motor #1)
	digitalWrite(extruderEnablePin, DISABLE);	  //  DISABLE the extruder motor  (motor #2)
#ifdef MMU2S
	digitalWrite(colorSelectorEnablePin, DISABLE); // DISABLE the color selector motor  (motor #3)
#endif

	// Initialize stepper
	println_log(F("Syncing the Idler Selector Assembly")); // do this before moving the selector motor
	initIdlerPosition();								   // reset the roller bearing position

#ifdef MMU2S
	println_log(F("Syncing the Filament Selector Assembly"));
	if (!isFilamentLoadedPinda())
	{
		initColorSelector(); // reset the color selector if there is NO filament present
	}
	else
	{
		println_log(F("Unable to clear the Color Selector, please remove filament"));
	}
#endif

	println_log(F("Inialialization Complete, let's multicolor print ...."));

} // end of init() routine

/*****************************************************
 * 
 * infinite loop - core of the program
 *
 *****************************************************/
void Application::loop()
{
	String kbString;

	// wait for 100 milliseconds
	delay(100);
	// check the serial interface for input commands from the mk3
	checkSerialInterface();

#ifdef SERIAL_DEBUG
	// check for keyboard input

	if (Serial.available())
	{
		println_log(F("Key was hit "));

		kbString = ReadSerialStrUntilNewLine();
		// ignore protenface message
		if (kbString[0] == ':' || kbString[0] == 'M')
			return;
		print_log("Message received : '");
		println_log(kbString);
		print_log("'");
		if (kbString[0] == 'C')
		{
			println_log(F("Processing 'C' Command"));
			filamentLoadWithBondTechGear();
		}
		if (kbString[0] == 'T')
		{
			println_log(F("Processing 'T' Command"));
			if ((kbString[1] >= '0') && (kbString[1] <= '4'))
			{
				toolChange(kbString[1]);
			}
			else
			{
				println_log(F("T: Invalid filament Selection"));
			}
		}
		if (kbString[0] == 'U')
		{
			println_log(F("Processing 'U' Command"));
			if (idlerStatus == QUICKPARKED)
			{
				quickUnParkIdler(); // un-park the idler from a quick park
			}
			if (idlerStatus == INACTIVE)
			{
				unParkIdler(); // turn on the idler motor
			}
			unloadFilamentToFinda(); //unload the filament
			parkIdler();			 // park the idler motor and turn it off
		}
#ifdef DEBUGMODE
		if (kbString[0] == 'Z')
		{
			print_log(F("FINDA status: "));
			int fstatus = digitalRead(findaPin);
			println_log(fstatus);
			print_log(F("colorSelectorEnstop status: "));
			int cdenstatus = digitalRead(colorSelectorEnstop);
			println_log(cdenstatus);
			print_log(F("Extruder endstop status: "));
			fstatus = digitalRead(filamentSwitch);
			Serial.println(fstatus);
			println_log(F("PINDA | EXTRUDER"));
			while (true)
			{
				isFilamentLoadedPinda() ? print_log(F("ON    | ")) : print_log(F("OFF   | "));
				isFilamentLoadedtoExtruder() ? println_log(F("ON")) : println_log(F("OFF"));
				delay(200);
				if (Serial.available())
				{
					ReadSerialStrUntilNewLine();
					break;
				}
			}
		}
#endif
	}
#endif

} // end of infinite loop

/***************************************************************************************************************
 ***************************************************************************************************************
 * 
 * SERIAL
 * 
 ***************************************************************************************************************
 **************************************************************************************************************/

/*****************************************************
 * 
 * Serial read until new line
 * 
 *****************************************************/
String ReadSerialStrUntilNewLine()
{
	String str = "";
	char c = -1;
	while ((c != '\n') && (c != '\r'))
	{
		if (Serial.available())
		{
			c = char(Serial.read());
			if (c != -1)
			{
				str += c;
			}
		}
	}
	return str;
}

/*****************************************************
 *
 * Handle command from the Printer
 * 
 *****************************************************/
void checkSerialInterface()
{
	int cnt;
	String inputLine;
	int index;

	index = 0;
	if ((cnt = SerialPRINTER.available()) > 0)
	{

		inputLine = SerialPRINTER.readString(); // fetch the command from the mmu2 serial input interface

		if (inputLine[0] != 'P')
		{
			print_log(F("MMU Command: "));
			println_log(inputLine);
		}
	process_more_commands: // parse the inbound command
		unsigned char c1, c2;

		c1 = inputLine[index++]; // fetch single characer from the input line
		c2 = inputLine[index++]; // fetch 2nd character from the input line
		inputLine[index++];		 // carriage return

		// process commands coming from the mk3 controller
		//***********************************************************************************
		// Commands still to be implemented:
		// X0 (MMU Reset)
		// F0 (Filament type select),
		// E0->E4 (Eject Filament)
		// R0 (recover from eject)
		//***********************************************************************************
		switch (c1)
		{
		case 'T':
			// request for idler and selector based on filament number
			if ((c2 >= '0') && (c2 <= '4'))
			{
				toolChange(c2);
			}
			else
			{
				println_log(F("T: Invalid filament Selection"));
			}

			SerialPRINTER.print(F("ok\n")); // send command acknowledge back to mk3 controller
			break;
		case 'C':
			// move filament from selector ALL the way to printhead
			if (filamentLoadWithBondTechGear())
				SerialPRINTER.print(F("ok\n"));
			break;

		case 'U':
			// request for filament unload
			println_log(F("U: Filament Unload Selected"));
			if (idlerStatus == QUICKPARKED)
			{
				quickUnParkIdler(); // un-park the idler from a quick park
			}
			if (idlerStatus == INACTIVE)
			{
				unParkIdler(); // turn on the idler motor
			}
			if ((c2 >= '0') && (c2 <= '4'))
			{
				unloadFilamentToFinda();
				parkIdler();
				println_log(F("U: Sending Filament Unload Acknowledge to MK3"));
				delay(200);
				SerialPRINTER.print(F("ok\n"));
			}
			else
			{
				println_log(F("U: Invalid filament Unload Requested"));
				delay(200);
				SerialPRINTER.print(F("ok\n"));
			}
			break;
#ifdef MMU2S
		case 'L':
			// request for filament load
			println_log(F("L: Filament Load Selected"));
			if (idlerStatus == QUICKPARKED)
			{
				quickUnParkIdler(); // un-park the idler from a quick park
			}
			if (idlerStatus == INACTIVE)
			{
				unParkIdler(); // turn on the idler motor
			}
			if (colorSelectorStatus == INACTIVE)
				activateColorSelector(); // turn on the color selector motor
			if ((c2 >= '0') && (c2 <= '4'))
			{
				println_log(F("L: Moving the bearing idler"));
				idlerSelector(c2); // move the filament selector stepper motor to the right spot
				println_log(F("L: Moving the color selector"));
				colorSelector(c2); // move the color Selector stepper Motor to the right spot
				println_log(F("L: Loading the Filament"));
				loadFilamentToFinda();
				parkIdler(); // turn off the idler roller
				println_log(F("L: Sending Filament Load Acknowledge to MK3"));
				delay(200);
				SerialPRINTER.print(F("ok\n"));
			}
			else
			{
				println_log(F("Error: Invalid Filament Number Selected"));
			}
			break;
#endif
		case 'S':
			// request for firmware version
			switch (c2)
			{
			case '0':
				println_log(F("S: Sending back OK to MK3"));
				SerialPRINTER.print(F("ok\n"));
				break;
			case '1':
				println_log(F("S: FW Version Request"));
				SerialPRINTER.print(FW_VERSION);
				SerialPRINTER.print(F("ok\n"));
				break;
			case '2':
				println_log(F("S: Build Number Request"));
				println_log(F("Initial Communication with MK3 Controller: Successful"));
				SerialPRINTER.print(FW_BUILDNR);
				SerialPRINTER.print(F("ok\n"));
				break;
			default:
				println_log(F("S: Unable to process S Command"));
				break;
			}
			break;
		case 'P':
			// check FINDA status
			if (!isFilamentLoadedPinda())
			{
				SerialPRINTER.print(F("0"));
			}
			else
			{
				SerialPRINTER.print(F("1"));
			}
			SerialPRINTER.print(F("ok\n"));
			break;
		case 'F':
			// 'F' command is acknowledged but no processing goes on at the moment
			// will be useful for flexible material down the road
			println_log(F("Filament Type Selected: "));
			println_log(c2);
			SerialPRINTER.print(F("ok\n")); // send back OK to the mk3
			break;
		default:
			print_log(F("ERROR: unrecognized command from the MK3 controller"));
			SerialPRINTER.print(F("ok\n"));
		} // end of switch statement

	} // end of cnt > 0 check

	if (index < cnt)
	{
		goto process_more_commands;
	}
	// }  // check for early commands
}

/*****************************************************
 *
 * this routine is the common routine called for fixing the filament issues (loading or unloading)
 *
 *****************************************************/
void fixTheProblem(String statement)
{
	println_log(F(""));
	println_log(F("********************* ERROR ************************"));
	println_log(statement); // report the error to the user
	println_log(F("********************* ERROR ************************"));
	println_log(F("Clear the problem and then hit any key to continue "));
	println_log(F(""));
	println_log(F("PINDA | EXTRUDER"));
	isFilamentLoadedPinda() ? print_log(F("ON    | ")) : print_log(F("OFF   | "));
	isFilamentLoadedtoExtruder() ? println_log(F("ON")) : println_log(F("OFF"));
	println_log(F(""));
	//FIXME
	// IF POSSIBLE : 
	// SYNC COLORSELECTOR
	// SYNC IDLER
	parkIdler();								   // park the idler stepper motor
#ifdef MMU2S
	digitalWrite(colorSelectorEnablePin, DISABLE); // turn off the selector stepper motor
#endif

#ifdef SERIAL_DEBUG
	while (!Serial.available())
	{
		//  wait until key is entered to proceed  (this is to allow for operator intervention)
	}
	Serial.readString(); // clear the keyboard buffer
#endif

	unParkIdler();								  // put the idler stepper motor back to its' original position
#ifdef MMU2S
	digitalWrite(colorSelectorEnablePin, ENABLE); // turn ON the selector stepper motor
#endif
	delay(1);									  // wait for 1 millisecond
}

#ifdef MMU2S
/***************************************************************************************************************
 ***************************************************************************************************************
 * 
 * COLOR SELECTOR
 * 
 ***************************************************************************************************************
 **************************************************************************************************************/

/*****************************************************
 *
 * Select the color : selection (0..4)
 * 
 *****************************************************/

/*****************************************************
 *
 *
 *****************************************************/
void deActivateColorSelector()
{
//FIXME : activate it by default
#ifdef TURNOFFSELECTORMOTOR
	digitalWrite(colorSelectorEnablePin, DISABLE); // turn off the color selector stepper motor  (nice to do, cuts down on CURRENT utilization)
	delay(1);
	colorSelectorStatus = INACTIVE;
#endif
}

/*****************************************************
 *
 *
 *****************************************************/
void activateColorSelector()
{
	digitalWrite(colorSelectorEnablePin, ENABLE);
	delay(1);
	colorSelectorStatus = ACTIVE;
}

void colorSelector(char selection)
{
	if ((selection < '0') || (selection > '4'))
	{
		println_log(F("colorSelector():  Error, invalid filament selection"));
		return;
	}
loop:
	if (isFilamentLoadedPinda())
	{
		fixTheProblem("colorSelector(): Error, filament is present between the MMU2 and the MK3 Extruder:  UNLOAD FILAMENT!!");
		goto loop;
	}

	switch (selection)
	{
	case '0':
		// position '0' is always just a move to the left
		// the '+CS_RIGHT_FORCE_SELECTOR_0' is an attempt to move the selector ALL the way left (puts the selector into known position)
		csTurnAmount(currentPosition + CS_RIGHT_FORCE_SELECTOR_0, CCW);
		// Apply CSOFFSET
		csTurnAmount((selectorAbsPos[0]), CW);
		currentPosition = selectorAbsPos[0];
		break;
	case '1':
		if (currentPosition <= selectorAbsPos[1])
		{
			csTurnAmount((selectorAbsPos[1] - currentPosition), CW);
		}
		else
		{
			csTurnAmount((currentPosition - selectorAbsPos[1]), CCW);
		}
		currentPosition = selectorAbsPos[1];
		break;
	case '2':
		if (currentPosition <= selectorAbsPos[2])
		{
			csTurnAmount((selectorAbsPos[2] - currentPosition), CW);
		}
		else
		{
			csTurnAmount((currentPosition - selectorAbsPos[2]), CCW);
		}
		currentPosition = selectorAbsPos[2];
		break;
	case '3':
		if (currentPosition <= selectorAbsPos[3])
		{
			csTurnAmount((selectorAbsPos[3] - currentPosition), CW);
		}
		else
		{
			csTurnAmount((currentPosition - selectorAbsPos[3]), CCW);
		}
		currentPosition = selectorAbsPos[3];
		break;
	case '4':
		if (currentPosition <= selectorAbsPos[4])
		{
			csTurnAmount((selectorAbsPos[4] - currentPosition), CW);
		}
		else
		{
			csTurnAmount((currentPosition - selectorAbsPos[4]), CCW);
		}
		currentPosition = selectorAbsPos[4];
		break;
	}

} // end of colorSelector routine()

/*****************************************************
 *
 * this is the selector motor with the lead screw (final stage of the MMU2 unit)
 * 
 *****************************************************/
void csTurnAmount(int steps, int direction)
{

	digitalWrite(colorSelectorEnablePin, ENABLE); // turn on the color selector motor
	if (direction == CW)
		digitalWrite(colorSelectorDirPin, LOW); // set the direction for the Color Extruder Stepper Motor
	else
		digitalWrite(colorSelectorDirPin, HIGH);
	// FIXME ??? NEEDED ???
	// wait 1 milliseconds
	delayMicroseconds(1500); // changed from 500 to 1000 microseconds on 10.6.18, changed to 1500 on 10.7.18)

#ifdef DEBUG
	int scount;
	print_log(F("raw steps: "));
	println_log(steps);

	scount = steps * STEPSIZE;
	print_log(F("total number of steps: "));
	println_log(scount);
#endif

	for (uint16_t i = 0; i <= (steps * STEPSIZE); i++)
	{
		digitalWrite(colorSelectorStepPin, HIGH);
		delayMicroseconds(PINHIGH); // delay for 10 useconds
		digitalWrite(colorSelectorStepPin, LOW);
		delayMicroseconds(PINLOW);					// delay for 10 useconds
		delayMicroseconds(COLORSELECTORMOTORDELAY); // wait for 60 useconds
		//add enstop
		if ((digitalRead(colorSelectorEnstop) == LOW) && (direction == CW))
			break;
	}

#ifdef TURNOFFSELECTORMOTOR
	digitalWrite(colorSelectorEnablePin, DISABLE); // turn off the color selector motor
#endif
}

/*****************************************************
 *
 * Home the Color Selector
 * perform this function only at power up/reset
 * 
 *****************************************************/
void initColorSelector()
{

	digitalWrite(colorSelectorEnablePin, ENABLE);		   // turn on the stepper motor
	delay(1);											   // wait for 1 millisecond
	csTurnAmount(MAXSELECTOR_STEPS, CW);				   // move to the right
	csTurnAmount(MAXSELECTOR_STEPS + CS_RIGHT_FORCE, CCW); // move all the way to the left
	digitalWrite(colorSelectorEnablePin, DISABLE);		   // turn off the stepper motor
}

/*****************************************************
 *
 * Re-Sync Color Selector
 * this function is performed by the 'T' command after so many moves to make sure the colorselector is synchronized
 *
 *****************************************************/
void syncColorSelector()
{
	int moveSteps;

	digitalWrite(colorSelectorEnablePin, ENABLE); // turn on the selector stepper motor
	delay(1);									  // wait for 1 millecond

	print_log(F("syncColorSelelector()   current Filament selection: "));
	println_log(filamentSelection);

	moveSteps = MAXSELECTOR_STEPS - selectorAbsPos[filamentSelection];

	print_log(F("syncColorSelector()   moveSteps: "));
	println_log(moveSteps);

	csTurnAmount(moveSteps, CW);						   // move all the way to the right
	csTurnAmount(MAXSELECTOR_STEPS + CS_RIGHT_FORCE, CCW); // move all the way to the left
														   //FIXME : turn off motor ???
														   //digitalWrite(colorSelectorEnablePin, DISABLE); // turn off the stepper motor
}
#endif
/***************************************************************************************************************
 ***************************************************************************************************************
 * 
 * IDLER
 * 
 ***************************************************************************************************************
 **************************************************************************************************************/

/*****************************************************
 *
 * Home the idler
 * perform this function only at power up/reset
 *
 *****************************************************/
void initIdlerPosition()
{

	digitalWrite(idlerEnablePin, ENABLE); // turn on the roller bearing motor
	delay(1);
	oldBearingPosition = 125; // points to position #1
	idlerturnamount(MAXROLLERTRAVEL, CW);
	idlerturnamount(MAXROLLERTRAVEL, CCW); // move the bearings out of the way
	digitalWrite(idlerEnablePin, DISABLE); // turn off the idler roller bearing motor

	filamentSelection = 0; // keep track of filament selection (0,1,2,3,4))
	currentExtruder = '0';
}

/*****************************************************
 *
 * this routine drives the 5 position bearings (aka idler, on the top of the MMU2 carriage)
 * filament 0..4 -> the position
 *
 *****************************************************/
void idlerSelector(char filament)
{
	int newBearingPosition;
	int newSetting;

#ifdef DEBUG
	print_log(F("idlerSelector(): Filament Selected: "));
	println_log(filament);
#endif

	digitalWrite(extruderEnablePin, ENABLE);
	if ((filament < '0') || (filament > '4'))
	{
		println_log(F("idlerSelector() ERROR, invalid filament selection"));
		print_log(F("idlerSelector() filament: "));
		println_log(filament);
		return;
	}

#ifdef DEBUG
	print_log(F("Old Idler Roller Bearing Position:"));
	println_log(oldBearingPosition);
	println_log(F("Moving filament selector"));
#endif

	switch (filament)
	{
	case '0':
		newBearingPosition = bearingAbsPos[0]; // idler set to 1st position
		filamentSelection = 0;
		currentExtruder = '0';
		break;
	case '1':
		newBearingPosition = bearingAbsPos[1];
		filamentSelection = 1;
		currentExtruder = '1';
		break;
	case '2':
		newBearingPosition = bearingAbsPos[2];
		filamentSelection = 2;
		currentExtruder = '2';
		break;
	case '3':
		newBearingPosition = bearingAbsPos[3];
		filamentSelection = 3;
		currentExtruder = '3';
		break;
	case '4':
		newBearingPosition = bearingAbsPos[4];
		filamentSelection = 4;
		currentExtruder = '4';
		break;
	default:
		println_log(F("idlerSelector(): ERROR, Invalid Idler Bearing Position"));
		break;
	}

	newSetting = newBearingPosition - oldBearingPosition;
	if (newSetting < 0)
		idlerturnamount(-newSetting, CW); // turn idler to appropriate position
	else
		idlerturnamount(newSetting, CCW); // turn idler to appropriate position
	oldBearingPosition = newBearingPosition;
}

/*****************************************************
 *
 * turn the idler stepper motor
 * 
 *****************************************************/
void idlerturnamount(int steps, int dir)
{
	digitalWrite(idlerEnablePin, ENABLE); // turn on motor
	digitalWrite(idlerDirPin, dir);
	delay(1); // wait for 1 millisecond

	// these command actually move the IDLER stepper motor
	for (uint16_t i = 0; i < steps * STEPSIZE; i++)
	{
		digitalWrite(idlerStepPin, HIGH);
		delayMicroseconds(PINHIGH); // delay for 10 useconds
		digitalWrite(idlerStepPin, LOW);
		//delayMicroseconds(PINLOW);               // delay for 10 useconds
		delayMicroseconds(IDLERMOTORDELAY);
	}
} // end of idlerturnamount() routine

/***************************************************************************************************************
 ***************************************************************************************************************
 * 
 * EXTRUDER
 * 
 ***************************************************************************************************************
 **************************************************************************************************************/

/*****************************************************
 *
 * this routine feeds filament by the amount of steps provided
 * stoptoextruder when mk3 switch detect it (only if switch is before mk3 gear)
 * 144 steps = 1mm of filament (using the current mk8 gears in the MMU2)
 *
 *****************************************************/
void feedFilament(unsigned int steps, int stoptoextruder)
{
	for (unsigned int i = 0; i <= steps; i++)
	{
		digitalWrite(extruderStepPin, HIGH);
		delayMicroseconds(PINHIGH); // delay for 10 useconds
		digitalWrite(extruderStepPin, LOW);
		delayMicroseconds(PINLOW); // delay for 10 useconds

		delayMicroseconds(EXTRUDERMOTORDELAY); // wait for 400 useconds
		//delay(delayValue);           // wait for 30 milliseconds
		if ((stoptoextruder) && isFilamentLoadedtoExtruder())
			break;
	}
}

/***************************************************************************************************************
 ***************************************************************************************************************
 * 
 * FILAMENT SENSORS
 * 
 ***************************************************************************************************************
 **************************************************************************************************************/

/*****************************************************
 *
 * Check if Filament is loaded into MMU pinda
 *
 *****************************************************/
int isFilamentLoadedPinda()
{
	int findaStatus;
	findaStatus = digitalRead(findaPin);
	return (findaStatus == PindaON);
}

/*****************************************************
 *
 * Check if Filament is loaded into extruder
 *
 *****************************************************/
bool isFilamentLoadedtoExtruder()
{
#ifdef MMU2S
	int fStatus;
	fStatus = digitalRead(filamentSwitch);
	return (fStatus == filamentSwitchON);
#endif
#ifdef MMU2_1S
	return findaStatus;
#endif
}

/***************************************************************************************************************
 ***************************************************************************************************************
 * 
 * LOAD / UNLOAD FILAMENT
 * 
 ***************************************************************************************************************
 **************************************************************************************************************/

#ifdef MMU2S
/*****************************************************
 *
 * Load the Filament using the FINDA and go back to MMU
 * 
 *****************************************************/
void loadFilamentToFinda()
{
	unsigned long startTime, currentTime;

	digitalWrite(extruderEnablePin, ENABLE);
	digitalWrite(extruderDirPin, CCW); // set the direction of the MMU2 extruder motor
	delay(1);

	startTime = millis();

loop:
	currentTime = millis();
	if ((currentTime - startTime) > 10000)
	{ // 10 seconds worth of trying to load the filament
		fixTheProblem("UNLOAD FILAMENT ERROR:   timeout error, filament is not loaded to the FINDA sensor");
		startTime = millis(); // reset the start time clock
	}

	// go 144 steps (1 mm) and then check the finda status
	feedFilament(STEPSPERMM, STOP_AT_EXTRUDER);

	// keep feeding the filament until the pinda sensor triggers
	if (!isFilamentLoadedPinda())
		goto loop;
	//
	// for a filament load ... need to get the filament out of the selector head !!
	//
	digitalWrite(extruderDirPin, CW); // back the filament away from the selector
	// after hitting the FINDA sensor, back away by UNLOAD_LENGTH_BACK_COLORSELECTOR mm
	feedFilament(STEPSPERMM * UNLOAD_LENGTH_BACK_COLORSELECTOR, IGNORE_STOP_AT_EXTRUDER);
}

#endif
/*****************************************************
 *
 * unload Filament using the FINDA sensor and push it in the MMU
 * 
 *****************************************************/
void unloadFilamentToFinda()
{
	unsigned long startTime, currentTime, startTime1;
	// if the filament is already unloaded, do nothing
	if (!isFilamentLoadedPinda())
	{
		println_log(F("unloadFilamentToFinda():  filament already unloaded"));
		return;
	}

	digitalWrite(extruderEnablePin, ENABLE); // turn on the extruder motor
	digitalWrite(extruderDirPin, CW);		 // set the direction of the MMU2 extruder motor
	delay(1);

	startTime = millis();
	startTime1 = millis();

#ifdef MMU2S
loop:
#endif

	currentTime = millis();

	// read the filament switch (on the top of the mk3 extruder)
	if (isFilamentLoadedtoExtruder())
	{
		// filament Switch is still ON, check for timeout condition
		if ((currentTime - startTime1) > 2000)
		{ // has 2 seconds gone by ?
			fixTheProblem("unloadFilamentToFinda(): UNLOAD FILAMENT ERROR: filament not unloading properly, stuck in mk3 head");
			startTime1 = millis();
		}
	}
	else
	{
		// check for timeout waiting for FINDA sensor to trigger
		if ((currentTime - startTime) > TIMEOUT_LOAD_UNLOAD)
		{
			// 10 seconds worth of trying to unload the filament
			fixTheProblem("unloadFilamentToFinda(): UNLOAD FILAMENT ERROR: filament is not unloading properly, stuck between mk3 and mmu2");
			startTime = millis(); // reset the start time
		}
	}

#ifdef MMU2S
	feedFilament(STEPSPERMM, IGNORE_STOP_AT_EXTRUDER); // 1mm and then check the pinda status

	// keep unloading until we hit the FINDA sensor
	if (isFilamentLoadedPinda())
	{
		goto loop;
	}

	// back the filament away from the selector by UNLOAD_LENGTH_BACK_COLORSELECTOR mm
	digitalWrite(extruderDirPin, CW);
	feedFilament(STEPSPERMM * UNLOAD_LENGTH_BACK_COLORSELECTOR, IGNORE_STOP_AT_EXTRUDER);
#endif
#ifdef MMU2_1S
	digitalWrite(extruderDirPin, CW);
	feedFilament(STEPSPERMM * DIST_MMU_EXTRUDER, IGNORE_STOP_AT_EXTRUDER);
	findaStatus = 0;
#endif
}


/***************************************************************************************************************
 ***************************************************************************************************************
 * 
 * PARK / UNPARK IDLER
 * 
 ***************************************************************************************************************
 **************************************************************************************************************/

/*****************************************************
 *
 * move the filament Roller pulleys away from the filament
 *
 *****************************************************/
void parkIdler()
{
	int newSetting;

	digitalWrite(idlerEnablePin, ENABLE);
	delay(1);

	newSetting = MAXROLLERTRAVEL - oldBearingPosition;
	oldBearingPosition = MAXROLLERTRAVEL; // record the current roller status  (CSK)

	idlerturnamount(newSetting, CCW); // move the bearing roller out of the way
	idlerStatus = INACTIVE;

	digitalWrite(idlerEnablePin, DISABLE);	// turn off the roller bearing stepper motor  (nice to do, cuts down on CURRENT utilization)
	digitalWrite(extruderEnablePin, DISABLE); // turn off the extruder stepper motor as well
}

/*****************************************************
 *
 *
 *****************************************************/
void unParkIdler()
{
	int rollerSetting;

	digitalWrite(idlerEnablePin, ENABLE); // turn on (enable) the roller bearing motor
	delay(1);							  // wait for 10 useconds

	rollerSetting = MAXROLLERTRAVEL - bearingAbsPos[filamentSelection];
	oldBearingPosition = bearingAbsPos[filamentSelection]; // update the idler bearing position

	idlerturnamount(rollerSetting, CW); // restore the old position
	idlerStatus = ACTIVE;				// mark the idler as active

	digitalWrite(extruderEnablePin, ENABLE); // turn on (enable) the extruder stepper motor as well
}

/*****************************************************
 *
 * attempt to disengage the idler bearing after a 'T' command instead of parking the idler
 * this is trying to save significant time on re-engaging the idler when the 'C' command is activated
 *
 *****************************************************/
void quickParkIdler()
{

	digitalWrite(idlerEnablePin, ENABLE); // turn on the idler stepper motor
	delay(1);

	idlerturnamount(IDLERSTEPSIZE, CCW);

	oldBearingPosition = oldBearingPosition + IDLERSTEPSIZE; // record the current position of the IDLER bearing
	idlerStatus = QUICKPARKED;								 // use this new state to show the idler is pending the 'C0' command

	//FIXME : Turn off idler ?
	//digitalWrite(idlerEnablePin, DISABLE);    // turn off the roller bearing stepper motor  (nice to do, cuts down on CURRENT utilization)
	digitalWrite(extruderEnablePin, DISABLE); // turn off the extruder stepper motor as well
}

/*****************************************************
 *
 * this routine is called by the 'C' command to re-engage the idler bearing
 *
 * FIXME: needed ?
 *****************************************************/
void quickUnParkIdler()
{
	int rollerSetting;

	rollerSetting = oldBearingPosition - IDLERSTEPSIZE; // go back IDLERSTEPSIZE units (hopefully re-enages the bearing

	idlerturnamount(IDLERSTEPSIZE, CW); // restore old position

	print_log(F("quickunparkidler(): oldBearingPosition"));
	println_log(oldBearingPosition);

	oldBearingPosition = rollerSetting - IDLERSTEPSIZE; // keep track of the idler position

	idlerStatus = ACTIVE; // mark the idler as active
}

/***************************************************************************************************************
 ***************************************************************************************************************
 * 
 * TOOLCHANGE / LOAD TO MK3 / LOAD TO BONTECH GEAR
 * 
 ***************************************************************************************************************
 **************************************************************************************************************/

/*****************************************************
 *
 * (T) Tool Change Command - this command is the core command used my the mk3 to drive the mmu2 filament selection
 *
 *****************************************************/
void toolChange(char selection)
{
	int newExtruder;

	++toolChangeCount; // count the number of tool changes
	++trackToolChanges;

	// automatic reset of the tracktoolchange counter since going to filament position '0' move the color selection ALL the way to the left
	if (selection == '0')
	{
		trackToolChanges = 0;
	}

	print_log(F("Tool Change Count: "));
	println_log(toolChangeCount);

	newExtruder = selection - 0x30; // convert ASCII to a number (0-4)

	if (newExtruder == filamentSelection)
	{ // already at the correct filament selection
		if (!isFilamentLoadedPinda())
		{ // no filament loaded

			println_log(F("toolChange: filament not currently loaded, loading ..."));

			idlerSelector(selection); // move the filament selector stepper motor to the right spot
#ifdef MMU2S
			colorSelector(selection); // move the color Selector stepper Motor to the right spot
#endif
			filamentLoadToMK3();
			quickParkIdler();
			repeatTCmdFlag = INACTIVE; // used to help the 'C' command to feed the filament again
		}
		else
		{
			println_log(F("toolChange:  filament already loaded to mk3 extruder"));
			repeatTCmdFlag = ACTIVE; // used to help the 'C' command to not feed the filament again
		}
	}
	else
	{
		// different filament position
		repeatTCmdFlag = INACTIVE; // turn off the repeat Commmand Flag (used by 'C' Command)
		if (isFilamentLoadedPinda())
		{

			println_log(F("toolChange: Unloading filament"));

			idlerSelector(currentExtruder); // point to the current extruder
			unloadFilamentToFinda();		// have to unload the filament first
		}

#ifdef MMU2S
		// reset the color selector stepper motor (gets out of alignment)
		if (trackToolChanges > TOOLSYNC)
		{
			println_log(F("toolChange: Synchronizing the Filament Selector Head"));
			syncColorSelector();
			//FIXME : add syncIdlerSelector here
			activateColorSelector(); // turn the color selector motor back on
			currentPosition = 0;	 // reset the color selector
			trackToolChanges = 0;
		}
#endif
#ifdef DEBUG
		println_log(F("toolChange: Selecting the proper Idler Location"));
#endif
		idlerSelector(selection);
#ifdef DEBUG
		println_log(F("toolChange: Selecting the proper Selector Location"));
#endif
#ifdef MMU2S
		colorSelector(selection);
#endif
#ifdef DEBUG
		println_log(F("toolChange: Loading Filament: loading the new filament to the mk3"));
#endif
		filamentLoadToMK3(); // moves the idler and loads the filament
		filamentSelection = newExtruder;
		currentExtruder = selection;
		quickParkIdler();
	}
} // end of ToolChange processing

/*****************************************************
 *
 * this routine is executed as part of the 'T' Command (Load Filament)
 *
 *****************************************************/
void filamentLoadToMK3()
{
#ifdef FILAMENTSWITCH_BEFORE_EXTRUDER
	int flag;
	int fStatus;
	int filamentDistance;
#endif
	if ((currentExtruder < '0') || (currentExtruder > '4'))
	{
		println_log(F("filamentLoadToMK3(): fixing current extruder variable"));
		currentExtruder = '0';
	}
#ifdef DEBUG
	println_log(F("Attempting to move Filament to Print Head Extruder Bondtech Gears"));
	//unParkIdler();
	print_log(F("filamentLoadToMK3():  currentExtruder: "));
	println_log(currentExtruder);
#endif

#ifdef MMU2S
	deActivateColorSelector();
#endif

	digitalWrite(extruderEnablePin, ENABLE); // turn on the extruder stepper motor (10.14.18)
	digitalWrite(extruderDirPin, CCW);		 // set extruder stepper motor to push filament towards the mk3
	delay(1);								 // wait 1 millisecond

#ifdef MMU2S
	int startTime, currentTime;
	startTime = millis();
	
loop:
	feedFilament(STEPSPERMM, IGNORE_STOP_AT_EXTRUDER); // feed 1 mm of filament into the bowden tube

	currentTime = millis();

	// added this timeout feature on 10.4.18 (2 second timeout)
	if ((currentTime - startTime) > 2000)
	{
		fixTheProblem("FILAMENT LOAD ERROR:  Filament not detected by FINDA sensor, check the selector head in the MMU2");

		startTime = millis();
	}
	// keep feeding the filament until the pinda sensor triggers
	if (!isFilamentLoadedPinda())
		goto loop;
#endif
#ifdef MMU2_1S
	findaStatus = 1;
#endif

loop1:
	if (isFilamentLoadedtoExtruder())
	{
		// switch is active (this is not a good condition)
		fixTheProblem("FILAMENT LOAD ERROR: Filament Switch in the MK3 is active (see the RED LED), it is either stuck open or there is debris");
		goto loop1;
	}

	// go DIST_MMU_EXTRUDER mm
	feedFilament(STEPSPERMM * DIST_MMU_EXTRUDER, STOP_AT_EXTRUDER);


#ifdef FILAMENTSWITCH_BEFORE_EXTRUDER
	// insert until the 2nd filament sensor
	filamentDistance = DIST_MMU_EXTRUDER;
	startTime = millis();
	flag = 0;

	// wait until the filament sensor on the mk3 extruder head (microswitch) triggers
	while (flag == 0)
	{

		currentTime = millis();
		if ((currentTime - startTime) > TIMEOUT_LOAD_UNLOAD)
		{
			fixTheProblem("FILAMENT LOAD ERROR: Filament not detected by the MK3 filament sensor, check the bowden tube for clogging/binding");
			startTime = millis(); // reset the start Time
		}
		feedFilament(STEPSPERMM, STOP_AT_EXTRUDER); // step forward 1 mm
		filamentDistance++;
		// read the filament switch on the mk3 extruder
		if (isFilamentLoadedtoExtruder())
		{
			flag = 1;
			print_log(F("Filament distance traveled (mm): "));
			println_log(filamentDistance);
		}
	}

	// feed filament an additional DIST_EXTRUDER_BTGEAR mm to hit the middle of the bondtech gear
	// go an additional DIST_EXTRUDER_BTGEAR
	feedFilament(STEPSPERMM * DIST_EXTRUDER_BTGEAR, IGNORE_STOP_AT_EXTRUDER);
#endif
}

/*****************************************************
 *
 * part of the 'C' command,  does the last little bit to load into the past the extruder gear
 *
 *****************************************************/
bool filamentLoadWithBondTechGear()
{
	int i;
	int delayFactor; // delay factor (in microseconds) for the filament load loop
	int stepCount;
	int tSteps;

	// added this code snippet to not process a 'C' command that is essentially a repeat command
	if (repeatTCmdFlag == ACTIVE)
	{
		println_log(F("filamentLoadWithBondTechGear(): filament already loaded and 'C' command already processed"));
		repeatTCmdFlag = INACTIVE;
		return false;
	}

	if (!isFilamentLoadedPinda())
	{
		println_log(F("filamentLoadWithBondTechGear()  Error, filament sensor thinks there is no filament"));
		return false;
	}

	if ((currentExtruder < '0') || (currentExtruder > '4'))
	{
		println_log(F("filamentLoadWithBondTechGear(): fixing current extruder variable"));
		currentExtruder = '0';
	}

	if (idlerStatus == QUICKPARKED)
	{
		quickUnParkIdler();
	}
	if (idlerStatus == INACTIVE)
	{
		unParkIdler();
	}

	stepCount = 0;
	digitalWrite(greenLED, HIGH); // turn on the green LED (for debug purposes)

	// feed the filament from the MMU2 into the bondtech gear
	tSteps = STEPSPERMM * ((float)LOAD_DURATION / 1000.0) * LOAD_SPEED;			// compute the number of steps to take for the given load duration
	delayFactor = (float(LOAD_DURATION * 1000.0) / tSteps) - INSTRUCTION_DELAY; // delayFactor algorithm

	digitalWrite(extruderEnablePin, ENABLE); // turn on the extruder stepper motor
	digitalWrite(extruderDirPin, CCW);		 // set extruder stepper motor to push filament towards the mk3

	for (i = 0; i < tSteps; i++)
	{
		digitalWrite(extruderStepPin, HIGH); // step the extruder stepper in the MMU2 unit
		delayMicroseconds(PINHIGH);
		digitalWrite(extruderStepPin, LOW);
		delayMicroseconds(delayFactor);
		++stepCount;
	}
	digitalWrite(greenLED, LOW); // turn off the green LED (for debug purposes)

#ifdef DEBUG
	println_log(F("C Command: parking the idler"));
#endif

	parkIdler();

#ifdef FILAMENTSWITCH_ON_EXTRUDER
	//Wait for MMU code in Marlin to load the filament and activate the filament switch
	delay(FILAMENT_TO_MK3_C0_WAIT_TIME);
	if (isFilamentLoadedtoExtruder())
	{
		println_log(F("filamentLoadWithBondTechGear(): Loading Filament to Print Head Complete"));
		return true;
	}
	println_log(F("filamentLoadWithBondTechGear() : FILAMENT LOAD ERROR:  Filament not detected by EXTRUDER sensor, check the EXTRUDER"));
	return false;
#endif

#ifdef DEBUG
	println_log(F("filamentLoadWithBondTechGear(): Loading Filament to Print Head Complete"));
#endif
	return true;
}

/************************************************************************************************************/
/************************************************************************************************************/
/************************************************************************************************************/

/*
 * Nothing to do in the constructor
 */
Application::Application()
{
	// nothing to do in the constructor
}
