#include <Arduino.h>

// -- COMPONENTS --
//  SHIFT REGISTER
#define SR_DATA_PIN 13     // SER
#define SR_LATCH_PIN 12    // RCLK
#define SR_CLOCK_PIN 11    // SRCLK
// BCD
#define BCD_A_PIN  A0
#define BCD_B_PIN  A1
#define BCD_C_PIN  A2
#define BCD_D_PIN  A3
// ROTARY ENCODER
#define RE_BUTTON_PIN 6    // SW
#define RE_CLK_PIN 5       // A
#define RE_DATA_PIN 4      // B
#define DIRECTION_CW 0          // clockwise direction
#define DIRECTION_CCW 1         // counter-clockwise direction
// BUTTON
#define BUTTON_SUBMIT_PIN = 1


// -- VARIABLES
const int DEBOUNCE_TIME = 50;

void setup() {
    Serial.begin(9600);
    // SHIFT REGISTER
    pinMode(SR_DATA_PIN, OUTPUT);
    pinMode(SR_LATCH_PIN, OUTPUT);
    pinMode(SR_CLOCK_PIN, OUTPUT);
    // BCD
    pinMode(BCD_A_PIN, OUTPUT);
    pinMode(BCD_B_PIN, OUTPUT);
    pinMode(BCD_C_PIN, OUTPUT);
    pinMode(BCD_D_PIN, OUTPUT);
    // ROTARY ENCODER
    pinMode(RE_BUTTON_PIN, INPUT_PULLUP);
    pinMode(RE_CLK_PIN, INPUT);
    pinMode(RE_DATA_PIN, INPUT);

}

void loop() {
    /*
     * TODO: Taking value from RE and displaying it on 7 segments
     * TODO: Create an array with 3 elements (as 3 seven-segments)
     * TODO: Using FOR loop to looping over the array.
     * TODO: Inside FOR loop. Check state of RE_CLK:
     * TODO:    IF LOW then -> switch to the second element on the array, and so on.
     * TODO: IF (
     */
    //const int seven_segments[3] = {0, 1, 2};
    //static int index_seven_segments = 0;
    static int counter = 0;
    static bool direction = DIRECTION_CW;

    static unsigned long time_of_last_change = 0;
    const unsigned long current_time = millis();
    // ROTARY ENCODER BUTTON
    static int RE_BUTTON_state = HIGH;
    const int prev_RE_BUTTON_state = digitalRead(RE_BUTTON_PIN);
    // ROTARY ENCODER CLOCK
    static int prev_RE_CLK_state = HIGH;
    const int RE_CLK_state = digitalRead(RE_CLK_PIN);
    // ROTARY ENCODER DATA

//    // TODO: Check RE_BUTTON click or not
    if (RE_BUTTON_state != prev_RE_BUTTON_state && (current_time - time_of_last_change > DEBOUNCE_TIME)) {
        // a valid change was detected
        time_of_last_change = current_time;         // save time of this change
        RE_BUTTON_state = prev_RE_BUTTON_state;                   // update the button's known state
        if (RE_BUTTON_state == LOW) {
            // Switch two the second seven segment
            Serial.println("The button is pressed");
        }
        // TODO: RE value displays on first seven segment
    }

    // read the current state of the rotary encoder's CLK pin

    // If the state of CLK is changed, then pulse occurred
    // React to only the rising edge (from LOW to HIGH) to avoid double count
    if (RE_CLK_state != prev_RE_CLK_state && RE_CLK_state == HIGH &&
        (current_time - time_of_last_change > DEBOUNCE_TIME)) {
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
