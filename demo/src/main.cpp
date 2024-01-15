//
// Created by Dung Phan on 1/11/2024.
//
#include <Arduino.h>
#include <Servo.h>

// -- COMPONENTS --
//  SHIFT REGISTER
const int SR_DATA_PIN = 13;   // SER
const int SR_LATCH_PIN = 12;  // RCLK
const int SR_CLOCK_PIN = 11;  // SRCLK
// BCD
const int BCD_A_PIN = A0;  // BCD Input 1
const int BCD_B_PIN = A1;  // BCD Input 2
const int BCD_C_PIN = A2;  // BCD Input 3
const int BCD_D_PIN = A3;  // BCD Input 4
// ROTARY ENCODER
const int RE_BUTTON_PIN = 10;  // SW
const int RE_CLK_PIN = 9;     // A
const int RE_DATA_PIN = 8;    // B
const int DIRECTION_CW = 0;   // clockwise direction
const int DIRECTION_CCW = 1;  // counter-clockwise direction
// BUTTON
const int BUTTON_SUBMIT_PIN = 7;  // BUTTON Check pass
//const int BUTTON_OPEN_PIN = 6;    // BUTTON OPEN DOOR
// SERVO
Servo MYSERVO;
const int SERVO_PIN = 5;

// -- VARIABLES
const int DEBOUNCE_TIME = 50;

//typedef struct {
//    char password_encryted[3];
//    byte attempts;
//    int penalty; //
//} password;


// BCD functions
// void zero() {  //0000
//    digitalWrite(BCD_A_PIN, LOW);
//    digitalWrite(BCD_B_PIN, LOW);
//    digitalWrite(BCD_C_PIN, LOW);
//    digitalWrite(BCD_D_PIN, LOW);
//}
//
//void one() {  //0001
//    digitalWrite(BCD_A_PIN, HIGH);
//    digitalWrite(BCD_B_PIN, LOW);
//    digitalWrite(BCD_C_PIN, LOW);
//    digitalWrite(BCD_D_PIN, LOW);
//}
//
//void two() {  // 0010
//    digitalWrite(BCD_A_PIN, LOW);
//    digitalWrite(BCD_B_PIN, HIGH);
//    digitalWrite(BCD_C_PIN, LOW);
//    digitalWrite(BCD_D_PIN, LOW);
//}
//
//void three() {  // 0011
//    digitalWrite(BCD_A_PIN, HIGH);
//    digitalWrite(BCD_B_PIN, HIGH);
//    digitalWrite(BCD_C_PIN, LOW);
//    digitalWrite(BCD_D_PIN, LOW);
//}
//
//void four() {  // 0100
//    digitalWrite(BCD_A_PIN, LOW);
//    digitalWrite(BCD_B_PIN, LOW);
//    digitalWrite(BCD_C_PIN, HIGH);
//    digitalWrite(BCD_D_PIN, LOW);
//}
//
//void five() {  // 0101
//    digitalWrite(BCD_A_PIN, HIGH);
//    digitalWrite(BCD_B_PIN, LOW);
//    digitalWrite(BCD_C_PIN, HIGH);
//    digitalWrite(BCD_D_PIN, LOW);
//}
//
//void six() {  // 0110
//    digitalWrite(BCD_A_PIN, LOW);
//    digitalWrite(BCD_B_PIN, HIGH);
//    digitalWrite(BCD_C_PIN, HIGH);
//    digitalWrite(BCD_D_PIN, LOW);
//}
//
//void seven() {  // 0111
//    digitalWrite(BCD_A_PIN, HIGH);
//    digitalWrite(BCD_B_PIN, HIGH);
//    digitalWrite(BCD_C_PIN, HIGH);
//    digitalWrite(BCD_D_PIN, LOW);
//}
//
//void eight() {  // 1000
//    digitalWrite(BCD_A_PIN, LOW);
//    digitalWrite(BCD_B_PIN, LOW);
//    digitalWrite(BCD_C_PIN, LOW);
//    digitalWrite(BCD_D_PIN, HIGH);
//}
//
//void nine() {  // 1001
//    digitalWrite(BCD_A_PIN, HIGH);
//    digitalWrite(BCD_B_PIN, LOW);
//    digitalWrite(BCD_C_PIN, LOW);
//    digitalWrite(BCD_D_PIN, HIGH);
//}

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
    if (display == 0) {  // Choosing value for the first shift register
        // Shift out the pattern to the first 74HC595
        digitalWrite(SR_LATCH_PIN, LOW);
        shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, patterns[0]);       // Clear the second shift register
        shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, patterns[number]);  // Shift pattern for the first display
        digitalWrite(SR_LATCH_PIN, HIGH);
        shift_register_1 = number;
    } else if (display == 1) {  // Choosing value for the second shift register
        // Shift out the pattern to the second 74HC595
        digitalWrite(SR_LATCH_PIN, LOW);
        shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, patterns[number]);
        shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, patterns[shift_register_1]);  // Save first number
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

