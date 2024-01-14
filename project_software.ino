#include "pitches.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int BUZZER_PIN = 10;
const int LED_PIN_RED = 13;
const int LED_PIN_GREEN =12;
const int LED_PIN_ORANGE = 11;
const int BUTTON_PIN = 2;
const int DEBOUNCE_TIME = 50;
const int BLINK_INTERVAL = 100;
const int MAX_BLINK_COUNT = 3;
bool option = 1;
int remain_attempt = 3;


int buttonPressCount = 1;
float count = 0; // for blink led



bool isButtonPressed() {
  static unsigned long timeOfLastChange = 0;
  static int buttonState = HIGH;
  const unsigned long currentTime = millis();
  const int newState = digitalRead(BUTTON_PIN);

  if (buttonState != newState && (currentTime - timeOfLastChange > DEBOUNCE_TIME)) {
    timeOfLastChange = currentTime;
    buttonState = newState;
    return (buttonState == LOW);
  }

  return false;
}

void sound(int option) {
  int melodies[2][3] = {
    { NOTE_E6, NOTE_C6, NOTE_G6 },
    { NOTE_C3, NOTE_D2, NOTE_C2 }
  };
  int noteDurations[2][3] = {
    { 16, 16, 4 },
    { 8, 4, 2 }
  };
  for (int thisNote = 0; thisNote < 3; thisNote++) {
    int noteDuration = 1000 / noteDurations[option][thisNote];
    tone(BUZZER_PIN, melodies[option][thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
}


void sound_buzzer(int option) {
  // danh sách các nốt nhạc
  
  if (option == 0) {
    sound(option);
    digitalWrite(LED_PIN_ORANGE,HIGH);

    //Ngừng phát nhạc để sau đó chơi nhạc tiếp!
  } else if (option == 1) {
    sound(option);
  }
}


void blinkLed(int interval,int LED_PIN) {
  static bool ledIsOn = false;
  static unsigned long timeOfLastChange = 0;
  const unsigned long currentTime = millis();

  if (count < MAX_BLINK_COUNT) {
    if (currentTime - timeOfLastChange > interval) {
      timeOfLastChange = currentTime;
      ledIsOn = !ledIsOn;
      digitalWrite(LED_PIN, ledIsOn);
      if (ledIsOn) {
        sound(option);
      } else {
        noTone(BUZZER_PIN);
      }
      count += 0.5;
    }
  } else {
    digitalWrite(LED_PIN, LOW);
    
  }
  if (isButtonPressed()) {
      count -= MAX_BLINK_COUNT;
    }
}



void lobby(bool theme) {
  delay(2000);         // wait for initializing
    oled.clearDisplay();
    
  oled.invertDisplay(theme);

  oled.setTextSize(1.5);      // text size
  oled.setTextColor(WHITE);    // text color
  oled.setCursor(0, 10);       // position to display
  oled.println("Hello World!");
  oled.setCursor(0, 18);
  oled.println("Please enter a");
  oled.setCursor(0, 26);
  oled.println("password: ");
  oled.display();
}

void change_display(bool theme) {
  
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.invertDisplay(!theme);
  
}
void correct_or_wrong(int option) {
  if(option == 0){
    oled.setTextSize(2);
    oled.setCursor(24, 15);
    oled.println("Success");
    oled.display();
    }else {
      oled.setTextSize(2);
      oled.setCursor(24, 15);
      oled.println("Failed");
      remain_attempt = remain_attempt - 1;
      
      char left_attempt[100];
      sprintf(left_attempt,"Attempt: %d",remain_attempt);
      oled.setTextSize(1);
      oled.setCursor(2, 33);
      oled.println(left_attempt);
      oled.display();
       if(remain_attempt < 1){
      oled.clearDisplay();
      oled.setTextSize(1);
      oled.setCursor(15, 0);
      oled.println("Your safe will be locked in 10s");
      oled.display();
      }
   }
}

void setup() {
  //không cần phải pinMode cho speakerPin

  sound_buzzer;
  Serial.begin(9600);
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_ORANGE, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);

  // initialize OLED display with address 0x3C for 128x64
  oled.begin(SSD1306_SWITCHCAPVCC, 0X3C);
}



void loop() {
  static bool theme = false;
  lobby(theme);

  if (isButtonPressed()) {
    buttonPressCount += 2;
     change_display(theme);  
     correct_or_wrong(option);
  }

  if (buttonPressCount % 2 == 1) {
    if (buttonPressCount == 1) {
      // Do nothing for the first button press
    } else {
      blinkLed(BLINK_INTERVAL,LED_PIN_RED);
    }
  }
}

