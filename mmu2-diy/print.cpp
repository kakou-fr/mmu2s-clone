#include "print.h"

extern HardwareSerial ConsoleSerial;

IOPrint::IOPrint()
{
    // nothing to do in the constructor
}

void IOPrint::setup()
{
#ifdef SERIAL_DEBUG
    ConsoleSerial.begin(250000); // startup the local serial interface (changed to 2 Mbaud on 10.7.18
    //while (!Serial)
    //{
        delay(200); // wait for serial port to connect. needed for native USB port only
        ConsoleSerial.println(F("waiting for serial port"));
    //}
    
#endif
}

void println_log(const __FlashStringHelper *msg)
{
#ifdef SERIAL_DEBUG
    ConsoleSerial.println(msg);
#endif
}

void println_log(const char *msg)
{
#ifdef SERIAL_DEBUG
    ConsoleSerial.println(msg);
#endif
}

void println_log(String msg)
{
#ifdef SERIAL_DEBUG
    ConsoleSerial.println(msg);
#endif
}

void println_log(int msg)
{
#ifdef SERIAL_DEBUG
    ConsoleSerial.println(msg);
#endif
}

void println_log(unsigned int msg)
{
#ifdef SERIAL_DEBUG
    ConsoleSerial.println(msg);
#endif
}

void println_log(char msg)
{
#ifdef SERIAL_DEBUG
    ConsoleSerial.println(msg);
#endif
}

void print_log(const __FlashStringHelper *msg)
{
#ifdef SERIAL_DEBUG
    ConsoleSerial.print(msg);
#endif
}

void print_log(const char *msg)
{
#ifdef SERIAL_DEBUG
    ConsoleSerial.println(msg);
#endif
}

void print_log(String msg)
{
#ifdef SERIAL_DEBUG
    ConsoleSerial.println(msg);
#endif
}

void print_log(char msg)
{
#ifdef SERIAL_DEBUG
    ConsoleSerial.println(msg);
#endif
}