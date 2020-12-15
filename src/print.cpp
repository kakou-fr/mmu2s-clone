#include "print.h"
#include "config.h"

char BUFFER[512];

IOPrint::IOPrint()
{
    // nothing to do in the constructor
}

void IOPrint::setup()
{
#ifdef SERIAL_INTERACTIVE
#if defined(CDC_SERIAL)
	USB_Init();			// USB Initialization
	USB_Connect(FALSE); // USB clear connection
	delay(1000);		// Give OS time to notice
	USB_Connect(TRUE);
#endif
    ConsoleSerial.begin(250000); 
    delay(200); 
    ConsoleSerial.println("waiting for serial port");
    
#endif
}

void println_log(String msg)
{
#ifdef SERIAL_INTERACTIVE
    ConsoleSerial.println(msg);
#endif
}


void println_log(int msg)
{
#ifdef SERIAL_INTERACTIVE
    ConsoleSerial.println(msg);
#endif
}

void println_log(unsigned int msg)
{
#ifdef SERIAL_INTERACTIVE
    ConsoleSerial.println(msg);
#endif
}

void println_log(char msg)
{
#ifdef SERIAL_INTERACTIVE
    ConsoleSerial.println(msg);
#endif
}

void print_log(String msg)
{
#ifdef SERIAL_INTERACTIVE
    ConsoleSerial.print(msg);
#endif
}

void print_log(char msg)
{
#ifdef SERIAL_INTERACTIVE
    ConsoleSerial.println(msg);
#endif
}