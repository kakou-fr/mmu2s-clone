#include "print.h"

char BUFFER[512];

IOPrint::IOPrint()
{
    // nothing to do in the constructor
}

void IOPrint::setup()
{
#ifdef SERIAL_DEBUG
    Serial.begin(250000); // startup the local serial interface (changed to 2 Mbaud on 10.7.18
    //while (!Serial)
    //{
        delay(200); // wait for serial port to connect. needed for native USB port only
        Serial.println("waiting for serial port");
    //}
    
#endif
}

void println_log(const char *msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
}


void println_log(int msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
}

void println_log(unsigned int msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
}

void println_log(char msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
}

void print_log(const char *msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
}

void print_log(char msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
}