#include <Arduino.h>
#include <Servo.h>
#include <EEPROM.h>

// TODO: CODE CONVENTION
// FUNTION_NAME:
// - NORMAL FUNCTION: this_is_function()
// - BOOL FUNCTION: is_this_function()
// VARIABLE_NAME: this_is_var
// CONST_NAME: THIS_IS_CONST

// # COMPONENTS & VARIABLES
// ## SHIFT REGISTER
const int SR_DATA_PIN = 13;   // SER
const int SR_LATCH_PIN = 12;  // RCLK
const int SR_CLOCK_PIN = 11;  // SRCLK
// ## BCD
const int BCD_A_PIN = A0;  // BCD Input 1
const int BCD_B_PIN = A1;  // BCD Input 2
const int BCD_C_PIN = A2;  // BCD Input 3
const int BCD_D_PIN = A3;  // BCD Input 4
// ## ROTARY ENCODER
const int RE_BUTTON_PIN = 6;  // SW
const int RE_CLK_PIN = 5;     // A
const int RE_DATA_PIN = 4;    // B
// ## BUTTON
const int BUTTON_SERVO_PIN = 3;  // BUTTON Check pass
const int BUTTON_DOOR_PIN = 2;    // BUTTON OPEN DOOR
// ## SERVO
Servo SERVO;
const int SERVO_PIN = 2;
// ## LED, BUZZER, OLED - NOTIFICATION

// ## VARIABLES
const int DEBOUNCE_TIME = 50;
const int DIRECTION_CW = 0;   // clockwise direction
const int DIRECTION_CCW = 1;  // counter-clockwise direction
const int EEPROM_USER_MEMORY = 0;
const int EEPROM_ATTEMPT_MEMORY = 50;
const int EEPROM_PASSWORD_MEMORY = 100;

typedef struct {
    int password[3];
    int attempts;
} password_t;

typedef enum {
    SUCCEEDED, FAILED, UPDATED_PASSWORD, EXISTED_PASSWORD, LOCKED
} notification_t;

// # FUNCTIONS
// ## COMPONENTS FUNCTIONS
///
/// \param button_pin
/// \param debounce_time
/// \return
bool is_button_pressed(const int button_pin, const int debounce_time);

//typedef enum {
//    ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO_DP
//} NUMBER;

byte byte_to_number(int number) {
    byte patterns[11] = {
            B01000000,  // 0
            B01111001,  // 1
            B00100100,  // 2
            B00110000,  // 3
            B00011001,  // 4
            B00010010,  // 5
            B00000011,  // 6
            B11111000,  // 7
            B00000000,  // 8
            B00011000,   // 9
            B11000000 // 0 not DP
    };
    return patterns[number];
}

void display_number(int number, int display) {
    static int shift_register_1 = 0;
    //    static int shift_register_2 = 0;
    // TODO: Function to control BCD
    if (display == 0) {  // Choosing value for the first shift register
        // Shift out the pattern to the first 74HC595
        digitalWrite(SR_LATCH_PIN, LOW);
        shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, byte_to_number(0));       // Clear the second shift register
        shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, byte_to_number(number));  // Shift pattern for the first display
        digitalWrite(SR_LATCH_PIN, HIGH);
        shift_register_1 = number;
    } else if (display == 1) {  // Choosing value for the second shift register
        // Shift out the pattern to the second 74HC595
        digitalWrite(SR_LATCH_PIN, LOW);
        shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, byte_to_number(number));
        shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, byte_to_number(shift_register_1));  // Save first number
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

///
/// \param notification
void notification_system(notification_t notification);

///
/// \param notification
void notification_oled(notification_t notification);

///
/// \param notification
void notification_buzzer(notification_t notification);

///
/// \param notification
void notification_leds(notification_t notification);


// ## PASSWORD FUNCTIONS
/*
 * TODO: Define where we store value
 * 0 - 99: User input
 * 100 - 199: Password
 * 200 - 299: Attempts
 */
///
/// \param password
/// \param user_input
/// \return
bool is_password_correct(password_t *user_input);

