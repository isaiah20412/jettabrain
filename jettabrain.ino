//# Define variables

//## Pins
//### Digital
int RELAY_00 = 2;
int RELAY_01 = 3;
int RELAY_02 = 4;
int RELAY_03 = 5;
int RELAY_04 = 6;
int RELAY_05 = 7;

//### Analog



//## Booleans


//# Strings
char *lightModes[] = {"Off", "Auto", "On"};  // Light system modes: Auto=car controls. On=soft manual.
String lightModeCurrent = lightModes[0];  // Currently selected light mode.
char *brightModes[] = {"Low", "High"};  // Low or high beams.
String brightModeCurrent = brightModes[0];  // Currently selected bright mode.


//# Libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup()
// Runs once on start.
{
	Serial.begin(9600);
  // Define pin modes.
  pinMode(RELAY_00, OUTPUT);
  pinMode(RELAY_01, OUTPUT);
  pinMode(RELAY_02, OUTPUT);
  pinMode(RELAY_03, OUTPUT);
  pinMode(RELAY_04, OUTPUT);
  pinMode(RELAY_05, OUTPUT);

  // Initialize Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.print("Power On");
  display.display();
  delay(1000);

  // Tell the user that we're ready
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setCursor(20, 0);
  display.print("Vehicle");
  display.setTextSize(1);
  display.setCursor(0, 15);
  display.print("Systems Initialized");
  display.display();
  delay(1500);
  display.clearDisplay();
  updateMenu();
  display.display();
}

void loop()
{
  // Continuously repeating code.

	//updateMenu();
}


//# Function Declarations
void updateMenu()
{
  // Light Status
  display.clearDisplay();
  display.setTextSize(1); // Draw 1X-scale text
  display.setCursor(0, 0);
  display.print(lightModeCurrent);
  display.setTextSize(1);
  
  // Brights Status
  display.setCursor(0, 30);
  display.print(brightModeCurrent);
  display.display();
}
