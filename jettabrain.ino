//# Define variables

//## Pins
//### Digital
int RELAY_00 = 2; // Light Bar Relay
int RELAY_01 = 3; // Light Pods Relay
int RELAY_03 = 5; // Unused; not wired
int RELAY_02 = 4; // Unused; not wired
int RELAY_04 = 6; // Unused; not wired
int RELAY_05 = 7; // Unused; not wired
int HIGH_BEAM_CAR = 8;
int HIGH_BEAM_DRIVER = 9;
int MODE = 10;
int ONOFF = 11; // Auxiliary fuse block relay
int DIMMER = 12; // Dimmer switch
int CAR_LIGHTS = 13; // Car light switch 


//### Analog



//## Booleans
bool dim = false; // Display dimming called to run.
bool brightsOn = false;


//# Strings
char *lightModes[] = {"Off", "Auto", "On"};  // Light system modes: Auto=car controls. On=soft manual.
int lightModeCurrent = 0;  // Currently selected light mode.
char *brightModes[] = {"Low", "High", "All"};  // Low or high beams.
int brightModeCurrent = 0;  // Currently selected bright mode.
int brightSelector = 9;


//# Libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup()
// Runs once on start.
{
	Serial.begin(9600);
  // Define pin modes.
  // Note: the relay module used is weird; LOW signal on a pin energizes the respective coil.
  pinMode(RELAY_00, OUTPUT);
  pinMode(RELAY_01, OUTPUT);
  pinMode(RELAY_02, OUTPUT);
  pinMode(RELAY_03, OUTPUT);
  pinMode(RELAY_04, OUTPUT);
  pinMode(RELAY_05, OUTPUT);
  pinMode(ONOFF, OUTPUT);

  // Initialize Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.print("Powering On");
  display.display();

  // Activate auxiliary fuse block
  digitalWrite(ONOFF, LOW);
  delay(1000);  // Pause, just for the fun of it.

  // Tell the user that we're ready
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setCursor(20, 0);
  display.print("Vehicle");
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print("Systems Initialized");
  display.display();
  delay(1500);
  display.clearDisplay();
  updateMenu();
  display.display();
}

void loop()
// Continuously repeating code.
{
  // Check Display Dimming Status
  if (digitalRead(DIMMER) == HIGH)
  {
    dim = true;
    dimDisplay();
  }
  else if (digitalRead(DIMMER) == HIGH)
  {
    dim = false;
    dimDisplay();
  }
  
  // Check and Update Light Mode
  if (lightModeCurrent == 2 && digitalRead(MODE) == HIGH) {
    delay(50);
    lightModeCurrent = 0;
    lightsOnOff();
  }
  else if (digitalRead(MODE) == HIGH) {
    delay(50);
    lightModeCurrent++;
    lightsOnOff();
  }

  /* Set Bright Mode Controller
  if (lightModeCurrent == 1) {  // If on auto, read bright status from steering wheel stalk switch
    brightSelector = HIGH_BEAM_CAR;
  }
  else if (lightModeCurrent == 2) { // If on manual, read bright status from button
    brightSelector = HIGH_BEAM_DRIVER;
  }
  */
  
  // Check and Update Bright Mode
  if (lightModeCurrent == 1 && digitalRead(brightSelector) == HIGH) {
    delay(50);
    brightsOn = !brightsOn;
    changeBrights();
  }
  else if (lightModeCurrent == 2 && digitalRead(brightSelector) == HIGH) {
    delay(50);
    brightModeCurrent++;
    if bright
    changeBrights();
  }
  /*
  if (brightModeCurrent != 0 && digitalRead(brightSelector) == HIGH) {
    delay(50);
    brightModeCurrent = 0;
    changeBrights();
  }
  */


  // Update Menu
	updateMenu();
}


//# Function Declarations
void updateMenu() {
  // Light Status
  display.clearDisplay();
  display.setTextSize(1); // Draw 1X-scale text
  display.setCursor(0, 0);
  display.print("Mode: ");
  display.print(lightModes[lightModeCurrent]);
  display.setTextSize(1);
  
  // Brights Status
  if (lightModeCurrent == 0 || lightModeCurrent == 1 && digitalRead(CAR_LIGHTS) == LOW) { //If the lights aren't on, don't show brights status.
    display.display();
  }
  else if (lightModeCurrent == 2) {
    display.setCursor(0, 23);
    display.print(brightModes[brightModeCurrent]);
    display.print(" Beams");
    display.display();
  }
  else {
    display.setCursor(0, 23);
    display.print(brightModes[brightModeCurrent]);
    display.print(" Beams");
    display.display();
  }
}

void dimDisplay() {
  if (dim) {
    display.ssd1306_command(SSD1306_SETCONTRAST);
    display.ssd1306_command(0x19);
  }
  else {
    display.ssd1306_command(SSD1306_SETCONTRAST);
    display.ssd1306_command(0x8F);
  }
}

void lightsOnOff () {
  if (lightModeCurrent == 1 && digitalRead(CAR_LIGHTS) == HIGH) {
    digitalWrite(RELAY_00, LOW);
  }
  else if (lightModeCurrent == 2 && !brightsOn) {
    digitalWrite(RELAY_00, LOW);
  }
  else {
    digitalWrite(RELAY_01, HIGH);
    digitalWrite(RELAY_00, HIGH);
    //changeBrights();
  }
  
  
}

void changeBrights() {
  if (brightsOn) {
    digitalWrite(RELAY_01, LOW);
    brightModeCurrent = 1;
  }
  else {
    digitalWrite(RELAY_01, HIGH);
    brightModeCurrent = 0;
  }
}