/// User use ROTARY ENCODER to
/// \param user_input
void save_user_input(password_t *user_input);

///
/// \param user_input
/// \return
void update_password(password_t *user_input);


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

void notification_system(notification_t notification) {
    switch (notification) {
        case SUCCEEDED:
            notification_oled(SUCCEEDED);
            notification_buzzer(SUCCEEDED);
            notification_leds(SUCCEEDED);
        case FAILED:
            notification_oled(FAILED);
            notification_buzzer(FAILED);
            notification_leds(FAILED);
        case UPDATED_PASSWORD:
            notification_oled(UPDATED_PASSWORD);
            notification_buzzer(SUCCEEDED);
            notification_leds(SUCCEEDED);
        case EXISTED_PASSWORD:
            notification_oled(EXISTED_PASSWORD);
            notification_buzzer(FAILED);
            notification_leds(FAILED);
        case LOCKED:
            notification_oled(LOCKED);
            notification_buzzer(LOCKED);
            notification_leds(LOCKED);
        default:
            notification_oled(SUCCEEDED);
            notification_buzzer(SUCCEEDED);
            notification_leds(SUCCEEDED);
    }
}

void notification_OLED(notification_t notification) {
}

void notification_BUZZER(notification_t notification) {
}

void notification_LEDS(notification_t notification) {
}

int *read_password(password_t *password) {
    int password_length = sizeof(password->password) / sizeof(password->password[0]);
    for (int i = 0; i < password_length; ++i) {
        password->password[i] = EEPROM.read(EEPROM_PASSWORD_MEMORY + 1);
    }
    return password->password;
}

void save_user_input(password_t *user_input, int segments) {
    EEPROM.write(EEPROM_USER_MEMORY + segments, user_input->password[segments]);
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
    }
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



void rotateServo(bool rotate) {
    if (rotate) {
        SERVO.write(90);
        Serial.print("Servo Angle: ");
        Serial.println(90);
    } else {
        SERVO.write(0);
        Serial.print("Servo Angle: ");
        Serial.println(0);
    }
}

// TODO: List of Var need to store in EEPROM
// --- PASSWORD
// Password: Array[3]
// Attempt: How many times have user tried?
// Attempt 1 / 3 = 0
// Attempt 2 / 3 = 0
// Attempt 3 / 3 = 1 -> penalty 1 * 100 seconds;
// 100s penalty
// --- USER INPUT
// Q: If we unplug the UNO, when we plug the UNO again value show at the segment we use
// -- END --
//
/*
 * TODO: Define where we store value
 * 0 - 99: User input
 * 100 - 199: Password
 * 200 - 299: Attempts
 */

/*
 * TODO: Functions we need:
 * - insert_password(password_t *)
 * Insert Password - Save user input at the first time they user the safe
 * - update_password()
 * Update Password - Change Password
 * - is_password_correct(password_t *password, password_t *user_input)
 * Check Password - Checking user input matches the Password
 * - user_attempts()
 * Check Attempts - Checking attempt number -> penalty for user
 *
 */

