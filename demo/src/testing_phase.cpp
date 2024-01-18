//
// Created by Dung Phan on 1/1/2024.
//
#include <Arduino.h>
#include <Servo.h>
#include <EEPROM.h>
#include "display.h"
#include "notification.h"


// TODO: CODE CONVENTION
// FUNTION_NAME:
// - NORMAL FUNCTION: this_is_function()
// - BOOL FUNCTION: is_this_function()
// VARIABLE_NAME: this_is_var
// CONST_NAME: THIS_IS_CONST

// # COMPONENTS & VARIABLES
// ## ROTARY ENCODER
const int RE_BUTTON_PIN = 10;  // SW
const int RE_CLK_PIN = 9;      // A
const int RE_DATA_PIN = 8;     // B

// ## BUTTON
const int BUTTON_DOOR_PIN = 4;   // BUTTON OPEN DOOR
const int BUTTON_SERVO_PIN = 3;  // BUTTON Check pass
// ## SERVO
Servo SERVO;
const int SERVO_PIN = 2;


// ## VARIABLES
const int DEBOUNCE_TIME = 70;
const int DIRECTION_CW = 0;   // clockwise direction
const int DIRECTION_CCW = 1;  // counter-clockwise direction
const int EEPROM_USER_MEMORY = 0;
const int EEPROM_7_SEGMENT = 25;
const int EEPROM_ATTEMPT_MEMORY = 50;
const int EEPROM_PASSWORD_MEMORY = 100;


typedef struct {
    int password[3];
    int attempts;  // How many times did user check password
} password_t;


// ## PASSWORD FUNCTIONS
/*
 * TODO: Define where we store value
 * 0 - 99: User input
 * 100 - 199: Password
 * 200 - 299: Attempts
 */

bool is_button_pressed(const int button_pin, const int debounce_time) {
    static unsigned long time_of_last_change = 0;
    static int button_state = HIGH;  // initial state: not pressed
    const unsigned long current_time = millis();
    const int new_state = digitalRead(button_pin);

    if (button_state != new_state && (current_time - time_of_last_change > debounce_time)) {
        // a valid change was detected
        time_of_last_change = current_time;    // save time of this change
        button_state = new_state;              // update the button's known state
        if (button_state == LOW) return true;  // if button was pressed, return true
    }
    return false;
}

void save_user_input(password_t *user_input, int segment) {
    Serial.print("Save USER_INPUT at MEMORY ADDRESS: ");
    Serial.print(EEPROM_USER_MEMORY + segment);
    Serial.print(" With VALUE: ");
    Serial.println(user_input->password[segment]);
    EEPROM.update(EEPROM_USER_MEMORY + segment, user_input->password[segment]);
}

int read_user_input(int segment) {
    EEPROM.read(EEPROM_USER_MEMORY + segment);
}

void print_password_memory() {
    Serial.print("{ ");
    for (int i = 0; i < 3; i++) {
        Serial.print(EEPROM.read(EEPROM_PASSWORD_MEMORY + i));
        Serial.print(" ");
    }
    Serial.println(" }");
}

void print_password_array(password_t *password) {
    Serial.print("{ ");
    for (int i = 0; i < 3; i++) {
        Serial.print(password->password[i]);
        Serial.print(" ");
    }
    Serial.println(" }");
}

int *read_password(password_t *password) {
    int password_length = sizeof(password->password) / sizeof(password->password[0]);
    // Serial.print("{ ");
    for (int i = 0; i < password_length; ++i) {
        password->password[i] = EEPROM.read(EEPROM_PASSWORD_MEMORY + i);
        // Serial.print(password->password[i]);
        // Serial.print(" ");
    }
    // Serial.println("}");
    return password->password;
}


bool is_password_correct(password_t *user_input) {
    password_t *password;
    read_password(password);
    int password_length = sizeof(password->password) / sizeof(password->password[0]);
    for (int i = 0; i < password_length; ++i) {
        if (password->password[i] != user_input->password[i]) return false;
    }
    return true;
}

