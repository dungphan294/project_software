//
// Created by Dung Phan on 1/1/2024.
//

#ifndef DEMO_NOTIFICATION_H
#define DEMO_NOTIFICATION_H

#include "Arduino.h"
#include "pitches.h"


// ## LEDS
const int LED_RED_PIN = 7;
const int LED_YELLOW_PIN = 6;
const int LED_GREEN_PIN = 5;
// BUZZER
const int BUZZER_PIN = A5;

typedef enum {
    SUCCEEDED,         // LED GREEN
    FAILED,            // LED RED
    UPDATED_PASSWORD,  // LED YELLOW + GREEN
    EXISTED_PASSWORD,  // LED YELLOW + RED
    LOCKED,            // LED RED + YELLOW + GREEN
    SERVO_ROTATE,      // LED YELLOW
    DOOR_CLOSE             // ALL LED OFF
} notification_t;

static void notification_oled_success();

static void notification_oled_failed();

static void notification_oled_update_password();

static void notification_oled_door_lock();

///
/// \param option
/// \param buzzer_pin
static void sound(int option, int buzzer_pin);

///
/// \param notification
static void notification_buzzer(notification_t notification);

///
/// \param notification
static void notification_oled(notification_t notification);

///
/// \param notification
static void notification_leds(notification_t notification);

///
/// \param notification
void notification_system(notification_t notification);

#endif //DEMO_NOTIFICATION_H
