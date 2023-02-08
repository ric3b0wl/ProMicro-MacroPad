#include <Keypad.h>
#include <Bounce2.h>
#include "HID-Project.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// #include <Fonts/FreeMono12pt7b.h>

//Keypad buttons
int R1 = 9;
int R2 = 8;
int C1 = 21;
int C2 = 20;
int C3 = 19;
int C4 = 18;
const byte ROWS = 2;
const byte COLS = 4;
char keys[COLS][ROWS] = {
  {'4','8'},
  {'3','7'},
  {'2','6'},
  {'1','5'}
};
byte rowPins[ROWS] = {R1, R2};
byte colPins[COLS] = {C1, C2, C3, C4};
Keypad kpd = Keypad( makeKeymap(keys), colPins, rowPins, COLS, ROWS);

//State LED pins
int led0 = 10;
int led1 = 16;
int led2 = 14;
int led3 = 15;
const int numLed = 4;
const int led[numLed] = {led0, led1, led2, led3};
int currentLed = 0;

//toggle switch
int tgUp = 4;
int tgDw = 5;
int tgUpState;
int tgDwState;
int tgUpLastState = LOW;
int tgDwLastState = LOW;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void ledStartAnimation(){
  int waitTime = 100;
  
  digitalWrite(led0, HIGH);
  delay(waitTime);
  digitalWrite(led1, HIGH);
  delay(waitTime);
  digitalWrite(led2, HIGH);
  delay(waitTime);
  digitalWrite(led3, HIGH);
  delay(waitTime);
  digitalWrite(led0, LOW);
  delay(waitTime);
  digitalWrite(led1, LOW);
  delay(waitTime);
  digitalWrite(led2, LOW);
  delay(waitTime);
  digitalWrite(led3, LOW);
  delay(waitTime);

  digitalWrite(led0, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  delay(waitTime);
  digitalWrite(led0, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  delay(waitTime);
  return;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // LED
  for (int i = 0; i < numLed; i++){
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }

  pinMode(tgUp, INPUT_PULLUP);
  pinMode(tgDw, INPUT_PULLUP);
  
  Keyboard.begin();
  //Consumer.begin();
  
  Serial.print("Ready");
  
  ledStartAnimation();
  digitalWrite(led[currentLed], LOW);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("DeMacroPad"));
  display.println(F("v2.15-RACE"));
  display.display();
  delay(1000); // Pause

}

void keyLayout(char button){
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  switch(button){
    case '1':
      Keyboard.print('1');
      display.println(F("1"));
      break;

    case '2':
      Keyboard.print('2');
      display.println(F("2"));
      break;

    case '3':
      Keyboard.print('3');
      display.println(F("3"));
      break;

    case '4':
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_SPACE);      
      display.println(F("RESET"));
      display.println(F("VIEW"));
      break;

    case '5':
      Keyboard.print('4');
      display.println(F("4"));
      break;

    case '6':
      Keyboard.print('6');
      display.println(F("6"));
      break;

    case '7':
      Keyboard.print('7');
      display.println(F("7"));
      break;

    case '8':
      Keyboard.press(KEY_S);
      display.println(F("ENGINE"));
      display.println(F("STARTER"));
      break;
  };

  display.display();
  Keyboard.releaseAll();
}

void toggleCheck(){
  
  int readingUp = digitalRead(tgUp);
  int readingDw = digitalRead(tgDw);

  if (readingUp != tgUpLastState || readingDw != tgDwLastState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingUp != tgUpState) {
      tgUpState = readingUp;

      // only toggle the LED if the new button state is HIGH
      if (tgUpState == LOW) {
        digitalWrite(led[0], HIGH);
        digitalWrite(led[1], LOW);
        digitalWrite(led[2], LOW);
        digitalWrite(led[3], HIGH);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_I);
      }
      else{
        digitalWrite(led[0], LOW);
        digitalWrite(led[1], LOW);
        digitalWrite(led[2], LOW);
        digitalWrite(led[3], LOW);
      }
    }
    else if (readingDw != tgDwState) {
      tgUpState = readingUp;

      // only toggle the LED if the new button state is HIGH
      if (tgUpState == LOW) {
        digitalWrite(led[0], LOW);
        digitalWrite(led[1], HIGH);
        digitalWrite(led[2], HIGH);
        digitalWrite(led[3], LOW);
        Keyboard.press(KEY_S);
      }
      else{
        digitalWrite(led[0], LOW);
        digitalWrite(led[1], LOW);
        digitalWrite(led[2], LOW);
        digitalWrite(led[3], LOW);
      }
    }
  }

  tgUpLastState = readingUp;
  tgDwLastState = readingDw;
  Keyboard.releaseAll();
}

void loop() {
  //check the key matrix first
  toggleCheck();

  char key = kpd.getKey();
  if(key) {
    keyLayout(key);
  }
}
