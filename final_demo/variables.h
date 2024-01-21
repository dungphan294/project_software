//
// Created by Dung Phan on 1/18/2024.
//
#ifndef DEMO_VARIABLES_H
#define DEMO_VARIABLES_H

// SHIFT REGISTER
#define SR_DATA_PIN 13   // SER
#define SR_LATCH_PIN 12  // RCLK
#define SR_CLOCK_PIN 11  // SRCLK
// ROTARY ENCODER
#define RE_BUTTON_PIN 10  // SW
#define RE_CLK_PIN 9      // A
#define RE_DATA_PIN 8     // B
// LEDS
#define LED_RED_PIN 7
#define LED_YELLOW_PIN 6
#define LED_GREEN_PIN 5
// BUTTON
#define BUTTON_DOOR_PIN 4   // BUTTON OPEN DOOR
#define BUTTON_SERVO_PIN 3  // BUTTON Check pass
#define SERVO_PIN 2
// BCD
#define BCD_A_PIN A0   // BCD Input 1
#define BCD_B_PIN A1   // BCD Input 2
#define BCD_C_PIN A2   // BCD Input 3
#define BCD_D_PIN A3   // BCD Input 4
#define BCD_DP_PIN A4  // BCD DP 7-segment
// BUZZER
#define BUZZER_PIN A5

// VARIABLES
#define DEBOUNCE_TIME 100
#define DIRECTION_CW 0   // clockwise direction
#define DIRECTION_CCW 1  // counter-clockwise direction
#define EEPROM_USER_MEMORY 0
#define EEPROM_ATTEMPT_MEMORY 50
#define EEPROM_PASSWORD_MEMORY 100

// ENUM
typedef enum {
  SUCCEEDED,         // LED GREEN
  FAILED,            // LED RED
  UPDATED_PASSWORD,  // LED YELLOW + GREEN
  EXISTED_PASSWORD,  // LED YELLOW + RED
  LOCKED,            // LED RED + YELLOW + GREEN
  SERVO_ROTATE,      // LED YELLOW
  DOOR_CLOSE         // ALL LED OFF
} notification_t;

// STRUCT
typedef struct {
  int password[3];
  int attempts;  // How many times did user check password
} password_t;

#endif  //DEMO_VARIABLES_H