//
// Created by Dung Phan on 1/1/2024.
//

#include "notification.h"


// static void notification_oled_success() {
//     oled.setTextSize(2);
//     oled.setCursor(24, 15);
//     oled.println("Success");
//     oled.display();
// }

// static void notification_oled_failed() {
//     oled.setTextSize(2);
//     oled.setCursor(24, 15);
//     oled.println("Failed");
//     oled.display();
// }

// static void notification_oled_update_password() {
//     oled.setTextSize(2);
//     oled.setCursor(24, 15);
//     oled.println("Update password");
//     oled.display();
// }

// static void notification_oled_door_lock() {
//     oled.setTextSize(2);
//     oled.setCursor(24, 15);
//     oled.println("Door Locked");
//     oled.display();
// }

static void sound(int option, int buzzer_pin) {
    int melodies[2][3] = {
            {NOTE_E6, NOTE_C6, NOTE_G6},  // SUCCEEDED
            {NOTE_C3, NOTE_D2, NOTE_C2}   // FAILED
    };
    int noteDurations[2][3] = {
            {16, 16, 4},
            {8,  4,  2}
    };
    for (int thisNote = 0; thisNote < 3; thisNote++) {
        int noteDuration = 1000 / noteDurations[option][thisNote];
        tone(buzzer_pin, melodies[option][thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
    }
}


static void notification_buzzer(notification_t notification) {
    switch (notification) {
        case SUCCEEDED:          // LED GREEN
            sound(0, BUZZER_PIN);  // succeed
            break;
        case FAILED:             // LED RED
            sound(1, BUZZER_PIN);  // failed
            break;
        case UPDATED_PASSWORD:   // LED YELLOW + GREEN
            sound(0, BUZZER_PIN);  // succeed
            break;
        case EXISTED_PASSWORD:   // LED YELLOW + RED
            sound(1, BUZZER_PIN);  // failed
            break;
        case LOCKED:             // LED RED + YELLOW + GREEN
            sound(1, BUZZER_PIN);  // failed
            break;
        case SERVO_ROTATE:  // LED YELLOW
            break;
        case DOOR_CLOSE:  // ALL LED OFF
            break;
        default:
            break;
    }
}

static void notification_oled(notification_t notification) {
    switch (notification) {
        case SUCCEEDED:  // LED GREEN
            // notification_oled_success();
            break;
        case FAILED:  // LED RED
            // notification_oled_failed();
            break;
        case UPDATED_PASSWORD:  // LED YELLOW + GREEN
            // notification_oled_update_password();
            break;
        case EXISTED_PASSWORD:  // LED YELLOW + RED
            break;
        case LOCKED:  // LED RED + YELLOW + GREEN
            break;
        case SERVO_ROTATE:  // LED YELLOW
            break;
        case DOOR_CLOSE:  // ALL LED OFF
            // notification_oled_door_lock();
            break;
        default:
            break;
    }
}

static void notification_leds(notification_t notification) {
    switch (notification) {
        case SUCCEEDED:  // LED GREEN
            digitalWrite(LED_RED_PIN, LOW);
            digitalWrite(LED_YELLOW_PIN, LOW);
            digitalWrite(LED_GREEN_PIN, HIGH);
            break;
        case FAILED:  // LED RED
            digitalWrite(LED_RED_PIN, HIGH);
            digitalWrite(LED_YELLOW_PIN, LOW);
            digitalWrite(LED_GREEN_PIN, LOW);
            break;
        case UPDATED_PASSWORD:  // LED YELLOW + GREEN
            digitalWrite(LED_RED_PIN, LOW);
            digitalWrite(LED_YELLOW_PIN, HIGH);
            digitalWrite(LED_GREEN_PIN, HIGH);
            break;
        case EXISTED_PASSWORD:  // LED YELLOW + RED
            digitalWrite(LED_RED_PIN, HIGH);
            digitalWrite(LED_YELLOW_PIN, HIGH);
            digitalWrite(LED_GREEN_PIN, LOW);
            break;
        case LOCKED:  // LED RED + YELLOW + GREEN
            digitalWrite(LED_RED_PIN, HIGH);
            digitalWrite(LED_YELLOW_PIN, HIGH);
            digitalWrite(LED_GREEN_PIN, HIGH);
            break;
        case SERVO_ROTATE:  // LED YELLOW
            digitalWrite(LED_RED_PIN, LOW);
            digitalWrite(LED_YELLOW_PIN, HIGH);
            digitalWrite(LED_GREEN_PIN, LOW);
            break;
        case DOOR_CLOSE:  // ALL LED OFF
            digitalWrite(LED_RED_PIN, LOW);
            digitalWrite(LED_YELLOW_PIN, LOW);
            digitalWrite(LED_GREEN_PIN, LOW);
            break;
        default:
            digitalWrite(LED_RED_PIN, LOW);
            digitalWrite(LED_YELLOW_PIN, LOW);
            digitalWrite(LED_GREEN_PIN, LOW);
    }
}

void notification_system(notification_t notification) {
    switch (notification) {
        case SUCCEEDED:
            notification_oled(SUCCEEDED);
            notification_buzzer(SUCCEEDED);
            notification_leds(SUCCEEDED);
            break;
        case FAILED:
            notification_oled(FAILED);
            notification_buzzer(FAILED);
            notification_leds(FAILED);
            break;
        case UPDATED_PASSWORD:
            notification_oled(UPDATED_PASSWORD);
            notification_buzzer(UPDATED_PASSWORD);
            notification_leds(UPDATED_PASSWORD);
            break;
        case EXISTED_PASSWORD:
            notification_oled(EXISTED_PASSWORD);
            notification_buzzer(EXISTED_PASSWORD);
            notification_leds(EXISTED_PASSWORD);
            break;
        case LOCKED:
            notification_oled(LOCKED);
            notification_buzzer(LOCKED);
            notification_leds(LOCKED);
            break;
        case SERVO_ROTATE:  // LED YELLOW
            notification_oled(SERVO_ROTATE);
            notification_buzzer(SERVO_ROTATE);
            notification_leds(SERVO_ROTATE);
            break;
        case DOOR_CLOSE:  // ALL LED OFF
            notification_oled(DOOR_CLOSE);
            notification_buzzer(DOOR_CLOSE);
            notification_leds(DOOR_CLOSE);
            break;
        default:
            notification_oled(DOOR_CLOSE);
            notification_buzzer(DOOR_CLOSE);
            notification_leds(DOOR_CLOSE);
    }
}