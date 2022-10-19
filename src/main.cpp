#include <Keypad.h>
// #include <Encoder.h>
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
int S1 = 10;
int S2 = 16;
int S3 = 14;
int S4 = 15;
const int numStates = 4;
const int States[numStates] = {S1, S2, S3, S4};
int currentState = 0;

int lastDebounceTime = 0;
const int debounceTime = 50;

//Encoder
int SW = 4;
int timeLimit = 300;
Bounce encoderButton = Bounce(SW,10);

int DT = 5;
int CLK = 6;
int16_t inputDelta = 0;             // Counts up or down depending which way the encoder is turned
bool printFlag = false;             // Flag to indicate that the value of inputDelta should be printed
// Encoder volumeKnob(DT,CLK);
// long oldPosition = -999;


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

void StartAnimation();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for (int i = 0; i < numStates; i++){
    pinMode(States[i], OUTPUT);
    digitalWrite(States[i], LOW);
  }

  // pinMode(CLK, INPUT_PULLUP);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  
  Keyboard.begin();
  //Consumer.begin();
  
  Serial.print("Ready");
  
  StartAnimation();
  digitalWrite(States[currentState], HIGH);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  // display.display();
  // delay(500); // Pause
  
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("MacroPad"));
  display.println(F("v2.1L"));
  display.display();
  delay(1000); // Pause

}

void StartAnimation(){
  int waitTime = 100;
  digitalWrite(S1, HIGH);
  delay(waitTime);
  digitalWrite(S2, HIGH);
  delay(waitTime);
  digitalWrite(S3, HIGH);
  delay(waitTime);
  digitalWrite(S4, HIGH);
  delay(waitTime);
  digitalWrite(S1, LOW);
  delay(waitTime);
  digitalWrite(S2, LOW);
  delay(waitTime);
  digitalWrite(S3, LOW);
  delay(waitTime);
  digitalWrite(S4, LOW);
  delay(waitTime);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  digitalWrite(S4, HIGH);
  delay(waitTime);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  digitalWrite(S4, LOW);
  delay(waitTime);
  return;
}

// s==1, next state
// s==0, previous state
void ChangeState(bool s){
  digitalWrite(States[currentState], LOW);
  if (s==1){
    currentState++;
  }
  else {
    currentState--;
  }
  if (currentState == numStates){
    currentState = 0;
  }
  digitalWrite(States[currentState], HIGH);
  // Serial.print("State Changed. Current State: "); Serial.println(currentState);
  delay(100);
  return;
}

void Layout1(char button){
  switch(button){
    case '1':
      Keyboard.print('1');
      break;
    case '2':
      Keyboard.print('2');
      break;
    case '3':
      Keyboard.print('3');
      break;
    case '4':
      Keyboard.print('4');
      break;
    case '5':
      Keyboard.print('5');
      break;
    case '6':
      Keyboard.print('6');
      break;
    case '7':
      Keyboard.print('7');
      break;
    case '8':
      Keyboard.print('8');
      break;
  };
}

void Layout2(char button){
  switch(button){
    case '1':
      Keyboard.print('1');
      break;
    case '2':
      Keyboard.print('2');
      break;
    case '3':
      Keyboard.print('3');
      break;
    case '4':
      Keyboard.print('4');
      break;
    case '5':
      Keyboard.print('5');
      break;
    case '6':
      Keyboard.print('6');
      break;
    case '7':
      Keyboard.print('7');
      break;
    case '8':
      Keyboard.print('8');
      break;
  };
}