/*
 * TODO: Workflow of the ELECTRICAL SAFE
 * # SITUATION: FIRST USE
 * -- STATE: SAFE CLOSE
 * 1. Connect to POWER SOURCES
 * 2. 3 SEVEN SEGMENTS set up at {0, 0, 0} -> function is_password_correct()
 * 3. Click SERVO_BUTTON -> servo_rotate(90)
 * 4. All number reset to ZERO
 * 5. Click DOOR_BUTTON -> indicate the door of the safe is OPENED
 * -- STATE: SAFE OPEN *
 * 1. Click SERVO_BUTTON -> STATE: CHANGE PASSWORD -> function update_password()
 * 2. Back to the first 7-segment: DP light up, other DP don't
 * EXTRA: DOOR_BUTTON works as RESET_BUTTON when user choose the wrong input (click DOOR_BUTTON -> BACK TO 1st 7-segment)
 * 3. Choose the number for the 1st segment -> Click the ROTARY_BUTTON -> Save it into EEPROM -> save_user_input()
 * 4. Choose the number for the 2nd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM -> save_user_input()
 * 5. Choose the number for the 3rd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM -> save_user_input()
 * 6. Click SERVO_BUTTON -> END STATE: CHANGE PASSWORD -> function notification()
 * 7. Click DOOR_BUTTON -> indicate the door of the safe is CLOSED -> servo_rotate(0)
 * -- STATE: SAFE CLOSE
 * # SITUATION: FROM THE SECOND TIMES
 * -- STATE: SAFE CLOSE
 * 1. Choose the number for the 1st segment -> Click the ROTARY_BUTTON -> Save it into EEPROM -> save_user_input()
 * 2. Choose the number for the 2nd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM -> save_user_input()
 * 3. Choose the number for the 3rd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM -> save_user_input()
 * 4. Click SERVO_BUTTON -> servo_rotate(90)
 * 5. All number reset to ZERO
 * 6. Click DOOR_BUTTON -> indicate the door of the safe is OPENED
 * 7. Click DOOR_BUTTON again -> indicate the door of the safe is CLOSED -> servo_rotate(0)
 * -- SITUATION: CHANGE PASSWORD
 * 1. Choose the number for the 1st segment -> Click the ROTARY_BUTTON -> Save it into EEPROM -> save_user_input()
 * 2. Choose the number for the 2nd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM -> save_user_input()
 * 3. Choose the number for the 3rd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM -> save_user_input()
 * 4. Click SERVO_BUTTON -> servo_rotate(90)
 * 5. All number reset to ZERO
 * 6. Click DOOR_BUTTON -> indicate the door of the safe is OPENED
 * -- STATE: SAFE OPEN *
 * 1. Click SERVO_BUTTON -> STATE: CHANGE PASSWORD -> function update_password()
 * 2. Back to the first 7-segment: DP light up, other DP don't
 * EXTRA: DOOR_BUTTON works as RESET_BUTTON when user choose the wrong input (click DOOR_BUTTON -> BACK TO 1st 7-segment)
 * 3. Choose the number for the 1st segment -> Click the ROTARY_BUTTON -> Save it into EEPROM -> save_user_input()
 * 4. Choose the number for the 2nd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM -> save_user_input()
 * 5. Choose the number for the 3rd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM -> save_user_input()
 * 6. Click SERVO_BUTTON -> END STATE: CHANGE PASSWORD -> function notification()
 * 7. Click DOOR_BUTTON -> indicate the door of the safe is CLOSED -> servo_rotate(0)
 */



void setup() {
    Serial.begin(9600);
    for (int i = 0; i < EEPROM.length(); i++) {
        Serial.println(EEPROM.read(i));
    }
//    password_t password = {.password = {1, 2, 3}, .attempts = 1};
//
//    EEPROM.put(0, password);
//    int index = 0;
//    while (index < EEPROM.length()) {
//        //Add one to each cell in the EEPROM
//        Serial.println(EEPROM.read(index));
//        index++;
//    }
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
    pinMode(BUTTON_SERVO_PIN, INPUT_PULLUP);
    // SERVO
    SERVO.attach(SERVO_PIN);

    display_number(0, 0);
    display_number(0, 1);
    display_number(0, 2);

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
    password_t user_input = {.password = {0,0,0}, .attempts = 0};
    static int index_seven_segments = 0;
    static int counter = 0;
    static bool direction = DIRECTION_CW;
    // PASSWORD
    static password_t password = {.password = {2,4,6}, .attempts = 0};
    const int password_length = sizeof(password.password) / sizeof(password.password[0]);
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
                user_input.password[index_seven_segments] = counter;
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

        display_number(counter, user_input.password[index_seven_segments]);
    }
    // save last CLK state
    prev_RE_CLK_state = RE_CLK_state;


    if (is_button_pressed(BUTTON_SERVO_PIN, DEBOUNCE_TIME) && (index_seven_segments == 3)) {
        Serial.println("Check password, please wait!");
        delay(1000);
        // function check pass
        if (is_password_correct(&user_input)) {
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