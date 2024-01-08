#include <Arduino.h>

// -- COMPONENTS --
//  SHIFT REGISTER
const int SR_DATA_PIN = 13;     // SER
const int SR_LATCH_PIN = 12;    // RCLK
const int SR_CLOCK_PIN = 11;    // SRCLK

// BCD
const int BCD_A_PIN = A0;
const int BCD_B_PIN = A1;
const int BCD_C_PIN = A2;
const int BCD_D_PIN = A3;

// ROTARY ENCODER
const int RE_BUTTON_PIN = 6;    // SW
const int RE_CLK_PIN = 5;       // BCD_A_PIN
const int RE_DATA_PIN = 4;      // BCD_B_PIN
#define DIRECTION_CW 0          // clockwise direction
#define DIRECTION_CCW 1         // counter-clockwise direction

// -- VARIABLES
const int DEBOUNCE_TIME = 50;


void zero() {  //0000
    digitalWrite(BCD_A_PIN, LOW);
    digitalWrite(BCD_B_PIN, LOW);
    digitalWrite(BCD_C_PIN, LOW);
    digitalWrite(BCD_D_PIN, LOW);
}

void one() {  //0001
    digitalWrite(BCD_A_PIN, HIGH);
    digitalWrite(BCD_B_PIN, LOW);
    digitalWrite(BCD_C_PIN, LOW);
    digitalWrite(BCD_D_PIN, LOW);
}

void two() {  // 0010
    digitalWrite(BCD_A_PIN, LOW);
    digitalWrite(BCD_B_PIN, HIGH);
    digitalWrite(BCD_C_PIN, LOW);
    digitalWrite(BCD_D_PIN, LOW);
}

void three() {  // 0011
    digitalWrite(BCD_A_PIN, HIGH);
    digitalWrite(BCD_B_PIN, HIGH);
    digitalWrite(BCD_C_PIN, LOW);
    digitalWrite(BCD_D_PIN, LOW);
}

void four() {  // 0100
    digitalWrite(BCD_A_PIN, LOW);
    digitalWrite(BCD_B_PIN, LOW);
    digitalWrite(BCD_C_PIN, HIGH);
    digitalWrite(BCD_D_PIN, LOW);
}

void five() {  // 0101
    digitalWrite(BCD_A_PIN, HIGH);
    digitalWrite(BCD_B_PIN, LOW);
    digitalWrite(BCD_C_PIN, HIGH);
    digitalWrite(BCD_D_PIN, LOW);
}

void six() {  // 0110
    digitalWrite(BCD_A_PIN, LOW);
    digitalWrite(BCD_B_PIN, HIGH);
    digitalWrite(BCD_C_PIN, HIGH);
    digitalWrite(BCD_D_PIN, LOW);
}

void seven() {  // 0111
    digitalWrite(BCD_A_PIN, HIGH);
    digitalWrite(BCD_B_PIN, HIGH);
    digitalWrite(BCD_C_PIN, HIGH);
    digitalWrite(BCD_D_PIN, LOW);
}

void eight() {  // 1000
    digitalWrite(BCD_A_PIN, LOW);
    digitalWrite(BCD_B_PIN, LOW);
    digitalWrite(BCD_C_PIN, LOW);
    digitalWrite(BCD_D_PIN, HIGH);
}

void nine() {  // 1001
    digitalWrite(BCD_A_PIN, HIGH);
    digitalWrite(BCD_B_PIN, LOW);
    digitalWrite(BCD_C_PIN, LOW);
    digitalWrite(BCD_D_PIN, HIGH);
}


void displayNumber(int number, int display) {
    static int shift_register_1 = 0;
//    static int shift_register_2 = 0;
    byte patterns[10] = {
            B01000000,  // 0
            B01111001,  // 1
            B00100100,  // 2
            B00110000,  // 3
            B00011001,  // 4
            B00010010,  // 5
            B00000011,  // 6
            B11111000,  // 7
            B00000000,  // 8
            B00011000   // 9
    };
    // TODO: Function to control BCD
    if (display == 0) { // Choosing value for the first shift register
        // Shift out the pattern to the first 74HC595
        digitalWrite(SR_LATCH_PIN, LOW);
        shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, patterns[0]); // Clear the second shift register
        shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, patterns[number]); // Shift pattern for the first display
        digitalWrite(SR_LATCH_PIN, HIGH);
        shift_register_1 = number;
    } else if (display == 1) { // Choosing value for the second shift register
        // Shift out the pattern to the second 74HC595
        digitalWrite(SR_LATCH_PIN, LOW);
        shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, patterns[number]);
        shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, patterns[shift_register_1]); // Save first number
        digitalWrite(SR_LATCH_PIN, HIGH);
