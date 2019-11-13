#ifndef APPLICATION_H
#define APPLICATION_H

#include <Arduino.h>

extern int isFilamentLoadedPinda();
extern bool isFilamentLoadedtoExtruder();

extern void initIdlerPosition();
extern void checkSerialInterface();
extern String ReadSerialStrUntilNewLine();
extern void initColorSelector();
extern void filamentLoadToMK3();
extern bool filamentLoadWithBondTechGear();
extern void toolChange( char selection);
extern void quickParkIdler();
extern void quickUnParkIdler();
extern void unParkIdler();
extern void unloadFilamentToFinda();
extern void parkIdler();
extern void activateColorSelector();
extern void deActivateColorSelector();
extern void idlerSelector(char filament);
extern void colorSelector(char selection);
extern void loadFilamentToFinda();
extern void fixTheProblem(String statement);
extern void csTurnAmount(int steps, int direction);
extern void feedFilament(unsigned int steps, int stoptoextruder);
extern void idlerturnamount(int steps, int dir);
extern void syncColorSelector();

class Application
{
public:
	Application();

	void setup();
	void loop();
};

#endif // APPLICATION_H
