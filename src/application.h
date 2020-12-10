#ifndef APPLICATION_H
#define APPLICATION_H

#include <Arduino.h>

extern int isFilamentLoadedPinda();
extern bool isFilamentLoadedtoExtruder();

extern void checkSerialInterface();
extern String ReadSerialStrUntilNewLine();

extern void filamentLoadToMK3();
extern bool filamentLoadWithBondTechGear();
extern void toolChange( char selection);
extern void fixTheProblem(const char* statement);
extern void feedFilament(unsigned int steps, int stoptoextruder);

extern void initIdlerPosition();
extern void quickParkIdler();
extern void quickUnParkIdler();
extern void unParkIdler();
extern void parkIdler();
extern void idlerSelector(char filament);
extern void idlerturnamount(int steps, int dir);

extern void unloadFilamentToFinda();
#ifdef MMU2S
extern void loadFilamentToFinda();

extern void activateColorSelector();
extern void deActivateColorSelector();
extern void colorSelector(char selection);
extern void csTurnAmount(int steps, int direction);
extern void initColorSelector();
extern void syncColorSelector();
#endif

class Application
{
public:
	Application();

	void setup();
	void loop();
};

#endif // APPLICATION_H
