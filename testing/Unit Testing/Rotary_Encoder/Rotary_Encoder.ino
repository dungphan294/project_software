#include <Arduino.h>
// ROTARY ENCODER
#define RE_BUTTON_PIN 10  // SW
#define RE_CLK_PIN 9      // A
#define RE_DATA_PIN 8     // B
// VARIABLES
#define DEBOUNCE_TIME 100
#define DIRECTION_CW 0   // clockwise direction
#define DIRECTION_CCW 1  // counter-clockwise direction

void setup() {
  // put your setup code here, to run once:
  // ROTARY ENCODER
  pinMode(RE_BUTTON_PIN, INPUT_PULLUP);  //10
  pinMode(RE_CLK_PIN, INPUT);            // 9
  pinMode(RE_DATA_PIN, INPUT);           // 8
}

void loop() {
  static int counter = 0;
  // TIME CHECK
  static unsigned long time_of_last_change = 0;
  const unsigned long current_time = millis();
  // ROTARY ENCODER BUTTON
  static int RE_BUTTON_state = HIGH;
  const int prev_RE_BUTTON_state = digitalRead(RE_BUTTON_PIN);
  // ROTARY ENCODER CLOCK
  static int prev_RE_CLK_state = HIGH;
  const int RE_CLK_state = digitalRead(RE_CLK_PIN);
  static bool direction = DIRECTION_CW;
  
  if (RE_BUTTON_PIN != prev_RE_BUTTON_state && (current_time - time_of_last_change > DEBOUNCE_TIME)) {
    time_of_last_change = current_time;
    RE_BUTTON_state = prev_RE_BUTTON_state;
    if (RE_BUTTON_state == LOW) {
      Serial.println("The button is pressed");
    }
  }
  // If the state of CLK is changed, then pulse occurred
  // React to only the rising edge (from LOW to HIGH) to avoid double count
  if (RE_CLK_state != prev_RE_CLK_state && RE_CLK_state == HIGH && (current_time - time_of_last_change > DEBOUNCE_TIME)) {
    // if the DT state is HIGH
    // the encoder is rotating in counter-clockwise direction => decrease the counter
    if (digitalRead(RE_DATA_PIN) == HIGH) {
      counter--;
      if (counter == -1) {
        counter = 9;
      }
      direction = DIRECTION_CCW;
    } else {
      // the encoder is rotating in clockwise direction => increase the counter
      counter++;
      if (counter == 10) {
        counter = 0;
      }
      direction = DIRECTION_CW;
    }
    Serial.print("DIRECTION: ");
    if (direction == DIRECTION_CW)
      Serial.print("Clockwise");
    else
      Serial.print("Counter-clockwise");
    Serial.print(" | COUNTER: ");
    Serial.println(counter);
  }
  // save last CLK state
  prev_RE_CLK_state = RE_CLK_state;
}
