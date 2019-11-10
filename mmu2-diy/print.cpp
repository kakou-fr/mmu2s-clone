#include "print.h"

/*************************/
int ENABLE_SSD1306 = 0;
#ifdef SSD1306
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif

IOPrint::IOPrint()
{
    // nothing to do in the constructor
}

void IOPrint::setup()
{
#ifdef SERIAL_DEBUG
    Serial.begin(250000); // startup the local serial interface (changed to 2 Mbaud on 10.7.18
     while (!Serial)
    {
        delay(200); // wait for serial port to connect. needed for native USB port only
        Serial.println(F("waiting for serial port"));
    }
    
#endif
#ifdef SSD1306
    ENABLE_SSD1306 = 1;
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        ENABLE_SSD1306 = 0;
    }
    if (ENABLE_SSD1306)
    {
        display.display();
        delay(200); // Pause for 2 seconds

        // Clear the buffer
        display.clearDisplay();
    }
#endif
}

void manage_screen()
{
    #ifdef SSD1306
    display.clearDisplay();
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.cp437(true);         // Use full 256 char 'Code Page 437' font
    #endif
}
void println_log(const __FlashStringHelper *msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
#ifdef SSD1306
    manage_screen();
    display.println(msg);
#endif
}

void println_log(const char *msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
#ifdef SSD1306
    manage_screen();
    display.println(msg);
#endif
}

void println_log(String msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
#ifdef SSD1306
    manage_screen();
    display.println(msg);
#endif
}

void println_log(int msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
#ifdef SSD1306
    manage_screen();
    display.println(msg);
#endif
}

void println_log(unsigned int msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
#ifdef SSD1306
    manage_screen();
    display.println(msg);
#endif
}

void println_log(char msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
#ifdef SSD1306
    manage_screen();
    display.println(msg);
#endif
}

void print_log(const __FlashStringHelper *msg)
{
#ifdef SERIAL_DEBUG
    Serial.print(msg);
#endif
#ifdef SSD1306
    manage_screen();
    display.println(msg);
#endif
}

void print_log(const char *msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
#ifdef SSD1306
    manage_screen();
    display.println(msg);
#endif
}

void print_log(String msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
#ifdef SSD1306
    manage_screen();
    display.println(msg);
#endif
}

void print_log(char msg)
{
#ifdef SERIAL_DEBUG
    Serial.println(msg);
#endif
#ifdef SSD1306
    manage_screen();
    display.println(msg);
#endif
}