// 
bool isButtonPressed(int button_pin) {
    static unsigned long time_of_last_change = 0;
    static int button_state = HIGH;  // initial state: not pressed
    const unsigned long current_time = millis();
    const int new_state = digitalRead(button_pin);

    if (button_state != new_state && (current_time - time_of_last_change > DEBOUNCE_TIME)) {
        // a valid change was detected
        time_of_last_change = current_time;    // save time of this change
        button_state = new_state;              // update the button's known state
        if (button_state == LOW) return true;  // if button was pressed, return true
    }
    return false;
}

bool isPasswordCorrect(const int *password, int password_length, const int *user_input) {
    for (int i = 0; i < password_length; ++i) {
        if (password[i] != user_input[i]) return false;
    }
    return true;
}

void printArray(const int *array, const int *length) {
    Serial.print("{ ");
    for (int i = 0; i < *length; i++) {
        Serial.print(array[i]);
        Serial.print(" ");
    }
    Serial.print(" }");
}

void rotateServo(bool rotate) {
    if (rotate) {
        MYSERVO.write(90);
        Serial.print("Servo Angle: ");
        Serial.println(90);
    } else {
        MYSERVO.write(0);
        Serial.print("Servo Angle: ");
        Serial.println(0);
    }
}

void handleButtonPress() {
    static bool servo_rotate = false;  // current state of the servo
    if (isButtonPressed(BUTTON_SUBMIT_PIN)) {
        servo_rotate = !servo_rotate;
        if (servo_rotate) {
            Serial.println("The button is pressed");
        }
        rotateServo(servo_rotate);
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
    // BUTTON
    pinMode(BUTTON_SUBMIT_PIN, INPUT_PULLUP);
    // SERVO
    MYSERVO.attach(SERVO_PIN);

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
    // 7-SEGMENTS
    const int seven_segments[3] = { 0, 1, 2 };
    static int index_seven_segments = 0;
    static int counter = 0;
    static bool direction = DIRECTION_CW;
    // PASSWORD
    static int password[3] = { 2, 4, 6 };
    const int password_length = sizeof(password) / sizeof(password[0]);
    static int user_input[3] = { 0, 0, 0 };
    // TIME CHECK
    static unsigned long time_of_last_change = 0;
    const unsigned long current_time = millis();
    // ROTARY ENCODER BUTTON
    static int RE_BUTTON_state = HIGH;
    const int prev_RE_BUTTON_state = digitalRead(RE_BUTTON_PIN);
    // ROTARY ENCODER CLOCK
    static int prev_RE_CLK_state = HIGH;
    const int RE_CLK_state = digitalRead(RE_CLK_PIN);
    static bool servo_rotate = false;


    if (RE_BUTTON_state != prev_RE_BUTTON_state && (current_time - time_of_last_change > DEBOUNCE_TIME)) {
        // a valid change was detected
        time_of_last_change = current_time;      // save time of this change
        RE_BUTTON_state = prev_RE_BUTTON_state;  // update the button's known state
        if (RE_BUTTON_state == LOW) {
            // Switch two the second seven segment
            Serial.println("The button is pressed");
            // TODO: Save input value into an array then compare with the password has saved in EEPROM
            // EEPROM Arduino Uno = 1kbytes
            // Switch to the next seven-segments
            if (index_seven_segments <= 3) {
                user_input[index_seven_segments] = counter;
                Serial.print("Index: ");
                Serial.print(index_seven_segments);
                Serial.print(" Value: ");
                Serial.println(counter);
                index_seven_segments++;
            }
            // TODO:
            // TODO: EEPROM variable
            // - Password // byte array (0->100)
            // - Attempts times // in
            // -
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

        displayNumber(counter, seven_segments[index_seven_segments]);
    }
    // save last CLK state
    prev_RE_CLK_state = RE_CLK_state;


    if (isButtonPressed(BUTTON_SUBMIT_PIN) && (index_seven_segments == 3)) {
        Serial.println("Check password, please wait!");
        delay(1000);
        // function check pass
        if (isPasswordCorrect(password, password_length, user_input)) {
            Serial.println("Password is correct! Servo is rotate!");
            servo_rotate = !servo_rotate;
            if (servo_rotate) {
                Serial.println("The button is pressed");
            }
            rotateServo(servo_rotate);
        } else {
            Serial.println("Password is incorrect! Servo is NOT rotate!");
        }
    }
}
