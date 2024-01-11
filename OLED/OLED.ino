#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define DEBOUNCE_TIME 50 // Adjust this value based on your needs

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int remain_attempt = 3;
int button = 2;
bool option = false;

  bool isButtonPressed(int button) {
  static unsigned long timeOfLastChange = 0;
  static int buttonState = HIGH;
  const unsigned long currentTime = millis();
  const int newState = digitalRead(button);

  if (buttonState != newState && (currentTime - timeOfLastChange > DEBOUNCE_TIME)) {
    timeOfLastChange = currentTime;
    buttonState = newState;
    return (buttonState == LOW);
  }

  return false;
}
void setup() {
  Serial.begin(9600);

  // initialize OLED display with address 0x3C for 128x64
  oled.begin(SSD1306_SWITCHCAPVCC, 0X3C);
  pinMode(button, INPUT_PULLUP);
  
}

void loop() {
  delay(2000);         // wait for initializing
    oled.clearDisplay();
    static bool theme = false; // clear display
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

  if (isButtonPressed(button)) {
    
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.invertDisplay(!theme);

    if(option == true){
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
}