//        shift_register_2 = number;
    } else if (display == 2) {
        if (number == 0) {
            digitalWrite(BCD_A_PIN, LOW);
            digitalWrite(BCD_B_PIN, LOW);
            digitalWrite(BCD_C_PIN, LOW);
            digitalWrite(BCD_D_PIN, LOW);
        } else if (number == 1) {
            digitalWrite(BCD_A_PIN, HIGH);
            digitalWrite(BCD_B_PIN, LOW);
            digitalWrite(BCD_C_PIN, LOW);
            digitalWrite(BCD_D_PIN, LOW);
        } else if (number == 2) {
            digitalWrite(BCD_A_PIN, LOW);
            digitalWrite(BCD_B_PIN, HIGH);
            digitalWrite(BCD_C_PIN, LOW);
            digitalWrite(BCD_D_PIN, LOW);
        } else if (number == 3) {
            digitalWrite(BCD_A_PIN, HIGH);
            digitalWrite(BCD_B_PIN, HIGH);
            digitalWrite(BCD_C_PIN, LOW);
            digitalWrite(BCD_D_PIN, LOW);
        } else if (number == 4) {
            digitalWrite(BCD_A_PIN, LOW);
            digitalWrite(BCD_B_PIN, LOW);
            digitalWrite(BCD_C_PIN, HIGH);
            digitalWrite(BCD_D_PIN, LOW);
        } else if (number == 5) {
            digitalWrite(BCD_A_PIN, HIGH);
            digitalWrite(BCD_B_PIN, LOW);
            digitalWrite(BCD_C_PIN, HIGH);
            digitalWrite(BCD_D_PIN, LOW);
        } else if (number == 6) {
            digitalWrite(BCD_A_PIN, LOW);
            digitalWrite(BCD_B_PIN, HIGH);
            digitalWrite(BCD_C_PIN, HIGH);
            digitalWrite(BCD_D_PIN, LOW);
        } else if (number == 7) {
            digitalWrite(BCD_A_PIN, HIGH);
            digitalWrite(BCD_B_PIN, HIGH);
            digitalWrite(BCD_C_PIN, HIGH);
            digitalWrite(BCD_D_PIN, LOW);
        } else if (number == 8) {
            digitalWrite(BCD_A_PIN, LOW);
            digitalWrite(BCD_B_PIN, LOW);
            digitalWrite(BCD_C_PIN, LOW);
            digitalWrite(BCD_D_PIN, HIGH);
        } else if (number == 9) {
            digitalWrite(BCD_A_PIN, HIGH);
            digitalWrite(BCD_B_PIN, LOW);
            digitalWrite(BCD_C_PIN, LOW);
            digitalWrite(BCD_D_PIN, HIGH);
        }
    }
}


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

    displayNumber(0, 0);
    displayNumber(0, 1);
    displayNumber(0, 2);
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
    const int seven_segments[3] = {0, 1, 2};
    static int index_seven_segments = 0;
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


    if (RE_BUTTON_state != prev_RE_BUTTON_state && (current_time - time_of_last_change > DEBOUNCE_TIME)) {
        // a valid change was detected
        time_of_last_change = current_time;         // save time of this change
        RE_BUTTON_state = prev_RE_BUTTON_state;                   // update the button's known state
        if (RE_BUTTON_state == LOW) {
            // Switch two the second seven segment
            Serial.println("The button is pressed");
            index_seven_segments++;
        }
    }
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
        displayNumber(counter, seven_segments[index_seven_segments]);
    }
    // save last CLK state
    prev_RE_CLK_state = RE_CLK_state;

}