void update_password(password_t *user_input) {
    int password_length = sizeof(user_input->password) / sizeof(user_input->password[0]);
    if (is_password_correct(user_input)) {
        Serial.println("This password is existed! Please try again!");
        notification_system(EXISTED_PASSWORD);
    } else {
        for (int i = 0; i < password_length; ++i) {
            EEPROM.update(EEPROM_PASSWORD_MEMORY + i, user_input->password[i]);
        }
        Serial.println("Change password successfully!");
        notification_system(SUCCEEDED);
    }
}


int read_attempts(password_t *attempt) {
    attempt->attempts = EEPROM.read(EEPROM_ATTEMPT_MEMORY);
    return attempt->attempts;
}

void update_attempts(password_t *attempt) {
    EEPROM.update(EEPROM_ATTEMPT_MEMORY, attempt->attempts++);
}

void system_locked() {
    password_t *attempt;
    read_attempts(attempt);
}


void rotate_servo(bool rotate) {
    if (!rotate) {
        SERVO.write(0);
        Serial.print("Servo Angle: ");
        Serial.println(0);
    } else {
        SERVO.write(180);
        Serial.print("Servo Angle: ");
        Serial.println(180);
    }
}

void setup() {

    Serial.begin(9600);
    // SHIFT REGISTER
    pinMode(SR_DATA_PIN, OUTPUT);   //13
    pinMode(SR_LATCH_PIN, OUTPUT);  //12
    pinMode(SR_CLOCK_PIN, OUTPUT);  //11
    // ROTARY ENCODER
    pinMode(RE_BUTTON_PIN, INPUT_PULLUP);  //10
    pinMode(RE_CLK_PIN, INPUT);            // 9
    pinMode(RE_DATA_PIN, INPUT);           // 8
    // LEDS
    pinMode(LED_RED_PIN, OUTPUT);     // 7
    pinMode(LED_YELLOW_PIN, OUTPUT);  // 6
    pinMode(LED_GREEN_PIN, OUTPUT);   // 5
    // BUTTON
    pinMode(BUTTON_DOOR_PIN, INPUT_PULLUP);   // 4
    pinMode(BUTTON_SERVO_PIN, INPUT_PULLUP);  // 3
    // SERVO
    SERVO.attach(SERVO_PIN);  // 2
    // BCD
    pinMode(BCD_A_PIN, OUTPUT);   // A0
    pinMode(BCD_B_PIN, OUTPUT);   // A1
    pinMode(BCD_C_PIN, OUTPUT);   // A2
    pinMode(BCD_D_PIN, OUTPUT);   // A3
    pinMode(BCD_DP_PIN, OUTPUT);  // A4
    // BUZZER
    pinMode(BUZZER_PIN, OUTPUT);  // A5
    // Set up the input as user input
    display_number(0, 0);
    display_number(10, 1);
    display_number(10, 2);
    // SERVO.write(0);
}