void Layout3(char button){
  switch(button){
    case '1':
      // Side Bar
      Keyboard.press(KEY_LEFT_CTRL); 
      Keyboard.press(KEY_B); 
      Keyboard.releaseAll();
      break;
    case '2':
      // Split View 
      Keyboard.press(KEY_LEFT_CTRL); 
      Keyboard.press(KEY_BACKSLASH); 
      Keyboard.releaseAll();
      break;
    case '3':
      // Trim Whitespace
      Keyboard.press(KEY_LEFT_CTRL); 
      Keyboard.press(KEY_K); 
      Keyboard.releaseAll();
      Keyboard.press(KEY_X);
      Keyboard.releaseAll();
      break;
    case '4':
      // Code Un-Folding
      Keyboard.press(KEY_LEFT_CTRL); 
      Keyboard.press(KEY_LEFT_SHIFT); 
      Keyboard.press(HID_KEYBOARD_RIGHT_BRACKET_AND_RIGHT_CURLY_BRACE);
      Keyboard.releaseAll();
      break;
    case '5':
      // File Explorer
      Keyboard.press(KEY_LEFT_CTRL); 
      Keyboard.press(KEY_LEFT_SHIFT); 
      Keyboard.press(KEY_E); 
      Keyboard.releaseAll();
      break;
    case '6':
      // Zen Mode
      Keyboard.press(KEY_LEFT_CTRL); 
      Keyboard.press(KEY_K); 
      Keyboard.releaseAll();
      Keyboard.press(KEY_Z); 
      Keyboard.releaseAll();
      break;
    case '7':
      // Code Formatting
      Keyboard.press(KEY_LEFT_CTRL); 
      Keyboard.press(KEY_K); 
      Keyboard.releaseAll();
      Keyboard.press(KEY_LEFT_CTRL); 
      Keyboard.press(KEY_F); 
      Keyboard.releaseAll();
      break;
    case '8':
      // Code Folding
      Keyboard.press(KEY_LEFT_CTRL); 
      Keyboard.press(KEY_LEFT_SHIFT); 
      Keyboard.press(HID_KEYBOARD_LEFT_BRACKET_AND_LEFT_CURLY_BRACE);
      Keyboard.releaseAll();
      break;
  };
}

void Layout4(char button){
  switch(button){
    case '1':
      // Normal-Constrction
      // Keyboard.print('x');
      Keyboard.press(KEY_X); 
      Keyboard.releaseAll(); 
      break;
    case '2':
      // Sketch Line
      // Keyboard.print('l');
      Keyboard.press(KEY_L); 
      Keyboard.releaseAll(); 
      break;
    case '3':
      // Sketch Point
      // Keyboard.print('k'); 
      Keyboard.press(KEY_K); 
      Keyboard.releaseAll();
      break;
    case '4':
      // Sketch Mirror
      // Keyboard.print('n'); 
      Keyboard.press(KEY_N); 
      Keyboard.releaseAll();
      break;
    case '5':
      Keyboard.press(KEY_ESC);
      Keyboard.releaseAll();
      break;
    case '6':
      // Delete
      Keyboard.press(KEY_DELETE); 
      Keyboard.releaseAll();
      break;
    case '7':
      // Extrude
      // Keyboard.print('e');
      Keyboard.press(KEY_E); 
      Keyboard.releaseAll();
      break;
    case '8':
      // Sketch Dimension
      // Keyboard.print('d'); 
      Keyboard.press(KEY_D); 
      Keyboard.releaseAll();
      break;
  };
}

void lcdMenu() {
  display.clearDisplay();

  // display.setFont(&FreeMono12pt7b);
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  switch (currentState){
    case 0:
      display.println(F("Desktop     Layer [1]"));
      display.println(F("---------------------"));
      display.println(F(" |  |  | "));
      display.println(F(" |  |  | "));
      break;

    case 1:
      display.println(F("Desktop     Layer [2]"));
      display.println(F("---------------------"));
      display.println(F(" |  |  | "));
      display.println(F(" |  |  | "));
      break;

    case 2:
      display.println(F("VSCode      Layer [3]"));
      display.println(F("---------------------"));
      display.println(F("Exp | Zen | Fmt | Fod"));
      display.println(F("Sid | Spl | Wsp | Fod"));
      break;

    case 3:
      display.println(F("Fusion360   Layer [4]"));
      display.println(F("---------------------"));
      display.println(F("Esc | Del | Ext | Dem"));
      display.println(F("Ctr | Lin | Pnt | Mir"));
      break;
  }

  display.display();      // Show initial text
}

