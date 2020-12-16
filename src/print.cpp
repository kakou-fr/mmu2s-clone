#include "print.h"
#include "config.h"

char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
    return NULL;
}

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
#ifdef CDC_SERIAL
    ConsoleSerial.println(string2char(msg));
#else
    ConsoleSerial.println(msg);
#endif
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
#ifdef CDC_SERIAL
    ConsoleSerial.print(string2char(msg));
#else
    ConsoleSerial.print(msg);
#endif
#endif
}

void print_log(char msg)
{
#ifdef SERIAL_INTERACTIVE
    ConsoleSerial.println(msg);
#endif
}