void loop() {
    // 7-SEGMENTS
    const int seven_segments[3] = { 0, 1, 2 };
    static int index_seven_segments = 0;          // Tracking the display
    static bool is_index_seven_segments = false;  // If index_seven_segments > 2 -> can not add more input from user
    static bool is_servo_rotate = false;          // If is_index_seven_segments && is_button_pressed(BUTTON_SERVO_PIN, DEBOUNCE_TIME) ->
    static bool is_door_open = false;             // If is_servo_rotate && is_button_pressed(BUTTON_DOOR_PIN, DEBOUNCE_TIME)
    static bool is_reset_index = false;
    static bool is_change_password_mode = false;  // If
    static bool is_count_to_two = false;
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
    // PASSWORD
    password_t password;
    read_password(&password);
    static password_t user_input;

    // ROTARY INPUT - DOOR CLOSED
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
        display_number(counter, seven_segments[index_seven_segments]);
    }
    // save last CLK state
    prev_RE_CLK_state = RE_CLK_state;
    // ROTARY BUTTON - DOOR CLOSED
    if (!is_door_open && is_button_pressed(RE_BUTTON_PIN, DEBOUNCE_TIME)) {
        if (index_seven_segments < 3) {
            user_input.password[index_seven_segments] = counter;
            // Save user_input into EEPROM
            save_user_input(&user_input, index_seven_segments);
            Serial.print("Index: ");
            Serial.print(index_seven_segments);
            Serial.print(" Value: ");
            Serial.println(counter);
            index_seven_segments++;
            counter = 0;
            display_number(counter, seven_segments[index_seven_segments]);
            if (index_seven_segments > 2) {
                is_index_seven_segments = true;
                is_count_to_two = false;
            }
        }
    } else if  // // DOOR OPEN - CHANGE PASSWORD MODE ON
            (is_door_open && is_change_password_mode && is_button_pressed(RE_BUTTON_PIN, DEBOUNCE_TIME)) {
        // Serial.println(digitalRead(BUTTON_SERVO_PIN));
        if (index_seven_segments < 3) {
            user_input.password[index_seven_segments] = counter;
            // Save user_input into EEPROM
            save_user_input(&user_input, index_seven_segments);
            Serial.print("Index: ");
            Serial.print(index_seven_segments);
            Serial.print(" Value: ");
            Serial.println(user_input.password[index_seven_segments]);
            index_seven_segments++;
            counter = 0;
            display_number(counter, seven_segments[index_seven_segments]);
            if (index_seven_segments > 2) {
                is_index_seven_segments = true;
                is_count_to_two = true;
            }
        }
    }
    // CHECK PASSWORD - DOOR CLOSED
    if (!is_door_open && is_index_seven_segments && is_button_pressed(BUTTON_SERVO_PIN, DEBOUNCE_TIME)) {
        is_index_seven_segments = false;
        // CHECK PASSWORD MODE
        Serial.println("Check password, please wait!");
        if (is_password_correct(&user_input)) {
            is_servo_rotate = true;
            if (is_servo_rotate) {
                Serial.println("Password is correct! Servo is rotate!");
                Serial.println("The button is pressed");
                print_password_memory();
                rotate_servo(is_servo_rotate);
                display_number(0, 0);
                display_number(0, 1);
                display_number(0, 2);
                notification_system(SERVO_ROTATE);
            }
        } else {
            Serial.println("Password is incorrect! Servo is NOT rotate!");
            print_password_memory();
            // Wrong pass -> update attempts
            update_attempts(&user_input);
            // Set index segment = 0
            index_seven_segments = 0;
            display_number(0, 0);
            display_number(10, 1);
            display_number(10, 2);
            notification_system(FAILED);
        }
    }
    // CHECK DOOR - DOOR OPEN
    if (!is_door_open && is_servo_rotate && is_button_pressed(BUTTON_DOOR_PIN, DEBOUNCE_TIME)) {
        is_servo_rotate = false;
        is_door_open = true;
        is_reset_index = true;
        notification_system(SUCCEEDED);
        Serial.println("The door is open!");
    } else if (is_door_open && is_button_pressed(BUTTON_DOOR_PIN, DEBOUNCE_TIME)) {
        index_seven_segments = 0;
        is_door_open = false;
        is_servo_rotate = false;
        is_reset_index = true;
        rotate_servo(is_servo_rotate);
        notification_system(DOOR_CLOSE);
        Serial.println("The door is close!");
        display_number(0, 0);
        display_number(10, 1);
        display_number(10, 2);
    }
    // // // DOOR OPEN - CHANGE PASSWORD MODE
    if (is_door_open && is_reset_index && is_button_pressed(BUTTON_SERVO_PIN, DEBOUNCE_TIME)) {
        index_seven_segments = 0;
        is_reset_index = !is_reset_index;
        is_change_password_mode = !is_change_password_mode;
        Serial.println("Change password mode!");
        display_number(0, 0);
        display_number(10, 1);
        display_number(10, 2);
    }
    if (is_door_open && is_change_password_mode && is_index_seven_segments && is_count_to_two && is_button_pressed(BUTTON_SERVO_PIN, DEBOUNCE_TIME) == true) {
        print_password_array(&user_input);
        update_password(&user_input);
        is_change_password_mode = !is_change_password_mode;
    }
}