//check the encoder button
void encoderButtonCheck(){
  if(encoderButton.update()) {
    if(encoderButton.fallingEdge()) {
      int fall = millis();
      while(!encoderButton.update()){}
      
      if(encoderButton.risingEdge()){
        int rise = millis();
        //Serial.println(rise - fall);
        if(rise - fall > timeLimit){
          ChangeState(0);
        //   Consumer.write(MEDIA_NEXT);
        //   Serial.print("Next");
        } else {
          ChangeState(1);
          // Consumer.write(MEDIA_PLAY_PAUSE);
          // Serial.print("Play/Pause");
        }
      }
      
      Keyboard.releaseAll();
    }
  }
}

//check encoder rotation
// void encoderKnobCheck(){
//   long newPosition = volumeKnob.read();
//   if(newPosition != oldPosition){
//     Serial.print(newPosition);
  
//     if((newPosition - oldPosition) > 0) {
//       //volumeup
//       Serial.println("volume up");
//       Consumer.write(MEDIA_VOLUME_UP);
//       newPosition = 0;
//     } else {
//       //volumedown
//       Serial.println("volume down");
//       Consumer.write(MEDIA_VOLUME_DOWN);
//       newPosition = 0;
//     }
//     oldPosition = newPosition;
//     Keyboard.releaseAll();
//     delay(200); //a delay of 200 seems to be the sweet spot for this encoder.
//   } 
// }

// void readEncoder() {
//     static uint8_t state = 0;
//     bool CLKstate = digitalRead(CLK);
//     bool DTstate = digitalRead(DT);
//     switch (state) {
//         case 0:                         // Idle state, encoder not turning
//             if (!CLKstate){             // Turn clockwise and CLK goes low first
//                 state = 1;
//             } else if (!DTstate) {      // Turn anticlockwise and DT goes low first
//                 state = 4;
//             }
//             break;
//         // Clockwise rotation
//         case 1:                     
//             if (!DTstate) {             // Continue clockwise and DT will go low after CLK
//                 state = 2;
//             } 
//             // Serial.println("CW1");
//             break;
//         case 2:
//             if (CLKstate) {             // Turn further and CLK will go high first
//                 state = 3;
//             }
//             // Serial.println("CW2");
//             break;
//         case 3:
//             if (CLKstate && DTstate) {  // Both CLK and DT now high as the encoder completes one step clockwise
//                 state = 0;
//                 ++inputDelta;
//                 printFlag = true;
//             }
//             // Serial.println("CW3");
//             Serial.println("VOL UP");
//             break;
//         // Anticlockwise rotation
//         case 4:                         // As for clockwise but with CLK and DT reversed
//             if (!CLKstate) {
//                 state = 5;
//             }
//             // Serial.println("CCW4");
//             break;
//         case 5:
//             if (DTstate) {
//                 state = 6;
//             }
//             // Serial.println("CCW5");
//             Serial.println("VOL DOWN");
//             break;
//         case 6:
//             if (CLKstate && DTstate) {
//                 state = 0;
//                 --inputDelta;
//                 printFlag = true;
//             }
//             // Serial.println("CCW6");
//             break; 
//     }
// }

void loop() {
  //check the key matrix first
  char key = kpd.getKey();
  if(key) {
    // switch(key){
    //   case '*':
    //     ChangeState();
    //     break;
    //   default:
        switch(currentState){
          case 0:
            Layout1(key);
            break;
          case 1:
            Layout2(key);
            break;
          case 2:
            Layout3(key);
            break;
          case 3: 
            Layout4(key);
            break;
        }
    }
  // }

  encoderButtonCheck();
  // encoderKnobCheck();
  // readEncoder();
  lcdMenu();
}


